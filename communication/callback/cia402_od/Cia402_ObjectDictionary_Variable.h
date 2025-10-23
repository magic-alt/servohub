#pragma once

#include <stdint.h>

typedef int8_t INTEGER8;
typedef int16_t INTEGER16;
typedef int32_t INTEGER32;
typedef uint8_t UNS8;
typedef uint16_t UNS16;
typedef uint32_t UNS32;

#define ABORT_CODE_SUCCESSFUL               (0x00000000)
#define ABORT_CODE_UNSUPPORTED_ACCESS       (0x06010000) //Unsupported access to an object
#define ABORT_CODE_CANNOT_READ_WO_OBJECT    (0x06010001) //Attempt to read a write only object
#define ABORT_CODE_CANNOT_WRITE_RO_OBJECT   (0x06010002) //Attempt to write a read only object
#define ABORT_CODE_SUB_INDEX_NOT_EXIST      (0x06090011) //Sub-index does not exist
#define ABORT_CODE_VALUE_TOO_HIGH           (0x06090031) //Value of parameter written too high
#define ABORT_CODE_VALUE_TOO_LOW            (0x06090032) //Value of parameter written too low
#define ABORT_CODE_DRIVE_STATE_DENIED       (0x08000022) //Data cannot be transferred or stored to the application because of the present device state

typedef struct
{
    UNS16 Controlword; //402控制字
    UNS16 Statusword; //402状态字
    UNS16 Error_code; //错误码
    INTEGER16 Quick_stop_option_code; //快速停止操作代码
    INTEGER8 Modes_of_operation; //运行模式
    INTEGER8 Modes_of_operation_display; //显示运行模式
}PDS_FSA;

typedef struct
{
    UNS8 Position_encoder_resolution;
    UNS32 Position_encoder_resolution_Encoder_increments; //负载端位置反馈分辨率
    UNS32 Position_encoder_resolution_Motor_revolutions; //电机端位置反馈分辨率
    UNS8 Gear_ratio;
    UNS32 Motor_revolutions; //齿轮比分母
    UNS32 Shaft_revolutions; //齿轮比分子
    UNS8 Polarity; //运动极性
}Factor_group;

typedef struct
{
    INTEGER32 Target_position; //位置目标值
    UNS8 Position_range_limit;
    INTEGER32 Position_range_limit_Minimal_position_limit; //位置溢出最小值
    INTEGER32 Position_range_limit_Maximal_position_limit; //位置溢出最大值
    UNS8 Software_position_limit;
    INTEGER32 Software_position_limit_Minimal_position_limit; //应用位置下限
    INTEGER32 Software_position_limit_Maximal_position_limit; //应用位置上限
    UNS32 Max_Profile_velocity; //应用速度限制
    UNS32 Max_motor_speed; //电机最大转速
    UNS32 Profile_velocity; //轮廓速度
    UNS32 Profile_acceleration; //轮廓加速度
    UNS32 Profile_deceleration; //轮廓减速度
    UNS32 Quick_stop_deceleration; //快速停止减速度
    UNS32 Max_acceleration; //应用加速度限制
    UNS32 Max_deceleration; //应用减速度限制
}Profile_position_mode;

typedef struct
{
    INTEGER8 Homing_method; //回零方法
}Homing_mode;

typedef struct
{
    INTEGER32 Position_demand_value; //负载端位置指令值
    INTEGER32 Position_actual_value_inc; //负载端内部位置当前值
    INTEGER32 Position_actual_value; //负载端位置当前值
    UNS32 Following_error_window; //位置跟随误差阈值
    UNS16 Following_error_time_Out; //位置跟随误差阈值时间
    UNS32 Position_window; //位置到达检测窗口
    UNS16 Position_window_time; //位置到达检测窗口时间
    INTEGER32 Following_error_actual_value; //负载端位置误差值
}Position_control_function;

typedef struct
{
    INTEGER32 Velocity_demand_value; //负载端速度指令值
    INTEGER32 Velocity_actual_value; //负载端速度当前值
    UNS16 Velocity_window; //速度到达检测窗口
    UNS16 Velocity_window_time; //速度到达检测窗口时间
    UNS16 Velocity_threshold; //零速检测窗口
    UNS16 Velocity_threshold_time; //零速检测窗口时间
    INTEGER32 Target_velocity; //速度目标值
}Profile_velocity_mode;

