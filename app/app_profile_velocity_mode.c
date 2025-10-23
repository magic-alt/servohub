#include "app_profile_velocity_mode.h"
#include "yuanhub_math.h"

static PvMode_t pv_mode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj = {
        .speed_tar_p = 0,
        .acc = 0,
        .period_s = 0,
    },
    .check_status_val = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .velocity_target = 0,
};

AppResult pv_mode_init()
{
    app_velocity_target_reached_state_clear();
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    pv_mode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult pv_mode_start()
{
    return APP_RET_SUCCESS;
}

AppResult pv_mode_run()
{
    pv_mode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (pv_mode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (pv_mode.pre_Controlword == APP_CTRL_DISABLE)
        {
            // 重新使能后初始化规划器
            speed_trajectory_planning_init();
        }

        pv_mode.velocity_target = get_app_Target_velocity();

        if (get_app_Halt_running_cmd() == true)
        {
            pv_mode.traj.speed_tar_p = 0;
        }
        else
        {
            pv_mode.traj.speed_tar_p = pv_mode.velocity_target * get_app_Load_rpm_2_pps() * \
                                        get_app_Reduction_ratio();
        }

        // 轮廓加速度减速度切换 目标速度绝对值 大于 当前规划速度绝对值加速 否则则加速
        if (MATH_ABS(pv_mode.velocity_target) > MATH_ABS(get_app_Velocity_demand_value()))
        {
            pv_mode.traj.acc = get_app_Profile_acceleration() * get_app_Load_rpm_2_pps() * \
                                get_app_Reduction_ratio();
        }
        else
        {
            pv_mode.traj.acc = get_app_Profile_deceleration() * get_app_Load_rpm_2_pps() * \
                                get_app_Reduction_ratio();
        }
    }
    else if (pv_mode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        pv_mode.traj.speed_tar_p = 0; // 如果处于急停状态，规划速度为0
        pv_mode.emergency_brake_mode = get_app_Quick_stop_option_code();
        if (pv_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP ||\
            pv_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP_ENABLE ||\
            pv_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT ||\
            pv_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT_ENABLE)
        {
            pv_mode.traj.acc = get_app_Quick_stop_deceleration() * get_app_Load_rpm_2_pps() * \
                                get_app_Reduction_ratio();
        }
        else if (pv_mode.emergency_brake_mode != EMERGENCY_BRAKE_MODE_DISABLED)
        {
            //TODO: 电压限制急停先不实现按正常减速斜率停机
            pv_mode.traj.acc = get_app_Profile_deceleration() * get_app_Load_rpm_2_pps() * \
                                get_app_Reduction_ratio();
        }
        // 在急停后失能电机模式下，检测到零速后电机失能
        if (pv_mode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            pv_mode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (pv_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||\
                pv_mode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                pv_mode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (pv_mode.now_Controlword != APP_CTRL_DISABLE)
    {
        speed_trajectory_planning_handle(&pv_mode.traj);
    }

    pv_mode.pre_Controlword = pv_mode.now_Controlword;

    app_velocity_target_reached_state_check();

    return APP_RET_RUNNING;
}

AppResult pv_mode_stop()
{
    return APP_RET_SUCCESS;
}
