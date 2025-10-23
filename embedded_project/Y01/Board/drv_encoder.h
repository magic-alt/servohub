#ifndef DRV_ENCODER_H
#define DRV_ENCODER_H

#include "board.h"

// 编码器参数定义
#define ENCODER_FRAME_MAX_LEN   16  // 数据帧最大帧长度
#define ENCODER_COMM_ERROR_MAX  20  // 编码器连续通信错误最大次数

typedef enum : uint8_t
{
    ENCODER_CF_INIT  = 0x00,        // 初始值
    // 多摩川编码器 CF_ID 宏定义（协议标准值）
    TAMAGAWA_CF_ID_0 = 0x02,        // 读取单圈数据（ABS0 ABS1 ABS2）
    TAMAGAWA_CF_ID_1 = 0x8A,        // 读取多圈数据（ABM0 ABM1 ABM2）
    TAMAGAWA_CF_ID_2 = 0x92,        // 读取编码器ID（ENID）
    TAMAGAWA_CF_ID_3 = 0x1A,        // 读取所有数据（ABS + ENID + ABM + ALMC）
    TAMAGAWA_CF_ID_4 = 0xA2,        // 读取单圈扩展数据（ABS0-ABS3）
    TAMAGAWA_CF_ID_5 = 0x2A,        // 读取单圈 + 多圈扩展数据（ABS0-ABS3 + ABM0-ABM1）
    TAMAGAWA_CF_ID_7 = 0xBA,        // 复位单圈计数 + 清除错误
    TAMAGAWA_CF_ID_8 = 0xC2,        // 复位单圈计数
    TAMAGAWA_CF_ID_C = 0x62,        // 复位多圈计数 + 清除错误
    TAMAGAWA_CF_ID_6 = 0x32,        // 写入EEPROM
    TAMAGAWA_CF_ID_D = 0xEA,        // 从EEPROM读取

    // 其他编码器类型
    // ...
} EncoderCf_t; // 编码器控制字段

typedef enum : uint8_t
{
    ENCODER_FRAME_LEN_INIT  = 0,    // 初始值
    // 多摩川编码器各CF_ID对应的帧长度（单位：字节）
    TAMAGAWA_FRAME_LEN_ID_0 = 6,    // TAMAGAWA_CF_ID_0：读取单圈数据（ABS0 ABS1 ABS2）
    TAMAGAWA_FRAME_LEN_ID_1 = 6,    // TAMAGAWA_CF_ID_1：读取多圈数据（ABM0 ABM1 ABM2）
    TAMAGAWA_FRAME_LEN_ID_2 = 2,    // TAMAGAWA_CF_ID_2：读取编码器ID（ENID）
    TAMAGAWA_FRAME_LEN_ID_3 = 13,   // TAMAGAWA_CF_ID_3：读取所有数据（ABS + ENID + ABM + ALMC）
    TAMAGAWA_FRAME_LEN_ID_4 = 7,    // TAMAGAWA_CF_ID_4：读取单圈扩展数据（ABS0-ABS3）
    TAMAGAWA_FRAME_LEN_ID_5 = 9,    // TAMAGAWA_CF_ID_5：读取单圈 + 多圈扩展数据（ABS0-ABS3 + ABM0-ABM1）
    TAMAGAWA_FRAME_LEN_ID_7 = 2,    // TAMAGAWA_CF_ID_7：复位单圈计数 + 清除错误
    TAMAGAWA_FRAME_LEN_ID_8 = 2,    // TAMAGAWA_CF_ID_8：复位单圈计数
    TAMAGAWA_FRAME_LEN_ID_C = 2,    // TAMAGAWA_CF_ID_C：复位多圈计数 + 清除错误
    TAMAGAWA_FRAME_LEN_ID_6 = 4,    // TAMAGAWA_CF_ID_6：写入EEPROM
    TAMAGAWA_FRAME_LEN_ID_D = 4,    // TAMAGAWA_CF_ID_D：从EEPROM读取

    // 其他编码器类型
    // ...
} EncoderFrameLen_t; // 编码器数据帧长度

typedef union
{
    uint8_t val;
    struct
    {
        uint8_t motor_dir : 1;        // bit0：电机端计数方向 0-默认, 1-取反
        uint8_t load_dir : 1;         // bit1：负载端计数方向 0-默认, 1-取反
        uint8_t turns_overflow_0 : 1; // bit2：多圈值溢出坐标为0/分辨率选项
        uint8_t l_cnt_2_m_turns : 1;  // bit3：负载端单圈作为值电机端多圈值选项

        uint8_t reserved : 4;
    } bits;
} Options_t; // 编码器配置选项