typedef struct
{
    INTEGER16 Target_torque; //力矩目标值
    UNS16 Max_torque; //应用力矩限制相对值
    UNS16 Max_current; //应用电流限制相对值
    INTEGER16 Torque_demand_value; //力矩指令值
    UNS32 Motor_rated_current; //电机额定电流
    UNS32 Motor_rated_torque; //电机额定力矩/推力
    INTEGER16 Torque_actual_value; //力矩当前值
    INTEGER16 Current_actual_value; //电流当前值
    UNS32 DC_link_circuit_voltage; //母线电压当前值
    UNS32 Torque_slope; //力矩上升斜率
}Profile_torque_mode;

typedef struct
{
    UNS32 Alarm_word; //告警字
    INTEGER32 MIT_feedforward_torque_current; //MIT前馈力矩电流
    INTEGER32 MIT_target_position; //MIT目标位置
    INTEGER32 MIT_max_current; //MIT最大输出电流
    INTEGER32 MIT_target_velocity; //MIT目标速度
    UNS32 MIT_Kp; //位置刚度
    UNS32 MIT_Kd; //速度阻尼系数
    UNS8 SysCmd; //系统指令
    INTEGER8 storage_status; //Flash存储状态
    UNS16 Notch_filter_frq[6]; //陷波滤波器频率
    UNS16 Notch_filter_width[6]; //陷波滤波器宽度
    UNS16 Notch_filter_depth[6]; //陷波滤波器深度
    UNS16 Input_shaping_wn; //末端振动抑制的频率
    UNS16 Pos_speed_ctl_aff; //加速度前馈系数
    UNS16 Pos_speed_ctl_vff; //速度前馈系数
    UNS32 Pos_speed_ctl_j_kt; //惯性系数
    UNS32 Pos_speed_ctl_ki_s; //速度环积分系数
    UNS16 Pos_speed_ctl_kp_p; //位置环比例系数
    UNS32 Pos_speed_ctl_kp_s; //速度环比例系数
    UNS16 Pos_speed_ctl_dob_wn; //负载扰动观测器带宽
    UNS8 Pos_speed_ctl_dob_enable; //负载扰动观测使能开关
    UNS16 Current_ctl_i_noise; //电流采样噪声绝对值
    UNS16 Current_ctl_comp_du; //死区补偿电压大小
    UNS16 Current_ctl_bandwidth_percentage; //电流环目标带宽
    UNS16 Current_ctl_kp_ld; //d轴 kp控制增益
    UNS16 Current_ctl_ki_ld; //d轴 ki控制增益
    UNS16 Current_ctl_kp_lq; //q轴 kp控制增益
    UNS16 Current_ctl_ki_lq; //q轴 ki控制增益
    UNS16 Speed_obs_pll_wn; //速度观测带宽
}Manufacturer;

UNS32 set_Controlword(UNS16 val);
UNS16 get_Controlword(void);

UNS32 set_Statusword(UNS16 val);
UNS16 get_Statusword(void);

UNS32 set_Error_code(UNS16 val);
UNS16 get_Error_code(void);

UNS32 set_Quick_stop_option_code(INTEGER16 val);
INTEGER16 get_Quick_stop_option_code(void);

UNS32 set_Modes_of_operation(INTEGER8 val);
INTEGER8 get_Modes_of_operation(void);

UNS32 set_Modes_of_operation_display(INTEGER8 val);
INTEGER8 get_Modes_of_operation_display(void);

UNS32 set_Position_encoder_resolution(UNS8 val);
UNS8 get_Position_encoder_resolution(void);

UNS32 set_Position_encoder_resolution_Encoder_increments(UNS32 val);
UNS32 get_Position_encoder_resolution_Encoder_increments(void);

UNS32 set_Position_encoder_resolution_Motor_revolutions(UNS32 val);
UNS32 get_Position_encoder_resolution_Motor_revolutions(void);

UNS32 set_Gear_ratio(UNS8 val);
UNS8 get_Gear_ratio(void);

UNS32 set_Motor_revolutions(UNS32 val);
UNS32 get_Motor_revolutions(void);

UNS32 set_Shaft_revolutions(UNS32 val);
UNS32 get_Shaft_revolutions(void);

