#include "bsp_api.h"
#include "motor_ctl_loop.h"
#include <stdlib.h>

#pragma region 系统控制相关
/**
 * @brief 系统复位
 * @return
 * @note
 */
void bsp_system_reset(void)
{
    return;
}
#pragma endregion

#pragma region 硬件状态相关
/**
 * @brief 获取系统硬件自检状态
 * @return bool false:未完成 true:完成
 * @note
 */
bool sys_get_hardware_self_test_status(void)
{
    return true;
}
/**
 * @brief 获取系统三相电流检测状态
 * @return CURRENT_CALIBRATION_STATUS
 * @note
 */
CURRENT_CALIBRATION_STATUS sys_get_current_calibration_status(void)
{
    return CURRENT_CALIBRATION_STATUS_OK;
}
/**
 * @brief 母线电压检测
 * @return
 * @note
 */
VOLTAGE_CHECK_STATUS sys_bus_voltage_check(void)
{
    return VOLTAGE_STATUS_UNKNOWN;
}
/**
 * @brief 三相电流检测
 * @return
 * @note
 */
void sys_current_calibration_step(void)
{
    return ;
}
/**
 * @brief 获取系统BSP错误码地址
 * @param[out] p_bsp_error BSP错误码地址
 * @return
 * @note
 */
void sys_get_bsp_error_state(BspErrorCode_t* *p_bsp_error)
{
    return;
}
/**
 * @brief 设置PWM输出状态
 * @param[in] state PWM输出状态，0-关闭;1-开启
 */
void bsp_set_pwm_state(bool state)
{
    return;
}
/**
 * @brief 获取PWM输出状态
 * @retval false PWM未准备好
 * @retval true PWM已准备好
 */
bool bsp_get_pwm_state(void)
{
    return true;
}
/**
 * @brief 设置相电压
 * @param[in] voltage UVW相电压数组(单位V)
 */
void bsp_set_phase_voltage(const float voltage[3])
{
    kAxis.sim_plant_input.uabc_tar_V[0] = voltage[0];
    kAxis.sim_plant_input.uabc_tar_V[1] = voltage[1];
    kAxis.sim_plant_input.uabc_tar_V[2] = voltage[2];
}
/**
 * @brief 获取UVW三相电流校准值
 * @param[out] piabc UVW三相电流校准值数组，单位adc值
 */
void bsp_get_current_calibration_drift(uint16_t *drift)
{
    drift[0] = 32768;
    drift[1] = 32768;
    drift[2] = 32768;
}
/**
 * @brief 获取UVW三相电流
 * @param[out] piabc UVW三相电流数组，单位A
 */
void bsp_get_phase_current(float piabc[3])
{
    // 从虚拟电机中获取三相电流
    piabc[0] = kAxis.sim_plant_output.iabc_now_A[0];
    piabc[1] = kAxis.sim_plant_output.iabc_now_A[1];
    piabc[2] = kAxis.sim_plant_output.iabc_now_A[2];
}
/**
 * @brief 读取母线电压
 * @return float 母线电压，单位V
 */
float bsp_get_dc_bus_voltage(void)
{
    return kAxis.sim_plant_output.dc_bus_V;
}
/**
 * @brief 读取母线电流
 * @return float 母线电流，单位A
 */
float bsp_get_dc_bus_current(void)
{
    return 0;
}
/**
 * @brief 读取电机当前温度
 * @return float 电机温度，单位摄氏度
 */
float bsp_get_motor_temp(void)
{
    // 生成随机数±1
    float temp = (float)(rand() % 201 - 100) / 10.0f;
    return 48.0f + temp;
}
/**
 * @brief 读取mos当前温度
 * @return float mos温度，单位摄氏度
 */
float bsp_get_mos_temperature(void)
{
    return 25.0f;
}
/**
 * @brief 读取mcu温度
 * @return float 单位摄氏度
 * @note 底层提供三维数组，连续存放三个温度值，用于中值滤波
 */
float bsp_get_mcu_temperature(void)
{
    return 25.0f;
}

#pragma endregion

#pragma region 编码器相关
/**
 * @brief 编码器配置
 * @param[in] enc_id 编码器端ID： ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @param[in] single_bits 编码器单圈位数
 * @param[in] multi_bits 编码器多圈位数(无多圈值时，设置为0)
 * @param[in] type 编码器类型
 * @param[in] options 编码器选项
 */
void bsp_set_encoder_config(ENCODER_ID const enc_id,
                        uint32_t const single_bits, uint32_t const  multi_bits,
                        uint16_t const type, uint8_t const options)
{
    return;
}
/**
 * @brief 获取编码器状态
 * @param[in] enc_id 编码器端ID： ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @retval false 编码器异常/未准备好
 * @retval true  编码器正常/已准备好
 */
bool bsp_get_encoder_state(ENCODER_ID const enc_id)
{
    return true;
}
/**
 * @brief 获取编码器单圈值
 * @param[in] enc_id 编码器端ID： ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @return uint32_t 单圈值
 */
