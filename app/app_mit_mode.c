#include "app_mit_mode.h"

static MitMode_t mit_mode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj =
    {
        .kp_pos_rad_NM = 0,
        .kd_spd_rad_s_NM = 0,
        .iq_max_A = 0,
        .speed_tar_p_s = 0,
        .pos_tar_p = 0,
        .tq_set_NM = 0,
    },
    .check_status_val = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .pos_tar_p_add = 0,
};

AppResult mit_mode_init()
{
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    mit_mode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult mit_mode_start()
{
    return APP_RET_SUCCESS;
}

AppResult mit_mode_run()
{
    int64_t pos_tar_p_add = 0;

    mit_mode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (mit_mode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (mit_mode.pre_Controlword == APP_CTRL_DISABLE)
        {
            // 重新使能后初始化规划器
            mit_mode.traj.iq_max_A = get_app_MIT_max_current();
            mit_trajectory_planning_init(&mit_mode.traj);
        }

        if (get_app_Halt_running_cmd() == true)
        {
            mit_mode.traj.speed_tar_p_s = 0;
        }
        else
        {
            mit_mode.traj.speed_tar_p_s = get_app_MIT_target_velocity() * get_app_Load_rpm_2_pps() * \
                                            get_app_Reduction_ratio();
        }
        mit_mode.pos_tar_p_add = (float)(get_app_MIT_target_position() - get_app_Position_actual_value()) * \
                                    get_app_Reduction_ratio();
        mit_mode.traj.pos_tar_p = mit_mode.pos_tar_p_add + get_app_Motor_position_actual_value();
        mit_mode.traj.tq_set_NM = get_app_MIT_feedforward_torque() * get_app_Reduction_ratio_inv();  //负载端转矩  转化 为电机端
        mit_mode.traj.kp_pos_rad_NM = get_app_MIT_kp() * get_app_Reduction_ratio_inv();  // 转化为电机端增益
        mit_mode.traj.kd_spd_rad_s_NM = get_app_MIT_kd() * get_app_Reduction_ratio_inv();  // 转化为电机端增益
    }
    else if (mit_mode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        mit_mode.traj.speed_tar_p_s = 0; // 如果处于急停状态，规划速度为0

        mit_mode.emergency_brake_mode = get_app_Quick_stop_option_code();
        // 在急停后失能电机模式下，检测到零速后电机失能
        if (mit_mode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            mit_mode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (mit_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||\
                mit_mode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                mit_mode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (mit_mode.now_Controlword != APP_CTRL_DISABLE)
    {
        mit_trajectory_planning_handle(&mit_mode.traj);
    }

    mit_mode.pre_Controlword = mit_mode.now_Controlword;

    return APP_RET_RUNNING;
}

AppResult mit_mode_stop()
{
    return APP_RET_SUCCESS;
}
