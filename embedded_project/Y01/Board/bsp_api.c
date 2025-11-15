#include "bsp_api.h"
#include "board.h"

#pragma region 系统控制相关
/**
 * @brief 系统复位
 * @return
 * @note
 */
void bsp_system_reset(void)
{
    HAL_NVIC_SystemReset();
}

#pragma endregion

#pragma region 硬件状态相关
/**
 * @brief 设置系统硬件错误状态
 * @param[in] type 错误类型
 * @param[in] op 错误操作
 * @return
 */
void sys_set_bsp_error_state(BSP_ERROR_CODE type, BSP_ERROR_OPERATION op)
{
    set_bsp_error_state(type, op);
}
/**
 * @brief 获取系统硬件错误状态地址
 * @param[out] p_bsp_error 硬件错误状态地址
 * @return
 * @note
 */
void sys_get_bsp_error_state(BspErrorCode_t **p_bsp_error)
{
    *p_bsp_error = get_bsp_error_state();
}
/**
 * @brief 获取系统硬件自检状态
 * @return bool false:未完成 true:完成
 * @note
 */
bool sys_get_hardware_self_test_status(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return true;
#else
    return get_hardware_self_test_status();
#endif
}
/**
 * @brief 系统母线电压检测
 * @return
 * @note
 */
VOLTAGE_CHECK_STATUS sys_bus_voltage_check(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return VOLTAGE_STATUS_NORMAL;
#else
    return BusVoltageCheck();
#endif
}
/**
 * @brief 三相电流检测
 * @return
 * @note
 */
void sys_current_calibration_step(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return;
#else
    CurrentCalibrationStep();
#endif
}
/**
 * @brief 获取系统三相电流检测状态
 * @return CURRENT_CALIBRATION_STATUS
 * @note
 */
CURRENT_CALIBRATION_STATUS sys_get_current_calibration_status(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return CURRENT_CALIBRATION_STATUS_OK;
#else
    return get_current_calibration_status();
#endif
}
/**
 * @brief 获取UVW三相电流校准值
 * @param[out] piabc UVW三相电流校准值数组，单位adc值
 */
void sys_get_current_calibration_drift(uint16_t *drift)
{
#ifdef VIRTUAL_MOTOR_MODEL
    drift[0] = UVW_CURRENT_MID_VAL;
    drift[1] = UVW_CURRENT_MID_VAL;
    drift[2] = UVW_CURRENT_MID_VAL;
#else
    get_current_calibration_drift(drift);
#endif
}
/**
 * @brief 设置PWM输出状态
 * @param[in] state PWM输出状态
 */
void bsp_set_pwm_state(bool state)
{
    kBspData.pwm_en_state = state;
#ifdef VIRTUAL_MOTOR_MODEL

#else
    if (state == PWM_ENABLE)
    {
        __HAL_TIM_MOE_ENABLE(&PWM_TIM_HANDLE);
    }
    else
    {
        __HAL_TIM_MOE_DISABLE_UNCONDITIONALLY(&PWM_TIM_HANDLE);
    }
#endif
}
/**
 * @brief 更新PWM输出准备状态
 */
void bsp_pwm_ready_state_updata(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    kBspData.pwm_ready_state = true;
#else
    if (DRIVER_PWM_READY_TIME)
    {
        if (kBspData.pwm_en_state == PWM_ENABLE)
        {
            kBspData.pwm_state_cnt++;
            if (kBspData.pwm_state_cnt >= DRIVER_PWM_READY_TIME)
            {
                kBspData.pwm_state_cnt = DRIVER_PWM_READY_TIME;
                kBspData.pwm_ready_state = true;
            }
        }
        else
        {
            kBspData.pwm_state_cnt = 0;
            kBspData.pwm_ready_state = false;
        }
    }
    else // 等待时间为0，PWM使能后立即认为PWM准备好
    {
        kBspData.pwm_ready_state = true;
    }
#endif
}
/**
 * @brief 获取PWM输出状态
 * @retval false PWM未准备好
 * @retval true PWM已准备好
 */
bool bsp_get_pwm_state(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return true;
#else
    return kBspData.pwm_ready_state;
#endif
}
/**
 * @brief 设置相电压
 * @param[in] voltage UVW相电压数组(单位V)
 */
