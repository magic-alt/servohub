#include "app_id_tq_fc_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化

AppResult IdTqFcModeInit()
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    return APP_RET_SUCCESS;
}

AppResult IdTqFcModeStart()
{
    return APP_RET_SUCCESS;
}

AppResult IdTqFcModeRun()
{
    if(get_app_Controlword() == APP_CTRL_ENABLE)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_ENABLE && \
                axis->tq_fc_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH)
            {
                // 辨识完成 会自动失能电机
                set_app_Controlword(APP_CTRL_DISABLE);
                // return APP_RET_SUCCESS;
            }
        }
        else
        {
            // 触发急停，辨识失败 会自动失能电机
            set_app_Controlword(APP_CTRL_DISABLE);
            // return APP_RET_FAIL;
        }
    }

    return APP_RET_RUNNING;
}

AppResult IdTqFcModeStop()
{
    return APP_RET_SUCCESS;
}
