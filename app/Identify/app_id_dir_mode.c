#include "app_id_dir_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化

AppResult IdDirModeInit()
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    axis->direction_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE; // 重置辨识状态

    return APP_RET_SUCCESS;
}

AppResult IdDirModeStart()
{
    return APP_RET_SUCCESS;
}

AppResult IdDirModeRun()
{
    if(get_app_Controlword() == APP_CTRL_ENABLE)
    {
        if (axis->direction_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH)
        {
            // 辨识完成 会自动失能电机
            set_app_Controlword(APP_CTRL_DISABLE);
            return APP_RET_SUCCESS;
        }
    }

    return APP_RET_RUNNING;
}

AppResult IdDirModeStop()
{
    return APP_RET_SUCCESS;
}