UNS32 set_Polarity(UNS8 val);
UNS8 get_Polarity(void);

UNS32 set_Target_position(INTEGER32 val);
INTEGER32 get_Target_position(void);

UNS32 set_Position_range_limit(UNS8 val);
UNS8 get_Position_range_limit(void);

UNS32 set_Position_range_limit_Minimal_position_limit(INTEGER32 val);
INTEGER32 get_Position_range_limit_Minimal_position_limit(void);

UNS32 set_Position_range_limit_Maximal_position_limit(INTEGER32 val);
INTEGER32 get_Position_range_limit_Maximal_position_limit(void);

UNS32 set_Software_position_limit(UNS8 val);
UNS8 get_Software_position_limit(void);

UNS32 set_Software_position_limit_Minimal_position_limit(INTEGER32 val);
INTEGER32 get_Software_position_limit_Minimal_position_limit(void);

UNS32 set_Software_position_limit_Maximal_position_limit(INTEGER32 val);
INTEGER32 get_Software_position_limit_Maximal_position_limit(void);

UNS32 set_Max_Profile_velocity(UNS32 val);
UNS32 get_Max_Profile_velocity(void);

UNS32 set_Max_motor_speed(UNS32 val);
UNS32 get_Max_motor_speed(void);

UNS32 set_Profile_velocity(UNS32 val);
UNS32 get_Profile_velocity(void);

UNS32 set_Profile_acceleration(UNS32 val);
UNS32 get_Profile_acceleration(void);

UNS32 set_Profile_deceleration(UNS32 val);
UNS32 get_Profile_deceleration(void);

UNS32 set_Quick_stop_deceleration(UNS32 val);
UNS32 get_Quick_stop_deceleration(void);

UNS32 set_Max_acceleration(UNS32 val);
UNS32 get_Max_acceleration(void);

UNS32 set_Max_deceleration(UNS32 val);
UNS32 get_Max_deceleration(void);

UNS32 set_Homing_method(INTEGER8 val);
INTEGER8 get_Homing_method(void);

UNS32 set_Position_demand_value(INTEGER32 val);
INTEGER32 get_Position_demand_value(void);

UNS32 set_Position_actual_value_inc(INTEGER32 val);
INTEGER32 get_Position_actual_value_inc(void);

UNS32 set_Position_actual_value(INTEGER32 val);
INTEGER32 get_Position_actual_value(void);

UNS32 set_Following_error_window(UNS32 val);
UNS32 get_Following_error_window(void);

UNS32 set_Following_error_time_Out(UNS16 val);
UNS16 get_Following_error_time_Out(void);

UNS32 set_Position_window(UNS32 val);
UNS32 get_Position_window(void);

UNS32 set_Position_window_time(UNS16 val);
UNS16 get_Position_window_time(void);

UNS32 set_Following_error_actual_value(INTEGER32 val);
INTEGER32 get_Following_error_actual_value(void);

UNS32 set_Velocity_demand_value(INTEGER32 val);
INTEGER32 get_Velocity_demand_value(void);

UNS32 set_Velocity_actual_value(INTEGER32 val);
INTEGER32 get_Velocity_actual_value(void);

UNS32 set_Velocity_window(UNS16 val);
UNS16 get_Velocity_window(void);

UNS32 set_Velocity_window_time(UNS16 val);
UNS16 get_Velocity_window_time(void);

UNS32 set_Velocity_threshold(UNS16 val);
UNS16 get_Velocity_threshold(void);

UNS32 set_Velocity_threshold_time(UNS16 val);
UNS16 get_Velocity_threshold_time(void);

UNS32 set_Target_velocity(INTEGER32 val);
INTEGER32 get_Target_velocity(void);

UNS32 set_Target_torque(INTEGER16 val);
INTEGER16 get_Target_torque(void);

UNS32 set_Max_torque(UNS16 val);
UNS16 get_Max_torque(void);

UNS32 set_Max_current(UNS16 val);
UNS16 get_Max_current(void);

UNS32 set_Torque_demand_value(INTEGER16 val);
INTEGER16 get_Torque_demand_value(void);

UNS32 set_Motor_rated_current(UNS32 val);
UNS32 get_Motor_rated_current(void);