void bsp_set_phase_voltage(const float voltage[3])
{
#ifdef VIRTUAL_MOTOR_MODEL
    kAxis.sim_plant_input.uabc_tar_V[0] = voltage[0];
    kAxis.sim_plant_input.uabc_tar_V[1] = voltage[1];
    kAxis.sim_plant_input.uabc_tar_V[2] = voltage[2];
#else
    uint32_t uabc_tar[3] = {0};

    if (kBspData.dc_bus_voltage_val < 8.0f)
    {
        return;
    }

    kBspData.uvw_target_voltage[0] = voltage[0];
    kBspData.uvw_target_voltage[1] = voltage[1];
    kBspData.uvw_target_voltage[2] = voltage[2];

    for (uint8_t i = 0; i < 3; i++)
    {
        uabc_tar[i] = voltage[i] * ((float)PWM_TIM_ARR / kBspData.dc_bus_voltage_val) + PWM_TIM_ARR_LIMIT_HALF;
        if (uabc_tar[i] > PWM_TIM_ARR_P_LIMIT)
        {
            uabc_tar[i] = PWM_TIM_ARR_P_LIMIT;
        }
        if (uabc_tar[i] < PWM_TIM_ARR_N_LIMIT)
        {
            uabc_tar[i] = PWM_TIM_ARR_N_LIMIT;
        }

        uabc_tar[i] = PWM_TIM_ARR - uabc_tar[i]; // CCR值越大，占空比越小
    }

    PWM_TIM_U_CCR_VAL = uabc_tar[0];
    PWM_TIM_V_CCR_VAL = uabc_tar[1];
    PWM_TIM_W_CCR_VAL = uabc_tar[2];
#endif
}
/**
 * @brief 获取UVW三相电流
 * @param[out] piabc UVW三相电流数组，单位A
 */
void bsp_get_phase_current(float piabc[3])
{
#ifdef VIRTUAL_MOTOR_MODEL
    piabc[0] = kAxis.sim_plant_output.iabc_now_A[0];
    piabc[1] = kAxis.sim_plant_output.iabc_now_A[1];
    piabc[2] = kAxis.sim_plant_output.iabc_now_A[2];
#else
    uint16_t drift[3] = {0};

    if (false == bsp_get_pwm_state()) // PWM未准备好，电流采样回读值强制为0
    {
        kBspData.uvw_current[0] = 0.0f;
        kBspData.uvw_current[1] = 0.0f;
        kBspData.uvw_current[2] = 0.0f;
    }
    else
    {
        sys_get_current_calibration_drift(drift);

        kBspData.uvw_current[0] = UVW_CURRENT_DIRECTION *
                                  (float)(int32_t)(UVW_CURRENT_U_CHANNEL - drift[0]) * UVW_CURRENT_SAMP_ADC_K;
        kBspData.uvw_current[1] = UVW_CURRENT_DIRECTION *
                                  (float)(int32_t)(UVW_CURRENT_V_CHANNEL - drift[1]) * UVW_CURRENT_SAMP_ADC_K;
        kBspData.uvw_current[2] = UVW_CURRENT_DIRECTION *
                                  (float)(int32_t)(UVW_CURRENT_W_CHANNEL - drift[2]) * UVW_CURRENT_SAMP_ADC_K;
    }

    piabc[0] = kBspData.uvw_current[0];
    piabc[1] = kBspData.uvw_current[1];
    piabc[2] = kBspData.uvw_current[2];
#endif
}
/**
 * @brief 读取母线电压
 * @return float 母线电压，单位V
 */
float bsp_get_dc_bus_voltage(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return kAxis.sim_plant_output.dc_bus_V;
#else
    kBspData.dc_bus_voltage_val = (float)kBspData.adc1_raw_buffer[DC_BUS_VOLTAGE_RANK1_INDEX] *
                                      DC_BUS_ADC_VOLTAGE_K +
                                  DC_BUS_ADC_VOLTAGE_BIAS;

    return kBspData.dc_bus_voltage_val;
#endif
}
/**
 * @brief 读取母线电流
 * @return float 母线电流，单位A
 */
