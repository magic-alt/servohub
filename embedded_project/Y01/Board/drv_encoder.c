#include "drv_encoder.h"

// 编码器接收数据缓冲区
__attribute__((section(".RAM_D1"))) uint8_t encoder_tx_buff[ENCODER_NUM][ENCODER_FRAME_MAX_LEN] = { 0 };
__attribute__((section(".RAM_D1"))) uint8_t encoder_rx_buff[ENCODER_NUM][ENCODER_FRAME_MAX_LEN] = { 0 };

static inline void Encoder_None(EncoderDataInfo_t* enc_data);
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ || ENCODER2_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ
static void ABZ_Encoder_Init(EncoderDataInfo_t* enc_data);
static void ABZ_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void ABZ_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
#endif // ENCODER_TYPE_INC_AB_ABZ
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA
static void TAMAGAWA_Encoder_Init(EncoderDataInfo_t* enc_data);
static void TAMAGAWA_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void TAMAGAWA_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
#endif // ENCODER_TYPE_ABS_RS485_TAMAGAWA
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX
static void KTM59XX_Encoder_Init(EncoderDataInfo_t* enc_data);
static void KTM59XX_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void KTM59XX_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
static inline bool KTM59XX_Encoder_Crc8_Check(uint64_t input, int32_t len);
#endif // ENCODER_TYPE_ABS_SPI_KTM59XX
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S
static void SMC40S_Encoder_Init(EncoderDataInfo_t* enc_data);
static void SMC40S_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void SMC40S_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
//static inline uint8_t BISSC_Crc6_Calc(uint32_t data, uint8_t bit_len, uint8_t final_xor);
#endif // ENCODER_TYPE_ABS_BISSC_SMC40S

EncoderDataInfo_t encoder_data[ENCODER_NUM] = {
    [ENCODER_ID_1] = {
        .id = ENCODER_ID_1,
        .tim_handle = NULL,
        .uart_handle = &ENCODER1_UART_HANDLE,
        .spi_handle = &ENCODER1_SPI_HANDLE,
        .abz_ab_cnt = 0,
        .abz_z_first_flag = true,
        .abz_z_first_ab_cnt = 0,
        .abz_z_last_ab_cnt = 0,
        .data_raw = { 0 },
        .frame_len = ENCODER_FRAME_LEN_INIT,
        .cf = ENCODER_CF_INIT,
        .sf = 0,
        .almc = 0,
        .enid = 0,
        .check_val = 0,
        .err_cnt = 0,
        .options.val = 0,
        .motor_single_less_bits = 0,
        .load_single_less_bits = 0,
        .motor_single_res = 0,
        .motor_multi_res = 0,
        .load_single_res = 0,
        .load_multi_res = 0,
        .motor_single_raw = 0,
        .motor_multi_raw = 0,
        .load_single_raw = 0,
        .load_multi_raw = 0,
        .single_cnt = 0,
        .multi_turns = 0,
        .real_motor_turns_res = 0,
    #if ENCODER1_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ
        .init = ABZ_Encoder_Init,
        .read = ABZ_Encoder_Data_Read,
        .process = ABZ_Encoder_Data_Process,
    #elif ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA
        .init = TAMAGAWA_Encoder_Init,
        .read = TAMAGAWA_Encoder_Data_Read,
        .process = TAMAGAWA_Encoder_Data_Process,
    #elif ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX
        .init = KTM59XX_Encoder_Init,
        .read = KTM59XX_Encoder_Data_Read,
        .process = KTM59XX_Encoder_Data_Process,
    #elif ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S
        .init = SMC40S_Encoder_Init,
        .read = SMC40S_Encoder_Data_Read,
        .process = SMC40S_Encoder_Data_Process,
    #else
        .init = Encoder_None,
        .read = Encoder_None,
        .process = Encoder_None,
    #endif
    },
    [ENCODER_ID_2] = {
        .id = ENCODER_ID_2,
        .tim_handle = NULL,
        .uart_handle = &ENCODER2_UART_HANDLE,
        .spi_handle = &ENCODER2_SPI_HANDLE,
        .abz_ab_cnt = 0,
        .abz_z_first_flag = true,
        .abz_z_first_ab_cnt = 0,
        .abz_z_last_ab_cnt = 0,
        .data_raw = { 0 },
        .frame_len = ENCODER_FRAME_LEN_INIT,
        .cf = ENCODER_CF_INIT,
        .sf = 0,
        .almc = 0,
        .enid = 0,
        .check_val = 0,
        .err_cnt = 0,
        .options.val = 0,
        .motor_single_less_bits = 0,
        .load_single_less_bits = 0,
        .motor_single_res = 0,
        .motor_multi_res = 0,
        .load_single_res = 0,
        .load_multi_res = 0,
        .motor_single_raw = 0,
        .motor_multi_raw = 0,
        .load_single_raw = 0,
        .load_multi_raw = 0,
        .single_cnt = 0,
        .multi_turns = 0,
        .real_motor_turns_res = 0,
    #if ENCODER2_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ
        .init = ABZ_Encoder_Init,
        .read = ABZ_Encoder_Data_Read,
        .process = ABZ_Encoder_Data_Process,
    #elif ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA
        .init = TAMAGAWA_Encoder_Init,
        .read = TAMAGAWA_Encoder_Data_Read,
        .process = TAMAGAWA_Encoder_Data_Process,
    #elif ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX
        .init = KTM59XX_Encoder_Init,
        .read = KTM59XX_Encoder_Data_Read,
        .process = KTM59XX_Encoder_Data_Process,
    #elif ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S
        .init = SMC40S_Encoder_Init,
        .read = SMC40S_Encoder_Data_Read,
        .process = SMC40S_Encoder_Data_Process,
    #else
        .init = Encoder_None,
        .read = Encoder_None,
        .process = Encoder_None,
    #endif
    }
};

