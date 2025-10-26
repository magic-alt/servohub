#include "board.h"

__attribute__((section(".RAM_D1"))) BspData kBspData =
{
    .adc1_raw_buffer[0] = 0,
    .adc1_raw_buffer[1] = 0,
    .adc1_raw_buffer[2] = 0,
    .adc2_raw_buffer[0] = 0,
    .adc2_raw_buffer[1] = 0,
    .adc2_raw_buffer[2] = 0,
    .adc3_raw_buffer[0] = 0,
    .adc3_raw_buffer[1] = 0,
    .adc3_raw_buffer[2] = 0,
    .adc_regular_sampling_request = true,
    .dc_bus_voltage_val = 0.0f,
    .dc_bus_current_val = 0.0f,
    .motor_temp_val = 20.0f,
    .mos_temp_val = 25.0f,
    .mcu_temp[0] = 30.0f,
    .mcu_temp[1] = 30.0f,
    .mcu_temp[2] = 30.0f,
    .uvw_current[0] = 0.0f,
    .uvw_current[1] = 0.0f,
    .uvw_current[2] = 0.0f,
    .uvw_target_voltage[0] = 0.0f,
    .uvw_target_voltage[1] = 0.0f,
    .uvw_target_voltage[2] = 0.0f,
    .motor_cnt = 0,
    .load_cnt = 0,
    .motor_turns = 0,
    .load_turns = 0,
    .pwm_en_state = 0,
    .pwm_ready_state = 0,
    .pwm_state_cnt = 0,
};

