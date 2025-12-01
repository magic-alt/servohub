#ifndef APP_TRAJECTORY_H
#define APP_TRAJECTORY_H

#include "app_data_type_define.h"
#include "motor_ctl_sm.h"

void PosTrajectoryPlanningInit(void);
void PosTrajectoryPlanningHandle(POS_TRAJECTORY_DATA *pos_traj_data);

void SpeedTrajectoryPlanningInit(void);
void SpeedTrajectoryPlanningHandle(SPEED_TRAJECTORY_DATA *speed_traj_data);

void TorqueTrajectoryPlanningInit(void);
void TorqueTrajectoryPlanningHandle(TORQUE_TRAJECTORY_DATA *torque_traj_data);

void MitTrajectoryPlanningInit(MIT_TRAJECTORY_DATA *mit_traj_data);
void MitTrajectoryPlanningHandle(MIT_TRAJECTORY_DATA *mit_traj_data);

#endif // APP_TRAJECTORY_H
