#include "app_homing_mode.h"

static HomingMode_t kHmMode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj =
    {
        .speed_tar_p = 0,
        .acc = 0,
        .period_s = 0,
    }
};

AppResult HomingModeInit()
{
    AppVelocityTargetReachedStateClear();
    set_app_Controlword(APP_CTRL_DISABLE);
    kHmMode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult HomingModeStart()
{
    return APP_RET_SUCCESS;
}

AppResult HomingModeRun()
{
    kHmMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (kHmMode.now_Controlword == APP_CTRL_ENABLE)
    {
        // 仅考虑35号回零模式，最终使用负载端的位置信息
        if (kHmMode.pre_Controlword == APP_CTRL_DISABLE)
        {
            // 重新使能后初始化规划器
            SpeedTrajectoryPlanningInit();
        }

        if (get_app_Halt_running_cmd() == true)
        {
            kHmMode.traj.speed_tar_p = 0;
        }
        else
        {
            kHmMode.traj.speed_tar_p = 0;       //仅考虑35号回零模式，其他回零模式设置为回零加速度
        }
        kHmMode.traj.acc = 0;                   //仅考虑35号回零模式，其他回零模式设置为对应搜索速度
    }

    if (kHmMode.now_Controlword != APP_CTRL_DISABLE)
    {
        SpeedTrajectoryPlanningHandle(&kHmMode.traj);
    }

    kHmMode.pre_Controlword = kHmMode.now_Controlword;

    AppVelocityTargetReachedStateCheck();

    // 单独处理35号回零模式
    if (kHmMode.now_Controlword == APP_CTRL_ENABLE && get_app_Homing_method() == 35)
    {
        volatile int64_t offset_last = get_app_Home_position_offset_value();
        set_app_Home_position_offset_value(offset_last + get_app_Position_actual_value());
        // TODO: 自动保存回零偏移值
        return APP_RET_SUCCESS;
    }

    return APP_RET_RUNNING;
}

AppResult HomingModeStop()
{
    return APP_RET_SUCCESS;
}