void BspInit(void)
{
    // 触发规则通道队列DMA采样
    HAL_ADC_Start_DMA(&DC_BUS_VOLTAGE_HANDLE, (uint32_t *)kBspData.adc1_raw_buffer, ADC1_REGULAR_RANK_NUMBER);
    // 等待母线电压稳定
    do {
        HAL_Delay(1);
    } while (sys_bus_voltage_check() == VOLTAGE_STATUS_UNKNOWN);

    HAL_ADC_Stop_DMA(&DC_BUS_VOLTAGE_HANDLE);

    // 启动 ADC 校准
    if (HAL_ADCEx_Calibration_Start(&UVW_CURRENT_U_HANDLE, \
        ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
    {
        set_bsp_error_state(ERROR_CURRENT_SAMPLE, ERROR_SET);
    }
    else if (HAL_ADCEx_Calibration_Start(&UVW_CURRENT_V_HANDLE, \
        ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
    {
        set_bsp_error_state(ERROR_CURRENT_SAMPLE, ERROR_SET);
    }
    else if (HAL_ADCEx_Calibration_Start(&UVW_CURRENT_W_HANDLE, \
        ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
    {
        set_bsp_error_state(ERROR_CURRENT_SAMPLE, ERROR_SET);
    }

    HAL_ADC_Start_DMA(&DC_BUS_VOLTAGE_HANDLE, (uint32_t *)kBspData.adc1_raw_buffer, ADC1_REGULAR_RANK_NUMBER);
    HAL_ADC_Start_DMA(&TEMP_MOS_HANDLE, (uint32_t *)kBspData.adc2_raw_buffer, ADC2_REGULAR_RANK_NUMBER);
    HAL_ADC_Start_DMA(&TEMP_MCU_HANDLE, (uint32_t *)kBspData.adc3_raw_buffer, ADC3_REGULAR_RANK_NUMBER);
    HAL_Delay(5);

    // 启动 1ms 任务
    HAL_TIM_Base_Start_IT(&CANOPEN_TIM_HANDLE);
    HAL_TIM_Base_Start_IT(&NRT_TASK_TIM_HANDLE);

    // 启动ADC注入中断
    HAL_ADCEx_InjectedStart_IT(&UVW_CURRENT_U_HANDLE);
    HAL_ADCEx_InjectedStart(&UVW_CURRENT_V_HANDLE);
    HAL_ADCEx_InjectedStart(&UVW_CURRENT_W_HANDLE);

    // 初始化时关闭pwm波
    PWM_TIM_U_CCR_VAL = 0;
    PWM_TIM_V_CCR_VAL = 0;
    PWM_TIM_W_CCR_VAL = 0;
    HAL_TIM_PWM_Start(&PWM_TIM_HANDLE, PWM_TIM_U_CHANNEL);
    HAL_TIMEx_PWMN_Start(&PWM_TIM_HANDLE, PWM_TIM_U_CHANNEL);
    HAL_TIM_PWM_Start(&PWM_TIM_HANDLE, PWM_TIM_V_CHANNEL);
    HAL_TIMEx_PWMN_Start(&PWM_TIM_HANDLE, PWM_TIM_V_CHANNEL);
    HAL_TIM_PWM_Start(&PWM_TIM_HANDLE, PWM_TIM_W_CHANNEL);
    HAL_TIMEx_PWMN_Start(&PWM_TIM_HANDLE, PWM_TIM_W_CHANNEL);
    bsp_set_pwm_state(PWM_DISABLE);
    __HAL_TIM_ENABLE_IT(&PWM_TIM_HANDLE, TIM_IT_BREAK);

    // 启动调试软件通讯
    HAL_UART_Receive_DMA(&HOST_UART_HANDLE, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE);
    __HAL_UART_ENABLE_IT(&HOST_UART_HANDLE, UART_IT_IDLE);
    __HAL_UART_CLEAR_FLAG(&HOST_UART_HANDLE, UART_IT_IDLE);

    HAL_Delay(10);
}

// 电流环中断任务 典型频率  20KHZ
void CURRENT_LOOP_IRQ_TASK(ADC_HandleTypeDef *hadc)
{
    static volatile uint8_t position_frq_div = 0;

    if (hadc->Instance == UVW_CURRENT_U_HANDLE.Instance)
    {
        bsp_set_timer_record_stop(SYS_TIMER_RECORD_CURRENT_LOOP_CYCLE_INDEX); // 测量电流环周期
        bsp_set_timer_record_start(SYS_TIMER_RECORD_CURRENT_LOOP_CYCLE_INDEX);

        // 硬件自检完毕且电流校准通过，运行电流环
        if (sys_get_hardware_self_test_status() == true && \
            sys_get_current_calibration_status() == CURRENT_CALIBRATION_STATUS_OK)
        {
            bsp_set_timer_record_start(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX); // 测量电流环运行时间
            CurrentLoopCtrl();
        #ifdef VIRTUAL_MOTOR_MODEL
            SimPlantStep();
        #endif
            bsp_set_timer_record_stop(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX);
        }

        if (position_frq_div == 0)
        {
        #ifndef VIRTUAL_MOTOR_MODEL
            if (sys_get_hardware_self_test_status() == false)
            {
                encoder_data_init();
                HardwareSelfTestRun();
            }

            // 编码器数据读取及处理
            encoder_data_read();
            encoder_data_process();

            BspReadyStateupdata(); // 更新硬件准备状态
        #endif

            PosSpeedLoopCtrl();

            position_frq_div = 1; // 1:10KHZ 位置环   3:5KHZ 位置环
        }
        else
        {
            position_frq_div--;
        }
    }
}

void ECAT_EXTI_IRQ_TASK(uint16_t GPIO_Pin)
{
    // TODO
}

// 1ms低频任务 典型频率  1KHZ
void NRT_CAN_ECAT_IRQ_TASK(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == NRT_TASK_TIM_HANDLE.Instance)
    {
        UnrealTimeBase1ms();
    }
}

/**
 * @brief  定时器断路中断回调函数
 * @param  htim: 定时器句柄指针
 * @retval None
 * @note   处理PWM输出的断路保护事件
 */
void PWM_TIM_BREAK_IRQ_HANDLE(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == PWM_TIM_HANDLE.Instance)
    {
        __HAL_TIM_DISABLE_IT(htim, TIM_IT_BREAK);

        bsp_set_pwm_state(PWM_DISABLE);
        //set_bsp_error_state(ERROR_NFAULT, ERROR_SET);
    }
}

/**
 * @brief 上位机通讯，向上位机发送数据
 * 该函数用于处理UART中断事件，主要用于处理IDLE空闲中断
 * 当检测到UART空闲状态时，会停止DMA传输，处理接收到的数据，然后重新启动DMA接收
 */
void mavlink_send_data(uint8_t *pdata, uint32_t len)
{
    HAL_UART_Transmit_DMA(&HOST_UART_HANDLE, pdata, len);
}
/**
 * @brief 上位机通讯UART中断任务
 * 该函数用于处理UART中断事件，主要用于处理IDLE空闲中断
 * 当检测到UART空闲状态时，会停止DMA传输，处理接收到的数据，然后重新启动DMA接收
 */
void HOST_UART_IRQ_TASK(void)
{
    HAL_UART_IRQHandler(&HOST_UART_HANDLE);  // 调用HAL库的UART中断处理函数

    if (__HAL_UART_GET_FLAG(&HOST_UART_HANDLE, UART_FLAG_IDLE))
    {
        __HAL_UART_CLEAR_IDLEFLAG(&HOST_UART_HANDLE);

        HAL_UART_DMAStop(&HOST_UART_HANDLE);

        // 调用Mavlink数据接收回调函数，处理接收到的数据
        // 参数为接收缓冲区和实际接收到的数据长度
        MavlinkRecvCallback(&kAxis, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE - __HAL_DMA_GET_COUNTER(HOST_UART_HANDLE.hdmarx));

        // 重新启动DMA接收，准备接收下一批数据
        HAL_UART_Receive_DMA(&HOST_UART_HANDLE, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE);
    }
}

/**
 * @brief 上位机通讯UART错误回调函数
 * @param huart: UART句柄指针，指向发生错误的UART实例
 * @note 该函数在UART通信发生错误时被调用，用于处理错误并恢复通信
 */
void HOST_UART_ERROR_HANDLE(UART_HandleTypeDef *huart)
{
    if (huart->Instance == HOST_UART_HANDLE.Instance)
    {
        // 检查是否存在奇偶校验错误(PE)、帧错误(FE)、噪声错误(NE)或溢出错误(ORE)
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE | UART_FLAG_FE | \
                                       UART_FLAG_NE | UART_FLAG_ORE))
        {
            __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_PE | UART_FLAG_FE |\
                                         UART_FLAG_NE | UART_FLAG_ORE);
            HAL_UART_DMAStop(huart);
            // 重新启动UART DMA接收，使用指定的接收缓冲区和缓冲区大小
            HAL_UART_Receive_DMA(huart, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE);
        }
    }
}