/**
 * @brief 初始化编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及接口，初始化编码器数据
 */
void EncoderDataInit(void)
{
    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id <= ENCODER_ID_MAXIMUN; enc_id ++)
    {
        encoder_data[enc_id].init(&encoder_data[enc_id]);
    }
}

/**
 * @brief 读取编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及接口，读取编码器数据
 */
void EncoderDataRead(void)
{
    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id <= ENCODER_ID_MAXIMUN; enc_id ++)
    {
        // 转存上周期读取的编码器器数据
        for (uint8_t i = 0; i < encoder_data[enc_id].frame_len; i++)
        {
            encoder_data[enc_id].data_raw[i] = encoder_rx_buff[enc_id][i];
            encoder_rx_buff[enc_id][i] = 0;
        }

        encoder_data[enc_id].read(&encoder_data[enc_id]);
    }
}

/**
 * @brief 处理编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及协议，解析编码器数据
 */
void EncoderDataProcess(void)
{
    uint32_t u32_calc_temp = 0;
    int64_t i64_calc_temp = 0;

    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id <= ENCODER_ID_MAXIMUN; enc_id ++)
    {
        // 按各自编码器协议对应解析
        encoder_data[enc_id].process(&encoder_data[enc_id]);

        // 编码器配置选项bit3，电机端多圈值为负载端单圈值
        if (encoder_data[enc_id].options.bits.l_cnt_2_m_turns)
        {
            encoder_data[enc_id].motor_multi_raw = encoder_data[enc_id].load_single_raw;  // 电机端多圈值 = 负载端单圈值
            encoder_data[enc_id].load_single_raw = 0;    // 负载端单圈值 = 0
            encoder_data[enc_id].real_motor_turns_res = encoder_data[enc_id].load_single_res; // 电机端多圈值分辨率 = 负载端单圈值分辨率
        }
        else
        {
            encoder_data[enc_id].real_motor_turns_res = encoder_data[enc_id].motor_multi_res;
        }

        // 编码器配置选项bit2，多圈值溢出坐标选项，默认为0：按正负分辨率一半溢出
        if (!encoder_data[enc_id].options.bits.turns_overflow_0)
        {
            // 大于半圈则作为负圈数
            if (encoder_data[enc_id].motor_multi_raw > (encoder_data[enc_id].real_motor_turns_res >> 1))
            {
                i64_calc_temp = encoder_data[enc_id].motor_multi_raw - (int64_t)(encoder_data[enc_id].real_motor_turns_res);
                encoder_data[enc_id].motor_multi_raw = i64_calc_temp;
            }
            if (encoder_data[enc_id].load_multi_raw > (encoder_data[enc_id].load_multi_res >> 1))
            {
                i64_calc_temp = encoder_data[enc_id].load_multi_raw - (int64_t)(encoder_data[enc_id].load_multi_res);
                encoder_data[enc_id].load_multi_raw = i64_calc_temp;
            }
        }

        // 编码器配置选项bit0，电机端编码器方向
        if (encoder_data[enc_id].options.bits.motor_dir)
        {
            u32_calc_temp = encoder_data[enc_id].motor_single_res - 1 - encoder_data[enc_id].motor_single_raw;
            i64_calc_temp = encoder_data[enc_id].real_motor_turns_res - 1 - encoder_data[enc_id].motor_multi_raw;
            encoder_data[enc_id].motor_single_raw = u32_calc_temp;
            encoder_data[enc_id].motor_multi_raw = i64_calc_temp;
        }
        // 编码器配置选项bit1，负载端编码器方向
        if (encoder_data[enc_id].options.bits.load_dir)
        {
            u32_calc_temp = encoder_data[enc_id].load_single_res - 1 - encoder_data[enc_id].load_single_raw;
            i64_calc_temp = encoder_data[enc_id].load_multi_res - 1 - encoder_data[enc_id].load_multi_raw;
            encoder_data[enc_id].load_single_raw = u32_calc_temp;
            encoder_data[enc_id].load_multi_raw = i64_calc_temp;
        }
    }
    // 统一更新编码器数据, 需根据实际编码器1、2接口读取的编码器数据更新电机端、负载端编码器数据
    encoder_data[ENCODER_ID_MOTOR].single_cnt = encoder_data[ENCODER_ID_1].motor_single_raw;
    encoder_data[ENCODER_ID_MOTOR].multi_turns = encoder_data[ENCODER_ID_1].motor_multi_raw;
    encoder_data[ENCODER_ID_LOAD].single_cnt = encoder_data[ENCODER_ID_2].motor_single_raw;
    encoder_data[ENCODER_ID_LOAD].multi_turns = encoder_data[ENCODER_ID_2].motor_multi_raw;
}

