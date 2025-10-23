#include "drv_encoder.h"

// 编码器接收数据缓冲区
__attribute__((section(".RAM_D1"))) volatile uint8_t encoder_receive_buffer[ENCODER_NUM][ENCODER_FRAME_MAX_LEN];

EncoderDataInfo_t encoder_data[ENCODER_NUM] = {
    [ENCODER_ID_1 ... ENCODER_ID_MAX] = {
        .data_raw = { 0 },
        .frame_len = ENCODER_FRAME_LEN_INIT,
        .cf = ENCODER_CF_INIT,
        .sf = 0,
        .almc = 0,
        .enid = 0,
        .check_val = 0,
        .err_cnt = 0,
        .options.val = 0,
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
        .real_motor_turns_res = 0
    }
};

/**
 * @brief 初始化编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及接口，初始化编码器数据
 */
void encoder_data_init(void)
{
    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id < ENCODER_ID_MAXIMUN; enc_id ++)
    {
        if (enc_id == ENCODER_ID_1)
        {
            encoder_data[enc_id].frame_len = TAMAGAWA_FRAME_LEN_ID_0;
            encoder_data[enc_id].cf = TAMAGAWA_CF_ID_0;
            encoder_data[enc_id].motor_single_res = PMSM_ENC_LINE_P_N;
            encoder_data[enc_id].motor_multi_res = PMSM_ENC_MULTI_LINE_P_N;
        }
        else// if (enc_id == ENCODER_ID_2)
        {
            return;
        }
    }
}

/**
 * @brief 读取编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及接口，读取编码器数据
 */
void encoder_data_read(void)
{
    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id < ENCODER_ID_MAXIMUN; enc_id ++)
    {
        if (enc_id == ENCODER_ID_1)
        {
            // 转存上周期读取的编码器器数据
            for (uint8_t i = 0; i < encoder_data[enc_id].frame_len; i++)
            {
                encoder_data[enc_id].data_raw[i] = encoder_receive_buffer[enc_id][i];
                encoder_receive_buffer[enc_id][i] = 0;
            }
            // 启动DMA接收
            HAL_UART_Receive_DMA(&ENCODER1_UART_HANDLE,\
                                (uint8_t *)encoder_receive_buffer[enc_id],\
                                encoder_data[enc_id].frame_len);
            // 发送控制命令
            ENCODER1_UART_HANDLE.Instance->TDR = encoder_data[enc_id].cf;
        }
        else// if (enc_id == ENCODER_ID_2)
        {
            return;
        }
    }
}

/**
 * @brief 处理编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及协议，解析编码器数据
 */
//volatile uint8_t check_val = 0;
void encoder_data_process(void)
{
    uint8_t check_cnt_val = 0;
    uint32_t u32_calc_temp = 0;
    int64_t i64_calc_temp = 0;

    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id < ENCODER_ID_MAXIMUN; enc_id ++)
    {
        // 按各自编码器协议对应解析
        if (enc_id == ENCODER_ID_1)
        {
            // 计算数据帧校验和
            for (uint8_t i = 0; i < (encoder_data[enc_id].frame_len - 1); i++)
            {
                check_cnt_val ^= encoder_data[enc_id].data_raw[i];
            }

            // 读取状态字段和校验和
            encoder_data[enc_id].sf = encoder_data[enc_id].data_raw[1];
            encoder_data[enc_id].check_val = encoder_data[enc_id].data_raw[encoder_data[enc_id].frame_len - 1];

            // 检查数据帧是否有效，是否存在异常
            if (SF_HAS_ENCODER_ERR(encoder_data[enc_id].sf))
            {
                //set_bsp_error_state(ERROR_ENCODER_MOTOR, ERROR_SET);
                return;
            }
            if (encoder_data[enc_id].check_val != check_cnt_val ||\
                encoder_data[enc_id].cf != encoder_data[enc_id].data_raw[0] ||\
                SF_HAS_COMM_ALARM(encoder_data[enc_id].sf))
            {
                encoder_data[enc_id].err_cnt ++;
                if (encoder_data[enc_id].err_cnt >= ENCODER_COMM_ERROR_MAX)
                {
                    encoder_data[enc_id].err_cnt = ENCODER_COMM_ERROR_MAX;
                    //set_bsp_error_state(ERROR_ENCODER_MOTOR, ERROR_SET);
                }
                return;
            }
            else if (encoder_data[enc_id].err_cnt > 0)
            {
                encoder_data[enc_id].err_cnt --;
            }

            // 数据无异常，进一步按协议解析数据
            //set_bsp_error_state(ERROR_ENCODER_MOTOR, ERROR_CLEAR); // 自动清除编码器错误状态

            encoder_data[enc_id].motor_single_raw = encoder_data[enc_id].data_raw[2] + \
                                                (encoder_data[enc_id].data_raw[3] << 8) + \
                                                (encoder_data[enc_id].data_raw[4] << 16);
            encoder_data[enc_id].motor_single_raw &= (encoder_data[enc_id].motor_single_res - 1);
            encoder_data[enc_id].motor_multi_raw = 0;
            encoder_data[enc_id].load_single_raw = 0;
            encoder_data[enc_id].load_multi_raw = 0;
            encoder_data[enc_id].almc = 0;
            encoder_data[enc_id].enid = 0;
        }
        else// if (enc_id == ENCODER_ID_2)
        {
            break; // 单编码器（电机端 或 电机端+负载端）模式，不解析编码器2（负载端）数据
        }

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
    encoder_data[ENCODER_ID_MOTOR].multi_turns = 0;
    encoder_data[ENCODER_ID_LOAD].single_cnt = encoder_data[ENCODER_ID_1].motor_single_raw;
    encoder_data[ENCODER_ID_LOAD].multi_turns = 0;
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
        if (encoder_data[enc_id].enid == TAMAGAWA_ENCODER_ID && \
            encoder_data[enc_id].err_cnt < ENCODER_COMM_ERROR_MAX)
        {
            return true;
        }
    }
    else// if (enc_id == ENCODER_ID_2)
    {
        return true;
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