typedef struct
{
    uint8_t data_raw[ENCODER_FRAME_MAX_LEN];    // 编码器数据帧
    EncoderFrameLen_t frame_len;                // 数据帧长度
    EncoderCf_t cf;                             // 控制字段
    uint8_t sf;                                 // 状态字段
    uint8_t almc;                               // 错误状态字段
    uint8_t enid;                               // 编码器ID
    uint8_t check_val;                          // 编码器校验值
    uint8_t err_cnt;                            // 错误计数
    Options_t options;                          // 编码器配置选项
    uint32_t motor_single_res;                  // 电机端单圈分辨率
    uint32_t motor_multi_res;                   // 电机端多圈分辨率
    uint32_t load_single_res;                   // 负载端单圈分辨率
    uint32_t load_multi_res;                    // 负载端多圈分辨率
    uint32_t motor_single_raw;                  // 电机端单圈绝对值原始数据
    int64_t motor_multi_raw;                    // 电机端多圈绝对值原始数据
    uint32_t load_single_raw;                   // 负载端单圈绝对值原始数据
    int64_t load_multi_raw;                     // 负载端多圈绝对值原始数据
    volatile uint32_t single_cnt;               // 编码器单圈值
    volatile int64_t multi_turns;               // 编码器多圈值
    uint32_t real_motor_turns_res;              // 实际电机端编码器多圈分辨率
} EncoderDataInfo_t;

// 多摩川编码器数据参数定义
// SF字段固定位定义（共10位，bit0为最低位，bit9为最高位）
#define SF_START_BIT          0x001  // 第0位：起始位，固定为1（文档6.3.2）
#define SF_INFORMATION        0x000  // 第1-4位：信息位，固定为0000（文档6.3.2）
#define SF_DELIMITER          0x200  // 第9位：分隔符，固定为1（文档6.3.2）
#define SF_TOTAL_BITS         10     // SF字段总位数
#define SF_ENCODER_ERR_MASK   0x030  // 第5-6位：编码器错误掩码（ea0=bit5，ea1=bit6）
#define SF_COMM_ALARM_MASK    0x0C0  // 第7-8位：通信告警掩码（ca0=bit7，ca1=bit8）
// 编码器错误（Encoder Error，ea0/ea1）宏定义（文档6.3.2）
#define SF_ERR_NONE           0x000  // 无编码器错误（ea0=0，ea1=0）
#define SF_ERR_COUNTING       0x020  // 计数错误（CE，ea0=1，bit5=1）
#define SF_ERR_MT_BAT         0x010  // 多圈/电池错误（ME+BE+BA的或逻辑，ea1=1，bit6=1）
#define SF_ERR_ALL_ENCODER    (SF_ERR_COUNTING | SF_ERR_MT_BAT)  // 所有编码器错误
// 通信告警（Communication Alarm，ca0/ca1）宏定义（文档6.3.2）
#define SF_ALARM_NONE         0x000  // 无通信错误（ca0=0，ca1=0）
#define SF_ALARM_PARITY       0x080  // 请求帧校验错误（ca0=1，bit7=1）
#define SF_ALARM_DELIMITER    0x040  // 请求帧分隔符错误（ca1=1，bit8=1）
#define SF_ALARM_ALL_COMM     (SF_ALARM_PARITY | SF_ALARM_DELIMITER)  // 所有通信告警
// 检查是否存在编码器错误（ea0/ea1）
#define SF_HAS_ENCODER_ERR(sf_data) ((sf_data) & SF_ERR_ALL_ENCODER)
// 检查是否存在计数错误（CE）
#define SF_HAS_COUNTING_ERR(sf_data) ((sf_data) & SF_ERR_COUNTING)
// 检查是否存在多圈/电池错误（ME/BE/BA）
#define SF_HAS_MT_BAT_ERR(sf_data)   ((sf_data) & SF_ERR_MT_BAT)
// 检查是否存在通信错误（ca0/ca1）
#define SF_HAS_COMM_ALARM(sf_data)  ((sf_data) & SF_ALARM_ALL_COMM)
// 检查是否存在通信校验错误
#define SF_HAS_PARITY_ALARM(sf_data) ((sf_data) & SF_ALARM_PARITY)
// 检查是否存在通信分隔符错误
#define SF_HAS_DELIM_ALARM(sf_data)  ((sf_data) & SF_ALARM_DELIMITER)

// 编码器ID (固定值)
#define TAMAGAWA_ENCODER_ID 0x00    // 不读取编码器ID，使用0替代

void encoder_data_init(void);
void encoder_data_read(void);
void encoder_data_process(void);
uint32_t get_encoder_cnt(ENCODER_ID const enc_id);
int64_t get_encoder_turns(ENCODER_ID const enc_id);
bool get_encoder_status(ENCODER_ID const enc_id);
void set_encoder_options(ENCODER_ID enc_id, uint8_t const options);
#endif // DRV_ENCODER_H