/**
 * @brief 获取编码器单圈值
 * @param[in] enc_id 编码器端ID：ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @retval 对应编码器端ID单圈值
 */
uint32_t get_encoder_cnt(ENCODER_ID const enc_id)
{
    return encoder_data[enc_id].single_cnt;
}
/**
 * @brief 获取编码器多圈值
 * @param[in] enc_id 编码器端ID：ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @retval 对应编码器端ID多圈值
 */
int64_t get_encoder_turns(ENCODER_ID const enc_id)
{
    return encoder_data[enc_id].multi_turns;
}

/**
 * @brief 获取编码器状态
 * @param[in] enc_id 编码器ID
 * @retval false 编码器异常/未准备好
 * @retval true  编码器正常/已准备好
 */
bool get_encoder_status(ENCODER_ID const enc_id)
{
    // 获取到编码器id，并且通讯错误次数小于最大值
    if (enc_id == ENCODER_ID_1)
    {
    #if ENCODER1_TYPE_OPTION != ENCODER_TYPE_NONE
        if (encoder_data[enc_id].enid != 0 && \
            encoder_data[enc_id].err_cnt < ENCODER_COMM_ERROR_MAX)
        {
            return true;
        }
    #else
        return true;
    #endif
    }
    else// if (enc_id == ENCODER_ID_2)
    {
    #if ENCODER2_TYPE_OPTION != ENCODER_TYPE_NONE
        if (encoder_data[enc_id].enid != 0 && \
            encoder_data[enc_id].err_cnt < ENCODER_COMM_ERROR_MAX)
        {
            return true;
        }
    #else
        return true;
    #endif
    }
    return false;
}