float bsp_get_dc_bus_current(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return 0;
#else
    kBspData.dc_bus_current_val = (float)(kBspData.adc1_raw_buffer[DC_BUS_CURRENT_RANK2_INDEX] -
                                          UVW_CURRENT_MID_VAL) *
                                      DC_BUS_CURRENT_SAMP_ADC_K +
                                  DC_BUS_ADC_CURRENT_BIAS;

    return kBspData.dc_bus_current_val;
#endif
}
/**
 * @brief 读取电机当前温度
 * @return float 电机温度，单位摄氏度
 */
float bsp_get_motor_temp(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    float temp = (float)(rand() % 201 - 100) / 10.0f;
    return 48.0f + temp;
#else
    kBspData.motor_temp_val = (float)kBspData.adc3_raw_buffer[TEMP_MOTOR_RANK2_INDEX] *
                                  MOTOR_TO_IN_VOLTAGE_RATIO * MOTOR_TEMP_SENSOR_K +
                              MOTOR_TEMP_SENSOR_BIAS;

    return kBspData.motor_temp_val;
#endif
}
/**
 * @brief 读取mos当前温度
 * @return float mos温度，单位摄氏度
 */
float bsp_get_mos_temperature(void)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return 25.0f;
#else
    float temp_mv = (float)kBspData.adc2_raw_buffer[TEMP_MOS_RANK1_INDEX] * MOS_TEMP_VOLTAGE_K;
    kBspData.mos_temp_val = (temp_mv - MOS_TEMP_SENSOR_BIAS) * MOS_TEMP_SENSOR_K;

    return kBspData.mos_temp_val;
#endif
}
/**
 * @brief 读取mcu温度
 * @return float 单位摄氏度
 * @note 底层提供三维数组，连续存放三个温度值，用于中值滤波
 */
float bsp_get_mcu_temperature(void)
{
    static uint8_t mcu_temp_index = 0;

    mcu_temp_index++;
    if (mcu_temp_index >= 3)
    {
        mcu_temp_index = 0;
    }
    kBspData.mcu_temp[mcu_temp_index] = __LL_ADC_CALC_TEMPERATURE(ADC_REFERENCE_MV,
                                                                  kBspData.adc3_raw_buffer[TEMP_MCU_RANK1_INDEX], LL_ADC_RESOLUTION_16B);

    return kBspData.mcu_temp[mcu_temp_index];
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
                            uint32_t const single_bits, uint32_t const multi_bits,
                            uint16_t const type, uint8_t const options)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return;
#else
    set_encoder_options(enc_id, options);
#endif
}
/**
 * @brief 获取编码器状态
 * @param[in] enc_id 编码器端ID： ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @retval false 编码器异常/未准备好
 * @retval true  编码器正常/已准备好
 */
bool bsp_get_encoder_state(ENCODER_ID const enc_id)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return true;
#else
    return get_encoder_status(enc_id);
#endif
}
/**
 * @brief 获取编码器单圈值
 * @param[in] enc_id 编码器端ID： ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @return uint32_t 单圈值
 */
uint32_t bsp_get_encoder_cnt(ENCODER_ID const enc_id)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return kAxis.sim_plant_output.enc_counts_P;
#else
    return get_encoder_cnt(enc_id);
#endif
}
/**
 * @brief 获取编码器多圈值
 * @param[in] enc_id 编码器端ID： ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @return int64_t 多圈值
 */
int64_t bsp_get_encoder_turns(ENCODER_ID const enc_id)
{
#ifdef VIRTUAL_MOTOR_MODEL
    return 0;
#else
    return get_encoder_turns(enc_id);
#endif
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
#if (defined MINOR_VERSION) && (IS_CAN_PROTOCOL(MINOR_VERSION))
    // can_device_set_id(can_id);
#endif
}
/**
 * @brief 获取当前 CAN ID
 * @return
 * @note
 */
uint32_t bsp_get_can_id(void)
{
#if (defined MINOR_VERSION) && (IS_CAN_PROTOCOL(MINOR_VERSION))
    // return can_device_get_id();
    return 0;
#else
    return 0;
#endif
}
/**
 * @brief 设置CAN 波特率
 * @param[in] baudrate 波特率  1000000, 500000  其他配置默认 1000000
 * @return
 * @note
 */
