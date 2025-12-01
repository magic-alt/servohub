#include "app_id_elec_angle_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化

AppResult IdElecAngleModeInit()
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    axis->elec_angle_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE; // 重置辨识状态
    axis->elec_angle_id_config.id_max_A = get_app_Motor_rated_current(); // 设置电角度辨识正弦波幅值，一般设置为电机额定电流

    return APP_RET_SUCCESS;
}

AppResult IdElecAngleModeStart()
{
    return APP_RET_SUCCESS;
}

AppResult IdElecAngleModeRun()
{
    if(get_app_Controlword() == APP_CTRL_ENABLE)
    {
        if (axis->elec_angle_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH)
        {
            // 辨识完成 会自动失能电机
            set_app_Controlword(APP_CTRL_DISABLE);
            return APP_RET_SUCCESS;
        }
    }

    return APP_RET_RUNNING;
}

AppResult IdElecAngleModeStop()
{
    return APP_RET_SUCCESS;
}