UNS32 set_Motor_rated_torque(UNS32 val);
UNS32 get_Motor_rated_torque(void);

UNS32 set_Torque_actual_value(INTEGER16 val);
INTEGER16 get_Torque_actual_value(void);

UNS32 set_Current_actual_value(INTEGER16 val);
INTEGER16 get_Current_actual_value(void);

UNS32 set_DC_link_circuit_voltage(UNS32 val);
UNS32 get_DC_link_circuit_voltage(void);

UNS32 set_Torque_slope(UNS32 val);
UNS32 get_Torque_slope(void);

UNS32 set_Alarm_word(UNS32 val);
UNS32 get_Alarm_word(void);

UNS32 set_MIT_feedforward_torque_current(INTEGER32 val);
INTEGER32 get_MIT_feedforward_torque_current(void);

UNS32 set_MIT_target_position(INTEGER32 val);
INTEGER32 get_MIT_target_position(void);

UNS32 set_MIT_max_current(INTEGER32 val);
INTEGER32 get_MIT_max_current(void);

UNS32 set_MIT_target_velocity(INTEGER32 val);
INTEGER32 get_MIT_target_velocity(void);

UNS32 set_MIT_Kp(UNS32 val);
UNS32 get_MIT_Kp(void);

UNS32 set_MIT_Kd(UNS32 val);
UNS32 get_MIT_Kd(void);

UNS32 set_SysCmd(UNS8 val);
UNS8 get_SysCmd(void);

UNS32 set_storage_status(INTEGER8 val);
INTEGER8 get_storage_status(void);

UNS32 set_Notch_filter_frq(uint8_t subindex, UNS16 val);
UNS16 get_Notch_filter_frq(uint8_t subindex);

UNS32 set_Notch_filter_width(uint8_t subindex, UNS16 val);
UNS16 get_Notch_filter_width(uint8_t subindex);

UNS32 set_Notch_filter_depth(uint8_t subindex, UNS16 val);
UNS16 get_Notch_filter_depth(uint8_t subindex);

UNS32 set_Input_shaping_wn(UNS16 val);
UNS16 get_Input_shaping_wn(void);

UNS32 set_Pos_speed_ctl_aff(UNS16 val);
UNS16 get_Pos_speed_ctl_aff(void);

UNS32 set_Pos_speed_ctl_vff(UNS16 val);
UNS16 get_Pos_speed_ctl_vff(void);

UNS32 set_Pos_speed_ctl_j_kt(UNS32 val);
UNS32 get_Pos_speed_ctl_j_kt(void);

UNS32 set_Pos_speed_ctl_ki_s(UNS32 val);
UNS32 get_Pos_speed_ctl_ki_s(void);

UNS32 set_Pos_speed_ctl_kp_p(UNS16 val);
UNS16 get_Pos_speed_ctl_kp_p(void);

UNS32 set_Pos_speed_ctl_kp_s(UNS32 val);
UNS32 get_Pos_speed_ctl_kp_s(void);

UNS32 set_Pos_speed_ctl_dob_wn(UNS16 val);
UNS16 get_Pos_speed_ctl_dob_wn(void);

UNS32 set_Pos_speed_ctl_dob_enable(UNS8 val);
UNS8 get_Pos_speed_ctl_dob_enable(void);

UNS32 set_Current_ctl_i_noise(UNS16 val);
UNS16 get_Current_ctl_i_noise(void);

UNS32 set_Current_ctl_comp_du(UNS16 val);
UNS16 get_Current_ctl_comp_du(void);

UNS32 set_Current_ctl_bandwidth_percentage(UNS16 val);
UNS16 get_Current_ctl_bandwidth_percentage(void);

UNS32 set_Current_ctl_kp_ld(UNS16 val);
UNS16 get_Current_ctl_kp_ld(void);

UNS32 set_Current_ctl_ki_ld(UNS16 val);
UNS16 get_Current_ctl_ki_ld(void);

UNS32 set_Current_ctl_kp_lq(UNS16 val);
UNS16 get_Current_ctl_kp_lq(void);

UNS32 set_Current_ctl_ki_lq(UNS16 val);
UNS16 get_Current_ctl_ki_lq(void);

UNS32 set_Speed_obs_pll_wn(UNS16 val);
UNS16 get_Speed_obs_pll_wn(void);

