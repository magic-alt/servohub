#include "app_homing_mode.h"

static HomingMode_t hm_mode =
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

AppResult hm_mode_init()
{
    app_velocity_target_reached_state_clear();
    set_app_Controlword(APP_CTRL_DISABLE);
    hm_mode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult hm_mode_start()
{
    return APP_RET_SUCCESS;
}

AppResult hm_mode_run()
{
    hm_mode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (hm_mode.now_Controlword == APP_CTRL_ENABLE)
    {
        // 仅考虑35号回零模式，最终使用负载端的位置信息
        if (hm_mode.pre_Controlword == APP_CTRL_DISABLE)
        {
            // 重新使能后初始化规划器
            speed_trajectory_planning_init();
        }

        if (get_app_Halt_running_cmd() == true)
        {
            hm_mode.traj.speed_tar_p = 0;
        }
        else
        {
            hm_mode.traj.speed_tar_p = 0;       //仅考虑35号回零模式，其他回零模式设置为回零加速度
        }
        hm_mode.traj.acc = 0;                   //仅考虑35号回零模式，其他回零模式设置为对应搜索速度
    }

    if (hm_mode.now_Controlword != APP_CTRL_DISABLE)
    {
        speed_trajectory_planning_handle(&hm_mode.traj);
    }

    hm_mode.pre_Controlword = hm_mode.now_Controlword;

    app_velocity_target_reached_state_check();

    // 单独处理35号回零模式
    if (hm_mode.now_Controlword == APP_CTRL_ENABLE && get_app_Homing_method() == 35)
    {
        volatile int64_t offset_last = get_app_Home_position_offset_value();
        set_app_Home_position_offset_value(offset_last + get_app_Position_actual_value());
        // TODO: 自动保存回零偏移值
        return APP_RET_SUCCESS;
    }

    return APP_RET_RUNNING;
}

AppResult hm_mode_stop()
{
    return APP_RET_SUCCESS;
}