/**
 * @brief 编码器配置选项设置
 * @param[in] enc_id 编码器ID
 * @param[in] options 编码器配置选项整体值
 * @retval
 */
void set_encoder_options(ENCODER_ID enc_id, uint8_t const options)
{
    encoder_data[enc_id].options.val = options;
}

/**
 * @brief 编码器无操作
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static inline void Encoder_None(EncoderDataInfo_t* enc_data)
{
    return;
}
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ || ENCODER2_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ
/**
 * @brief ABZ编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void ABZ_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    enc_data->abz_ab_cnt = 0;
    enc_data->abz_z_first_flag = true;
    enc_data->abz_z_first_ab_cnt = 0;
    enc_data->abz_z_last_ab_cnt = 0;

    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->tim_handle = &ENCODER1_ABZ_TIM_HANDLE;
        if (PMSM_MOTOR_ENC_DIR == -1)
        {
            enc_data->options.bits.motor_dir = 1;
        }
        enc_data->motor_single_less_bits = PMSM_ENC_LINE_LESS_BITS;
        enc_data->motor_single_res = PMSM_ENC_LINE_P_N;
        enc_data->motor_multi_res = PMSM_ENC_MULTI_LINE_P_N;

        enc_data->tim_handle->Instance->ARR = enc_data->motor_single_res - 1; //设置为编码器4倍频增量计数分辨率 - 1
        HAL_TIM_Encoder_Start(enc_data->tim_handle, TIM_CHANNEL_ALL);
        HAL_TIM_IC_Start_IT(enc_data->tim_handle, TIM_CHANNEL_3); // 根据实际情况配置通道
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->tim_handle = &ENCODER2_ABZ_TIM_HANDLE;
        if (PMSM_LOAD_ENC_DIR == -1)
        {
            enc_data->options.bits.motor_dir = 1;
        }
        enc_data->motor_single_less_bits = PMSM_LOAD_ENC_LINE_LESS_BITS;
        enc_data->motor_single_res = PMSM_LOAD_ENC_LINE_P_N;
        enc_data->motor_multi_res = PMSM_LOAD_ENC_MULTI_LINE_P_N;

        enc_data->tim_handle->Instance->ARR = enc_data->motor_single_res - 1; //设置为编码器4倍频增量计数分辨率 - 1
        HAL_TIM_Encoder_Start(enc_data->tim_handle, TIM_CHANNEL_ALL);
        HAL_TIM_IC_Start_IT(enc_data->tim_handle, TIM_CHANNEL_3); // 根据实际情况配置通道
    }
    else
    {
        return;
    }
}
/**
 * @brief ABZ编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void ABZ_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    enc_data->abz_ab_cnt = enc_data->tim_handle->Instance->CNT;
}
/**
 * @brief ABZ编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void ABZ_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    int32_t abz_ab_cnt_diff = (int32_t)enc_data->abz_z_last_ab_cnt - (int32_t)enc_data->abz_z_first_ab_cnt;
    if (MATH_ABS(abz_ab_cnt_diff) > (int32_t)(enc_data->motor_single_res * ENCODER_ABZ_ERROR_RATIO))
    {
        enc_data->abz_z_last_ab_cnt = enc_data->abz_z_first_ab_cnt; //等待下一圈更新
        enc_data->err_cnt ++;
        if (enc_data->err_cnt >= ENCODER_COMM_ERROR_MAX)
        {
            enc_data->err_cnt = ENCODER_COMM_ERROR_MAX;
            sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        }
        return;
    }
    // else if (enc_data->err_cnt > 0)
    // {
    //     enc_data->err_cnt --;
    // }

    enc_data->motor_single_raw = enc_data->abz_ab_cnt;
    enc_data->motor_single_raw >>= enc_data->motor_single_less_bits; // 降位处理
    enc_data->motor_multi_raw = 0;
    enc_data->load_single_raw = 0;
    enc_data->load_multi_raw = 0;
    enc_data->sf = 0;
    enc_data->almc = 0;
    enc_data->enid = ENCODER_CONNECTED_ID;
}

/**
 * @brief ABZ编码器Z相中断回调函数
 * @param[in] htim 定时器句柄指针
 * @retval
 */
