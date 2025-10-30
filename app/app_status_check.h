#ifndef APP_STATUS_CHECK_H
#define APP_STATUS_CHECK_H

#include "app_data_type_define.h"

#include "bsp_api.h"


#define TASK_PERIOD_1MS         (0.001f)        // 1ms = 0.001s任务周期
#define DRIVE_OVER_PEAK_COOLING_TIME (30.0f)    // 30s
#define DC_BUS_UNDER_VOLTAGE_CHECK_TIME (0.2f)  // 欠压错误持续时间阈值
#define LED_NORMAL_STATE_PERIOD (500.0f)        // 正常状态持续时间ms
#define LED_ERROR_STATE_PERIOD  (100.0f)        // 错误状态持续时间ms

typedef union
{
    uint32_t all;
    struct
    {
        uint32_t drive_peak_current_overload : 1; // 驱动器峰值电流过载保护
        uint32_t drive_overload : 1;              // 驱动器过载保护
        uint32_t dc_bus_over_voltage : 1;         // 母线过压
        uint32_t dc_bus_under_voltage : 1;        // 母线欠压
        uint32_t over_temperature_drive : 1;      // 驱动器过温
        uint32_t under_temperature_drive : 1;     // 驱动器欠温
        uint32_t over_speed : 1;                  // 电机过速
        uint32_t position_following_error : 1;    // 位置误差过大

        uint32_t load_encoder_error : 1;          // 负载端编码器错误
        uint32_t motor_encoder_error : 1;         // 电机端码器错误
        uint32_t flash_store_error : 1;           // flash存储错误
        uint32_t drv_init_error : 1;              // drv初始化错误
        uint32_t current_sample_error : 1;        // 电流采样错误
        uint32_t nfault_error : 1;                // 硬件短路保护
        uint32_t drive_over_current_error : 1;    // 驱动器软件检测过流保护
        uint32_t drive_bus_voltage_error : 1;     // 母线电压检测异常

        uint32_t can_bus_disconnection_error : 1; // CAN总线掉线错误
        uint32_t over_temperature_motor : 1;      // 电机过温
        uint32_t under_temperature_motor : 1;     // 电机欠温
        uint32_t over_temperature_mcu : 1;        // MCU过温
        uint32_t under_temperature_mcu : 1;       // MCU欠温

        uint32_t reserved : 11;
    } bits; // 位字段
} CheckErrorCode_t;

typedef union
{
    uint32_t all;
    struct
    {
        uint32_t over_temperature_drive : 1;      // 驱动器过温警告
        uint32_t under_temperature_drive : 1;     // 驱动器欠温警告
        uint32_t over_temperature_motor : 1;      // 电机过温警告
        uint32_t under_temperature_motor : 1;     // 电机欠温警告
        uint32_t over_temperature_mcu : 1;        // MCU过温警告
        uint32_t under_temperature_mcu : 1;       // MCU欠温警告
        uint32_t motor_temperature_ntc : 1;       // 电机温度NTC异常警告

        uint32_t reserved : 25;
    } bits; // 位字段
} CheckWarningVal;

typedef struct {
    CheckErrorCode_t error;
    CheckWarningVal warning;
    CheckStatusVal_t status;
    BspErrorCode_t *p_bsp_error;

    uint8_t scan_ring_num;              // 检查函数轮询次数

    bool error_record_latch_flag;       // 错误记录锁存标志
    uint32_t *error_record_addr;        // 错误记录地址

    APP_CONTROL_WORD pre_ctrl_word;
    APP_CONTROL_WORD now_ctrl_word;

    // 初始化更新参数
    float dt;
    float dt_1ms;
    float idq_now[2];
    float idq_squared_now;
    float i_rated_squared;
    float i_peak_squared_threshold;
    float overload_heat_threshold_now;
    float drive_heat_now;
    float drive_temp_now;
    float motor_temp_now;
    float mcu_temp_now;
    float motor_rpm_now;
    float load_rpm_now;
    int64_t pos_error_now;
    int64_t pos_diff_now;
    float vel_diff_now;
    float trq_diff_now;
    float over_current_threshold;
    float iabc_now[3];
    uint32_t can_mg_counts_now;
    uint32_t can_mg_counts_last;
} AppCheckVal;

typedef bool (*CheckFunction)(void); // 定义检查函数指针类型
typedef struct {
    CheckFunction check_func;
    bool scan_fast;          // 是否在快速轮询中调用
}CheckFunctionList;

// 任务循环调用接口
void app_status_scan_init(void);
void app_status_scan_fast(void);        // 错误轮询检查函数  位置环调用
void app_status_scan_slow(void);        // 错误轮询检查函数  1ms任务调用
void app_status_check(void);            // 通用状态轮询检查函数  位置环调用
void app_led_state_updata_1ms(void);    // LED状态更新函数  1ms任务调用


// 获取错误、警告和状态值
uint32_t app_get_check_error_val(void);
uint32_t app_get_check_warning_val(void);
uint32_t app_get_check_status_val(void);


// 状态检测
bool app_motor_enable_state_check(void);
bool app_target_reached_state_check(void);
bool app_set_point_acknowledge_state_check(void);
bool app_velocity_zero_state_check(void);
bool app_homing_attained_state_check(void);
bool app_position_target_reached_state_check(void);
void app_position_target_reached_state_clear(void);
bool app_velocity_target_reached_state_check(void);
void app_velocity_target_reached_state_clear(void);
bool app_target_torque_reached_state_check(void);
void app_target_torque_reached_state_clear(void);

#endif // APP_STATUS_CHECK_H
