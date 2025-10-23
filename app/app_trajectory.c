#include "app_trajectory.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis;

pos_trajectory_planning_DW_f kPosTrajDw;
linear_trajectory_planning_DW_f kTorqueTrajDw;
linear_trajectory_planning_DW_f kSpeedTrajDw;

// 位置轨迹规划器初始化
void pos_trajectory_planning_init(void)
{
    memset(&kPosTrajDw, 0, sizeof(kPosTrajDw));

    // 初始化当前规划器 为当前速度  当前位置
    kPosTrajDw.q0_int = axis->pos_speed_ctl_input.pos_now_p;
    kPosTrajDw.x = axis->pos_speed_ctl_input.pos_now_p;
    kPosTrajDw.q0_dec = 0;
    kPosTrajDw.dq0 = axis->pos_speed_ctl_input.speed_now_rad_s /
                     MOTOR_CTL_SM_TWO_PI * axis->pmsm_config.enc_line_p_n; // 从当前速度开始规划  p/s
}

// 位置轨迹规划器处理函数
void pos_trajectory_planning_handle(POS_TRAJECTORY_DATA *pos_traj_data)
{
    int8_T state_now = 0;
    pos_traj_data->period_s = axis->pmsm_config.tp_s;

    pos_trajectory_planning(&pos_traj_data->pos_tar_p,
                            &pos_traj_data->profile_speed,
                            &pos_traj_data->profile_acc,
                            &pos_traj_data->profile_dec,
                            &pos_traj_data->period_s,
                            &axis->input_shaping_input.pos_cmd_p,
                            &pos_traj_data->pos_out_dec_p,
                            &axis->pos_speed_ctl_input.speed_tar_p_s,
                            &axis->pos_speed_ctl_input.acc_tar_p_ss,
                            &state_now, &kPosTrajDw);
}

// 速度轨迹规划器初始化
void speed_trajectory_planning_init(void)
{
    memset(&kSpeedTrajDw, 0, sizeof(kSpeedTrajDw));
    kSpeedTrajDw.traj_now = axis->pos_speed_ctl_input.speed_now_rad_s /
                            MOTOR_CTL_SM_TWO_PI * axis->pmsm_config.enc_line_p_n; // 从当前速度开始规划  p/s
}

// 速度轨迹规划器处理函数
void speed_trajectory_planning_handle(SPEED_TRAJECTORY_DATA *speed_traj_data)
{
    int8_T state_now = 0;
    speed_traj_data->period_s = axis->pmsm_config.tp_s;

    linear_trajectory_planning(&speed_traj_data->speed_tar_p,
                               &speed_traj_data->acc,
                               &speed_traj_data->period_s,
                               &axis->pos_speed_ctl_input.speed_tar_p_s,
                               &state_now, &(kSpeedTrajDw));
}

// 转矩轨迹规划器初始化
void torque_trajectory_planning_init(void)
{
    memset(&kTorqueTrajDw, 0, sizeof(kTorqueTrajDw));
    // 初始化当前规划器 为当前 q轴电流
    kTorqueTrajDw.traj_now = axis->current_ctl_output.idq_now_A[1];
}

// 转矩轨迹规划器处理函数
void torque_trajectory_planning_handle(TORQUE_TRAJECTORY_DATA *torque_traj_data)
{
    int8_T state_now = 0;
    torque_traj_data->period_s = axis->pmsm_config.tp_s;

    linear_trajectory_planning(&torque_traj_data->torque_tar,
                               &torque_traj_data->slope,
                               &torque_traj_data->period_s,
                               &axis->current_ctl_input.idq_tar_A[1],
                               &state_now, &(kTorqueTrajDw));
}

void mit_trajectory_planning_init(MIT_TRAJECTORY_DATA *mit_traj_data)
{
    axis->mit_ctl_input.iq_max_A = mit_traj_data->iq_max_A;
}

void mit_trajectory_planning_handle(MIT_TRAJECTORY_DATA *mit_traj_data)
{
    axis->mit_ctl_input.pos_tar_p = mit_traj_data->pos_tar_p;
    axis->mit_ctl_input.speed_tar_p_s = mit_traj_data->speed_tar_p_s;
    axis->mit_ctl_input.tq_set_A = mit_traj_data->tq_set_A;
    axis->mit_ctl_config.kp_pos_rad_A = mit_traj_data->kp_pos_rad_A;
    axis->mit_ctl_config.kd_spd_rad_s_A = mit_traj_data->kd_spd_rad_s_A;
}