void ENCODER_ABZ_TIM_Z_IRQ_TASK(TIM_HandleTypeDef *htim)
{
    if(htim == encoder_data[ENCODER_ID_1].tim_handle)
    {
        encoder_data[ENCODER_ID_1].abz_z_last_ab_cnt = htim->Instance->CNT;
        if(encoder_data[ENCODER_ID_1].abz_z_first_flag == true)  //第一次进入记录CNT 的值
        {
            encoder_data[ENCODER_ID_1].abz_z_first_flag = false;
            encoder_data[ENCODER_ID_1].abz_z_first_ab_cnt = encoder_data[ENCODER_ID_1].abz_z_last_ab_cnt;
        }
        // 重置CNT计数器的值为第一次记录的值，需考虑Z脉冲宽度及电机正反转进入Z相情况
        htim->Instance->CNT = encoder_data[ENCODER_ID_1].abz_z_first_ab_cnt;
    }
    else if(htim == encoder_data[ENCODER_ID_2].tim_handle)
    {
        encoder_data[ENCODER_ID_2].abz_z_last_ab_cnt = htim->Instance->CNT;
        if(encoder_data[ENCODER_ID_2].abz_z_first_flag == true)  //第一次进入记录CNT 的值
        {
            encoder_data[ENCODER_ID_2].abz_z_first_flag = false;
            encoder_data[ENCODER_ID_2].abz_z_first_ab_cnt = encoder_data[ENCODER_ID_2].abz_z_last_ab_cnt;
        }
        // 重置CNT计数器的值为第一次记录的值，需考虑Z脉冲宽度及电机正反转进入Z相情况
        htim->Instance->CNT = encoder_data[ENCODER_ID_2].abz_z_first_ab_cnt;
    }
}
#endif // ENCODER_TYPE_INC_AB_ABZ
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA
/**
 * @brief TAMAGAWA编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void TAMAGAWA_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->uart_handle = &ENCODER1_UART_HANDLE;
        enc_data->frame_len = TAMAGAWA_FRAME_LEN_ID_0;
        enc_data->cf = TAMAGAWA_CF_ID_0;
        if (PMSM_MOTOR_ENC_DIR == -1)
        {
            enc_data->options.bits.motor_dir = 1;
        }
        enc_data->motor_single_less_bits = PMSM_ENC_LINE_LESS_BITS;
        enc_data->motor_single_res = PMSM_ENC_LINE_P_N;
        enc_data->motor_multi_res = PMSM_ENC_MULTI_LINE_P_N;
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->uart_handle = &ENCODER2_UART_HANDLE;
        enc_data->frame_len = TAMAGAWA_FRAME_LEN_ID_0;
        enc_data->cf = TAMAGAWA_CF_ID_0;
        if (PMSM_LOAD_ENC_DIR == -1)
        {
            enc_data->options.bits.motor_dir = 1;
        }
        enc_data->motor_single_less_bits = PMSM_LOAD_ENC_LINE_LESS_BITS;
        enc_data->motor_single_res = PMSM_LOAD_ENC_LINE_P_N;
        enc_data->motor_multi_res = PMSM_LOAD_ENC_MULTI_LINE_P_N;
    }
    else
    {
        return;
    }
}
/**
 * @brief TAMAGAWA编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void TAMAGAWA_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    if (HAL_UART_Receive_DMA(enc_data->uart_handle, encoder_rx_buff[enc_data->id], \
                                enc_data->frame_len) != HAL_OK)
    {
        // 传输启动失败，增加错误计数
        enc_data->err_cnt++;
    }
    else
    {
        // 发送CF指令
        enc_data->uart_handle->Instance->TDR = enc_data->cf;
    }
}
/**
 * @brief TAMAGAWA编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void TAMAGAWA_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    uint8_t check_cnt_val = 0;

    // 计算数据帧校验和
    for (uint8_t i = 0; i < (enc_data->frame_len - 1); i++)
    {
        check_cnt_val ^= enc_data->data_raw[i];
    }

    // 读取状态字段和校验和
    enc_data->sf = enc_data->data_raw[1];
    enc_data->check_val = enc_data->data_raw[enc_data->frame_len - 1];

    // 检查数据帧是否有效，是否存在异常
    if (SF_HAS_ENCODER_ERR(enc_data->sf))
    {
        sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        return;
    }
    if (enc_data->check_val != check_cnt_val ||\
        enc_data->cf != enc_data->data_raw[0] ||\
        SF_HAS_COMM_ALARM(enc_data->sf))
    {
        enc_data->err_cnt ++;
        if (enc_data->err_cnt >= ENCODER_COMM_ERROR_MAX)
        {
            enc_data->err_cnt = ENCODER_COMM_ERROR_MAX;
            sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        }
        return;
    }
    else if (enc_data->err_cnt > 0)
    {
        enc_data->err_cnt --;
    }

    // 数据无异常，进一步按协议解析数据
    //sys_set_bsp_error_state((BSP_ERROR_CODE)enc_id, ERROR_CLEAR); // 自动清除编码器错误状态

    enc_data->motor_single_raw = enc_data->data_raw[2] + \
                                (enc_data->data_raw[3] << 8) + \
                                (enc_data->data_raw[4] << 16);
    enc_data->motor_single_raw >>= enc_data->motor_single_less_bits;
    enc_data->motor_multi_raw = 0;
    enc_data->load_single_raw = 0;
    enc_data->load_multi_raw = 0;
    enc_data->almc = 0;
    enc_data->enid = ENCODER_CONNECTED_ID;
}
#endif // ENCODER_TYPE_ABS_RS485_TAMAGAWA
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX
/**
 * @brief KTM59XX编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void KTM59XX_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->spi_handle = &ENCODER1_SPI_HANDLE;
        enc_data->frame_len = KTM59XX_FRAME_LEN_ID_3;
        enc_data->cf = KTM59XX_CF_ID_3;
        if (PMSM_MOTOR_ENC_DIR == -1)
        {
            enc_data->options.bits.motor_dir = 1;
        }
        enc_data->motor_single_less_bits = PMSM_ENC_LINE_LESS_BITS;
        enc_data->motor_single_res = PMSM_ENC_LINE_P_N;
        enc_data->motor_multi_res = PMSM_ENC_MULTI_LINE_P_N;
        // 首字节为cf，其他字节均为0
        encoder_tx_buff[enc_data->id][0] = enc_data->cf;
        for (uint8_t i = 1; i < enc_data->frame_len; i++)
        {
            encoder_tx_buff[enc_data->id][i] = 0x00;
        }
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->spi_handle = &ENCODER2_SPI_HANDLE;
        enc_data->frame_len = KTM59XX_FRAME_LEN_ID_3;
        enc_data->cf = KTM59XX_CF_ID_3;
        if (PMSM_LOAD_ENC_DIR == -1)
        {
            enc_data->options.bits.motor_dir = 1;
        }
        enc_data->motor_single_less_bits = PMSM_LOAD_ENC_LINE_LESS_BITS;
        enc_data->motor_single_res = PMSM_LOAD_ENC_LINE_P_N;
        enc_data->motor_multi_res = PMSM_LOAD_ENC_MULTI_LINE_P_N;
        // 首字节为cf，其他字节均为0
        encoder_tx_buff[enc_data->id][0] = enc_data->cf;
        for (uint8_t i = 1; i < enc_data->frame_len; i++)
        {
            encoder_tx_buff[enc_data->id][i] = 0x00;
        }
    }
    else
    {
        return;
    }
}
/**
 * @brief KTM59XX编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void KTM59XX_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    if (HAL_SPI_TransmitReceive_DMA(enc_data->spi_handle, encoder_tx_buff[enc_data->id], \
                                    encoder_rx_buff[enc_data->id], enc_data->frame_len) != HAL_OK)
    {
        // 传输启动失败，增加错误计数
        enc_data->err_cnt++;
    }
}
/**
 * @brief KTM59XX编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void KTM59XX_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    uint64_t frame_data = 0;

    for (uint8_t i = 0; i < enc_data->frame_len; i++)
    {
        frame_data <<= 8;
        frame_data |= enc_data->data_raw[i];
    }

    if (KTM59XX_Encoder_Crc8_Check(frame_data, KTM59xx_FRAME_LEN_DATA_BW) == false)
    {
        enc_data->err_cnt ++;
        if (enc_data->err_cnt >= ENCODER_COMM_ERROR_MAX)
        {
            enc_data->err_cnt = ENCODER_COMM_ERROR_MAX;
            sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        }
        return;
    }
    else if (enc_data->err_cnt > 0)
    {
        enc_data->err_cnt --;
    }

    enc_data->motor_single_raw = (uint32_t)((frame_data << KTM59xx_FRAME_LEN_RC_BW) >> \
                                            (KTM59xx_FRAME_LEN_RX_BW - KTM59xx_FRAME_LEN_ANGLE_BW));
    enc_data->motor_single_raw >>= enc_data->motor_single_less_bits; // 降位处理
    enc_data->motor_multi_raw = 0;
    enc_data->load_single_raw = 0;
    enc_data->load_multi_raw = 0;
    enc_data->sf = (uint8_t)((frame_data << (KTM59xx_FRAME_LEN_RC_BW + KTM59xx_FRAME_LEN_ANGLE_BW)) >> \
                                (KTM59xx_FRAME_LEN_RX_BW - KTM59xx_FRAME_LEN_STATUS_BW));
    enc_data->almc = 0;
    enc_data->enid = ENCODER_CONNECTED_ID;
}
/**
 * @brief KTM59XX编码器CRC8校验
 * @param[in] input 待校验数据
 * @param[in] len 校验数据位宽
 * @retval true 校验成功 false 校验失败
 */
