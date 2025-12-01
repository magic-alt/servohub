#include "app_id_pole_pairs_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化

AppResult IdPolePairsModeInit()
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    axis->pole_pairs_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE; // 重置辨识状态
    axis->pole_pairs_id_config.id_tar_max_A = get_app_Motor_rated_current(); // 设置辨识最大电流，一般设置为电机额定电流

    return APP_RET_SUCCESS;
}

AppResult IdPolePairsModeStart()
{
    return APP_RET_SUCCESS;
}

AppResult IdPolePairsModeRun()
{
    if(get_app_Controlword() == APP_CTRL_ENABLE)
    {
        if (axis->pole_pairs_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH)
        {
            // 辨识完成 会自动失能电机
            set_app_Controlword(APP_CTRL_DISABLE);
            return APP_RET_SUCCESS;
        }
    }

    return APP_RET_RUNNING;
}

AppResult IdPolePairsModeStop()
{
    return APP_RET_SUCCESS;
}
