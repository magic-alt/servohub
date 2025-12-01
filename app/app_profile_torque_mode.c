#include "app_profile_torque_mode.h"

static PtMode_t pt_mode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj = {
        .torque_tar = 0,
        .slope = 0,
        .period_s = 0,
    },
    .check_status_val = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
};

AppResult pt_mode_init()
{
    AppTargetTorqueReachedStateClear();
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    pt_mode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult pt_mode_start()
{
    return APP_RET_SUCCESS;
}

AppResult pt_mode_run()
{
    pt_mode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (pt_mode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (pt_mode.pre_Controlword == APP_CTRL_DISABLE)
        {
            // 重新使能后初始化规划器
            torque_trajectory_planning_init();
        }

        if (get_app_Halt_running_cmd() == true)
        {
            pt_mode.traj.torque_tar = 0;
        }
        else
        {
            pt_mode.traj.torque_tar = get_app_Target_torque();
            pt_mode.traj.slope = get_app_Torque_slope();
        }
    }
    else if (pt_mode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        pt_mode.traj.torque_tar = 0; // 如果处于急停状态，规划器目标力矩为0

        pt_mode.emergency_brake_mode = get_app_Quick_stop_option_code();
        // 在急停后失能电机模式下，直接电机失能
        if (pt_mode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            set_app_Controlword(APP_CTRL_DISABLE);
            pt_mode.now_Controlword = APP_CTRL_DISABLE;
        }
    }

    if (pt_mode.now_Controlword != APP_CTRL_DISABLE)
    {
        torque_trajectory_planning_handle(&pt_mode.traj);
    }

    pt_mode.pre_Controlword = pt_mode.now_Controlword;

    AppTargetTorqueReachedStateCheck();

    return APP_RET_RUNNING;
}

AppResult pt_mode_stop()
{
    return APP_RET_SUCCESS;
}
