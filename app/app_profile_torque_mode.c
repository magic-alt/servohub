#include "app_profile_torque_mode.h"

static PtMode_t kPtMode =
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

AppResult PtModeInit()
{
    AppTargetTorqueReachedStateClear();
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    kPtMode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult PtModeStart()
{
    return APP_RET_SUCCESS;
}

AppResult PtModeRun()
{
    kPtMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (kPtMode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (kPtMode.pre_Controlword == APP_CTRL_DISABLE)
        {
            // 重新使能后初始化规划器
            TorqueTrajectoryPlanningInit();
        }

        if (get_app_Halt_running_cmd() == true)
        {
            kPtMode.traj.torque_tar = 0;
        }
        else
        {
            kPtMode.traj.torque_tar = get_app_Target_torque();
            kPtMode.traj.slope = get_app_Torque_slope();
        }
    }
    else if (kPtMode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        kPtMode.traj.torque_tar = 0; // 如果处于急停状态，规划器目标力矩为0

        kPtMode.emergency_brake_mode = get_app_Quick_stop_option_code();
        // 在急停后失能电机模式下，直接电机失能
        if (kPtMode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            set_app_Controlword(APP_CTRL_DISABLE);
            kPtMode.now_Controlword = APP_CTRL_DISABLE;
        }
    }

    if (kPtMode.now_Controlword != APP_CTRL_DISABLE)
    {
        TorqueTrajectoryPlanningHandle(&kPtMode.traj);
    }

    kPtMode.pre_Controlword = kPtMode.now_Controlword;

    AppTargetTorqueReachedStateCheck();

    return APP_RET_RUNNING;
}

AppResult PtModeStop()
{
    return APP_RET_SUCCESS;
}