uint32_t bsp_get_encoder_cnt(ENCODER_ID const enc_id)
{
    if (enc_id == ENCODER_ID_MOTOR)
    {
        return kAxis.sim_plant_output.enc_counts_P;
    }
    else if (enc_id == ENCODER_ID_LOAD)
    {
        return kAxis.sim_plant_output.enc_counts_P;
    }

    return kAxis.sim_plant_output.enc_counts_P;
}
/**
 * @brief 获取编码器多圈值
 * @param[in] enc_id 编码器端ID： ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @return int64_t 多圈值
 */
int64_t bsp_get_encoder_turns(ENCODER_ID const enc_id)
{
    return 0;
}

#pragma endregion

#pragma region 通讯相关
/**
 * @brief 设置CAN ID
 * @param[in] can_id CAN ID
 * @return
 * @note
 */
void bsp_set_can_id(uint32_t can_id)
{
    return;
}
/**
 * @brief 设置CAN 波特率
 * @param[in] baudrate 波特率  1000000, 500000  其他配置默认 1000000
 * @return
 * @note
 */
void bsp_set_can_baudrate(uint32_t baudrate)
{
    return;
}
/**
 * @brief 获取当前 CAN ID
 * @return
 * @note
 */
uint32_t bsp_get_can_id(void)
{
    return 0;
}
/**
 * @brief 获取当前 CAN 波特率
 * @return
 * @note
 */
uint32_t bsp_get_can_baudrate(void)
{
    return 0;
}
/**
 * @brief 获取当前 CAN 消息累计计数值
 * @return
 * @note
 */
uint32_t bsp_get_can_mg_counts(void)
{
    return 0;
}

#pragma endregion

#pragma region 参数存储相关
/**
 * @brief FlashDB数据库初始化
 * @return FLASHDB_STATUS 状态
 * @note
 */
FLASHDB_STATUS bsp_flashdb_init(void)
{
    return FLASHDB_NO_ERR;
}
/**
 * @brief FlashDB数据库读取
 * @param index:目标数据键值索引
 * @return FLASHDB_STATUS 状态
 * @note
 */
FLASHDB_STATUS bsp_flashdb_read(FLASHDB_KEY_INDEX const index)
{
    return FLASHDB_NO_ERR;
}
/**
 * @brief FlashDB数据库写入
 * @param index:目标数据键值索引
 * @return FLASHDB_STATUS 状态
 * @note
 */
FLASHDB_STATUS bsp_flashdb_write(FLASHDB_KEY_INDEX const index)
{
    return FLASHDB_NO_ERR;
}
/**
 * @brief FlashDB数据库键值注册
 * @param index:目标数据键值索引
 * @param key:目标数据键值
 * @param value:目标数据地址
 * @param value_len:目标数据长度
 * @retval FLASHDB_STATUS
 * @note
 */
FLASHDB_STATUS bsp_flashdb_key_register(FLASHDB_KEY_INDEX index, char *key, void *value, size_t value_len)
{
    return FLASHDB_NO_ERR;
}
/**
 * @brief FlashDB数据库键值删除
 * @param index:目标数据键值索引
 * @return FLASHDB_STATUS 状态
 * @note
 */
FLASHDB_STATUS bsp_flashdb_key_delete(FLASHDB_KEY_INDEX const index)
{
    return FLASHDB_NO_ERR;
}
#pragma endregion

#pragma region 其它
/**
 * @brief 系统阻塞us延时
 * @param[in] us 延时时间，单位us
 * @return
 * @note
 */
void bsp_sys_blocking_delay_us(uint32_t us)
{
    return;
}
/**
 * @brief 系统阻塞ms延时
 * @param[in] ms 延时时间，单位ms
 * @return
 * @note
 */
void bsp_sys_blocking_delay_ms(uint32_t ms)
{
    return;
}
/**
 * @brief 系统耗时记录开始
 * @param[in] index 代码区块序号
 * @return
 * @note
 */
void bsp_set_timer_record_start(SYS_TIMER_RECORD_INDEX index)
{
    return;
}
/**
 * @brief 系统耗时记录结束
 * @param[in] index 代码区块序号
 * @return
 * @note
 */
void bsp_set_timer_record_stop(SYS_TIMER_RECORD_INDEX index)
{
    return;
}
/**
 * @brief 获取系统代码区块执行耗时
 * @param[in] index 代码区块序号
 * @return
 * @note
 */
float bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_INDEX index)
{
    return 0;
}
/**
 * @brief 设置运行LED状态
 * @param[in] state  0:关闭 1:打开
 * @return
 * @note
 */
void bsp_set_run_led_state(uint8_t state)
{
    return;
}
/**
 * @brief 设置运行 LED状态翻转
 * @return
 * @note
 */
void bsp_set_run_led_toggle(void)
{
    return;
}
/**
 * @brief 设置错误LED状态
 * @param[in] state  0:关闭 1:打开
 * @return
 * @note
 */
void bsp_set_error_led_state(uint8_t state)
{
    return;
}
/**
 * @brief 设置错误LED状态翻转
 * @return
 * @note
 */
void bsp_set_error_led_toggle(void)
{
    return;
}

#pragma endregion
