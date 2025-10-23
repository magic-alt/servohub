#ifndef APP_TRAJECTORY_H
#define APP_TRAJECTORY_H

#include "app_data_type_define.h"
#include "motor_ctl_sm.h"

void pos_trajectory_planning_init(void);
void pos_trajectory_planning_handle(POS_TRAJECTORY_DATA *pos_traj_data);

void speed_trajectory_planning_init(void);
void speed_trajectory_planning_handle(SPEED_TRAJECTORY_DATA *speed_traj_data);

void torque_trajectory_planning_init(void);
void torque_trajectory_planning_handle(TORQUE_TRAJECTORY_DATA *torque_traj_data);

void mit_trajectory_planning_init(MIT_TRAJECTORY_DATA *mit_traj_data);
void mit_trajectory_planning_handle(MIT_TRAJECTORY_DATA *mit_traj_data);

#endif // APP_TRAJECTORY_H