static inline bool KTM59XX_Encoder_Crc8_Check(uint64_t input, int32_t len)
{
    input >>= 56 - len;
    uint64_t data = input;
    input &= 0xFFFFFFFFFFFFFF00;
    uint64_t inputTemp = input;
    uint64_t mark = 0x8000000000000000;
    uint64_t ploy = 0x8380000000000000;
    ploy >>= 56 - len;
    mark >>= 56 - len;

    for (int32_t i = 0; i < len; i++)
    {
        if ((input & mark) != 0)
        {
            input ^= ploy;
        }

        mark >>= 1;
        ploy >>= 1;
    }

    inputTemp += (input ^ KTM5XXX_CRC8_FINAL_XOR) & 0xFF;
    return (inputTemp == data) ? true : false;
}
#endif // ENCODER_TYPE_ABS_SPI_KTM59XX
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S
/**
 * @brief SMC40S编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void SMC40S_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->spi_handle = &ENCODER1_SPI_HANDLE;
        enc_data->frame_len = SMC40S_FRAME_LEN_ID_0;
        enc_data->cf = SMC40S_CF_ID_0;
        if (PMSM_MOTOR_ENC_DIR == -1)
        {
            enc_data->options.bits.motor_dir = 1;
        }
        enc_data->motor_single_less_bits = PMSM_ENC_LINE_LESS_BITS;
        enc_data->motor_single_res = PMSM_ENC_LINE_P_N;
        enc_data->motor_multi_res = PMSM_ENC_MULTI_LINE_P_N;
        for (uint8_t i = 0; i < enc_data->frame_len; i++)
        {
            encoder_tx_buff[enc_data->id][i] = enc_data->cf;
        }
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->spi_handle = &ENCODER2_SPI_HANDLE;
        enc_data->frame_len = SMC40S_FRAME_LEN_ID_0;
        enc_data->cf = SMC40S_CF_ID_0;
        if (PMSM_LOAD_ENC_DIR == -1)
        {
            enc_data->options.bits.motor_dir = 1;
        }
        enc_data->motor_single_less_bits = PMSM_LOAD_ENC_LINE_LESS_BITS;
        enc_data->motor_single_res = PMSM_LOAD_ENC_LINE_P_N;
        enc_data->motor_multi_res = PMSM_LOAD_ENC_MULTI_LINE_P_N;
        for (uint8_t i = 0; i < enc_data->frame_len; i++)
        {
            encoder_tx_buff[enc_data->id][i] = enc_data->cf;
        }
    }
    else
    {
        return;
    }
}
/**
 * @brief SMC40S编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void SMC40S_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    if (HAL_SPI_TransmitReceive_DMA(enc_data->spi_handle, encoder_tx_buff[enc_data->id], \
                                    encoder_rx_buff[enc_data->id], enc_data->frame_len) != HAL_OK)
    {
        // 传输启动失败，增加错误计数
        enc_data->err_cnt++;
    }
}
/**
 * @brief SMC40S编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void SMC40S_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    uint32_t frame_data = 0;
    // uint8_t frame_crc = 0;
    // uint32_t frame_check_data = 0;

    for (uint8_t i = 0; i < enc_data->frame_len; i++)
    {
        frame_data <<= 8;
        frame_data |= enc_data->data_raw[i];
    }

    // frame_crc = (~enc_data->data_raw[enc_data->frame_len - 1] ) & (((uint8_t)1 << SMC40S_FRAME_LEN_CRC_BW) - 1);
    // frame_check_data = (frame_data >> SMC40S_FRAME_LEN_CRC_BW) & (((uint32_t)1 << (SMC40S_FRAME_LEN_TOTAL_BW - SMC40S_FRAME_LEN_CRC_BW)) - 1);

    // if (BISSC_Crc6_Calc(frame_check_data, (SMC40S_FRAME_LEN_TOTAL_BW - SMC40S_FRAME_LEN_CRC_BW), SMC40S_CRC6_FINAL_XOR) != frame_crc)
    // {
    //     // CRC校验失败，增加错误计数
    //     enc_data->err_cnt++;
    //     return;
    // }
    // else if (enc_data->err_cnt > 0)
    // {
    //     enc_data->err_cnt --;
    // }

    enc_data->motor_single_raw = (uint32_t)(frame_data >> (SMC40S_FRAME_LEN_TOTAL_BW - SMC40S_FRAME_LEN_DATA_BW));
    enc_data->motor_single_raw >>= enc_data->motor_single_less_bits; // 降位处理
    enc_data->motor_multi_raw = 0;
    enc_data->load_single_raw = 0;
    enc_data->load_multi_raw = 0;
    enc_data->sf = (frame_data >> (SMC40S_FRAME_LEN_CRC_BW + SMC40S_FRAME_LEN_WARNING_BW)) & (((uint8_t)1 << SMC40S_FRAME_LEN_ERROR_BW) - 1);
    enc_data->almc = (frame_data >> SMC40S_FRAME_LEN_CRC_BW) & (((uint8_t)1 << SMC40S_FRAME_LEN_WARNING_BW) - 1);
    enc_data->enid = ENCODER_CONNECTED_ID;
}
/**
 * @brief BISSC编码器CRC6校验值计算
 * @param[in] data 待校验数据
 * @param[in] bit_len 校验数据位宽
 * @param[in] final_xor 最终异或值
 * @retval uint8_t CRC6校验值
 */
// static inline uint8_t BISSC_Crc6_Calc(uint32_t data, uint8_t bit_len, uint8_t final_xor)
// {
//     uint8_t crc = 0x00;  // 起始值
//     for (int i = bit_len - 1; i >= 0; i--) {  // MSB先行
//         uint8_t bit = (data >> i) & 0x01;
//         crc ^= (bit << 5);  // 最高位对齐
//         if (crc & 0x20) {   // 第6位为1
//             crc = (crc << 1) ^ final_xor;  // 多项式
//         } else {
//             crc <<= 1;
//         }
//         crc &= 0x3F;  // 保持6位
//     }
//     return crc ^ 0x3F;  // 输出反转（0x3F=6位全1）
// }
#endif // ENCODER_TYPE_ABS_BISSC_SMC40S
