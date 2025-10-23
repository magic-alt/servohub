#ifndef APP_HOMING_MODE_H
#define APP_HOMING_MODE_H

#include "app_data_type_define.h"

#include "app_trajectory.h"
#include "app_status_check.h"

typedef struct
{
    APP_CONTROL_WORD now_Controlword;               // 当前控制字
    APP_CONTROL_WORD pre_Controlword;               // 前一次控制字
    SPEED_TRAJECTORY_DATA traj;                     // 回零模式使用速度规划器
} HomingMode_t;

AppResult hm_mode_init();
AppResult hm_mode_start();
AppResult hm_mode_run();
AppResult hm_mode_stop();

#endif // APP_HOMING_MODE_H
