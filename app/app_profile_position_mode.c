#include "app_profile_position_mode.h"

static PpMode_t pp_mode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj = {
        .pos_tar_p = 0,
        .profile_speed = 0,
        .profile_acc = 0,
        .profile_dec = 0,
        .period_s = 0,
        .pos_out_dec_p = 0,
    },
    .check_status_val = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .start_upedge_latch = false,
    .start_upedge_state = false,
    .position_target_last = 0,
    .pos_tar_p_add = 0,
};

AppResult pp_mode_init()
{
    app_position_target_reached_state_clear(); // 清除目标到达标志
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    pp_mode.pre_Controlword = APP_CTRL_DISABLE;
    pp_mode.start_upedge_latch = false;
    pp_mode.start_upedge_state = false;
    pp_mode.position_target_last = get_app_Position_actual_value();

    return APP_RET_SUCCESS;
}

AppResult pp_mode_start()
{
    return APP_RET_SUCCESS;
}

AppResult pp_mode_run()
{
    pp_mode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (pp_mode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (pp_mode.pre_Controlword == APP_CTRL_DISABLE)
        {
            // 重新使能后初始化规划器
            pos_trajectory_planning_init();
            pp_mode.position_target_last = get_app_Position_actual_value(); // 目标位置 等于 当前位置
            pp_mode.traj.pos_tar_p = get_app_Motor_position_actual_value();
        }

        // 总线控制时pp模式下检测控制字bit4上升沿事件，或，非总线控制时bit4上升沿事件一直有效更新目标位置
        if (pp_mode.start_upedge_state == true ||\
            (APP_COMM_CONTROL_AUTHORITY)get_app_Comm_control_authority() == COMM_CONTROL_HOST)
        {
            pp_mode.start_upedge_latch = true;
            pp_mode.start_upedge_state = false;
        }

        if (get_app_Halt_running_cmd() == true)
        {
            pp_mode.start_upedge_latch = false; // 暂停后重新使能
            pp_mode.traj.profile_speed = 0; // 如果处于暂停状态，规划速度为0
        }
        else
        {
            pp_mode.traj.profile_speed = get_app_Profile_velocity() * get_app_Load_rpm_2_pps() * \
                                            get_app_Reduction_ratio();
        }

        // 设置规划器参数
        // 计算目标位置和当前位置差值
        if (true == pp_mode.start_upedge_latch)
        {
            pp_mode.start_upedge_latch = false;
            pp_mode.position_target_last = get_app_Target_position(); // 上升沿更新目标位置
        }

        pp_mode.pos_tar_p_add = (float)(pp_mode.position_target_last - get_app_Position_actual_value()) * \
                                get_app_Reduction_ratio();
        pp_mode.traj.pos_tar_p = pp_mode.pos_tar_p_add + get_app_Motor_position_actual_value(); //  转化到内环目标位置

        pp_mode.traj.profile_acc = get_app_Profile_acceleration() * get_app_Load_rpm_2_pps() * \
                                    get_app_Reduction_ratio();
        pp_mode.traj.profile_dec = get_app_Profile_deceleration() * get_app_Load_rpm_2_pps() * \
                                    get_app_Reduction_ratio();

    }
    else if (pp_mode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        pp_mode.traj.profile_speed = 0; // 如果处于急停状态，规划速度为0

        pp_mode.emergency_brake_mode = get_app_Quick_stop_option_code();
        if (pp_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP ||\
            pp_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP_ENABLE ||\
            pp_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT ||\
            pp_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT_ENABLE)
        {
            pp_mode.traj.profile_acc = get_app_Quick_stop_deceleration() * get_app_Load_rpm_2_pps() * \
                                        get_app_Reduction_ratio();
            pp_mode.traj.profile_dec = pp_mode.traj.profile_acc;
        }
        else if (pp_mode.emergency_brake_mode != EMERGENCY_BRAKE_MODE_DISABLED)
        {
            //TODO: 电压限制急停先不实现按正常减速斜率停机
            pp_mode.traj.profile_acc = get_app_Profile_acceleration() * get_app_Load_rpm_2_pps() * \
                                        get_app_Reduction_ratio();
            pp_mode.traj.profile_dec = get_app_Profile_deceleration() * get_app_Load_rpm_2_pps() * \
                                        get_app_Reduction_ratio();
        }
        // 在急停后失能电机模式下，检测到零速后电机失能
        if (pp_mode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            pp_mode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (pp_mode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||\
                pp_mode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                pp_mode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (pp_mode.now_Controlword != APP_CTRL_DISABLE)
    {
        pos_trajectory_planning_handle(&pp_mode.traj);
    }

    pp_mode.pre_Controlword = pp_mode.now_Controlword;

    app_position_target_reached_state_check();

    return APP_RET_RUNNING;
}

AppResult pp_mode_stop()
{
    pp_mode.start_upedge_state = false;
    pp_mode.start_upedge_latch = false;

    return APP_RET_SUCCESS;
}

void set_app_g_start_upedge_state(bool state)
{
    pp_mode.start_upedge_state = state;
}