void bsp_set_can_baudrate(uint32_t baudrate)
{
#if (defined MINOR_VERSION) && (IS_CAN_PROTOCOL(MINOR_VERSION))
    // can_device_set_baudrate(baudrate);
#endif
}
/**
 * @brief 获取当前 CAN 波特率
 * @return
 * @note
 */
uint32_t bsp_get_can_baudrate(void)
{
#if (defined MINOR_VERSION) && (IS_CAN_PROTOCOL(MINOR_VERSION))
    // return can_device_get_baudrate();
    return 0;
#else
    return 0;
#endif
}
/**
 * @brief 获取当前 CAN 消息累计计数值
 * @return
 * @note
 */
uint32_t bsp_get_can_mg_counts(void)
{
#if (defined MINOR_VERSION) && (IS_CAN_PROTOCOL(MINOR_VERSION))
    // return can_device_get_mg_counts();
    return 0;
#else
    return 0;
#endif
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
    return (FLASHDB_STATUS)flashdb_init();
}
/**
 * @brief FlashDB数据库读取
 * @param index:目标数据键值索引
 * @return FLASHDB_STATUS 状态
 * @note
 */
FLASHDB_STATUS bsp_flashdb_read(FLASHDB_KEY_INDEX const index)
{
    return (FLASHDB_STATUS)flashdb_read(index);
}
/**
 * @brief FlashDB数据库写入
 * @param index:目标数据键值索引
 * @return FLASHDB_STATUS 状态
 * @note
 */
FLASHDB_STATUS bsp_flashdb_write(FLASHDB_KEY_INDEX const index)
{
    return (FLASHDB_STATUS)flashdb_write(index);
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
    return (FLASHDB_STATUS)flashdb_key_register(index, key, value, value_len);
}
/**
 * @brief FlashDB数据库键值删除
 * @param index:目标数据键值索引
 * @return FLASHDB_STATUS 状态
 * @note
 */
FLASHDB_STATUS bsp_flashdb_key_delete(FLASHDB_KEY_INDEX const index)
{
    return (FLASHDB_STATUS)flashdb_key_delete(index);
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
    sys_blocking_delay_us(us);
}
/**
 * @brief 系统阻塞ms延时
 * @param[in] ms 延时时间，单位ms
 * @return
 * @note
 */
void bsp_sys_blocking_delay_ms(uint32_t ms)
{
    sys_blocking_delay_ms(ms);
}
/**
 * @brief 系统耗时记录开始
 * @param[in] index 代码区块序号
 * @return
 * @note
 */
void bsp_set_timer_record_start(SYS_TIMER_RECORD_INDEX index)
{
    set_timer_record_start(index);
}
/**
 * @brief 系统耗时记录结束
 * @param[in] index 代码区块序号
 * @return
 * @note
 */
void bsp_set_timer_record_stop(SYS_TIMER_RECORD_INDEX index)
{
    set_timer_record_stop(index);
}
/**
 * @brief 获取系统代码区块执行耗时
 * @param[in] index 代码区块序号
 * @return
 * @note
 */
float bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_INDEX index)
{
    return get_timer_duration_records_us(index);
}
/**
 * @brief 设置运行LED状态
 * @param[in] state  0:关闭 1:打开
 * @return
 * @note
 */
void bsp_set_run_led_state(uint8_t state)
{
    if (state)
    {
        LED_BLUE_ON();
    }
    else
    {
        LED_BLUE_OFF();
    }
}
/**
 * @brief 设置运行 LED状态翻转
 * @return
 * @note
 */
void bsp_set_run_led_toggle(void)
{
    LED_BLUE_TOGGLE();
}
/**
 * @brief 设置错误LED状态
 * @param[in] state  0:关闭 1:打开
 * @return
 * @note
 */
void bsp_set_error_led_state(uint8_t state)
{
    if (state)
    {
        LED_RED_ON();
    }
    else
    {
        LED_RED_OFF();
    }
}
/**
 * @brief 设置错误LED状态翻转
 * @return
 * @note
 */
void bsp_set_error_led_toggle(void)
{
    LED_RED_TOGGLE();
}

#pragma endregion
