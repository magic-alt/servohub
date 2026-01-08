#ifndef DRV_ENCODER_H
#define DRV_ENCODER_H

#include "board.h"

// 编码器类型/型号定义
#define ENCODER_TYPE_NONE               0x00 // 无编码器
#define ENCODER_TYPE_INC_AB_ABZ         0x01 // 增量式通用AB/ABZ编码器，注：由于Y01硬件单接口，只可配置电机端/负载端任选一端
#define ENCODER_TYPE_ABS_RS485_TAMAGAWA 0x02 // 绝对式通用RS485多摩川编码器
#define ENCODER_TYPE_ABS_SPI_KTM59XX    0x03 // 绝对式SPI KTM59xx 编码器
#define ENCODER_TYPE_ABS_BISSC_SMC40S   0x04 // 绝对式SPI BISS-C SMC40S 编码器
// 其他编码器类型
// ...

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

    // KTM59xx编码器 CF_ID（bit31~24） 宏定义（协议标准值）
    KTM59XX_CF_ID_1 = 0x5B,         // 指令1：控制寄存器写入
    KTM59XX_CF_ID_2 = 0x62,         // 指令2：控制寄存器读取
    KTM59XX_CF_ID_3 = 0x23,         // 指令3：角度和内部信号读取

    KTM59XX_REG_ADD_CALIB = 0xA0,       // 校准寄存器地址
    KTM59XX_REG_VAL_CALIB_OFF = 0x00,   // 校准寄存器值：关闭校准

    // BISSC SMC40S BISS-C编码器 宏定义
    SMC40S_CF_ID_0 = 0x00,          // 读取单圈数据，无需命令

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
    TAMAGAWA_FRAME_LEN_ID_3 = 11,   // TAMAGAWA_CF_ID_3：读取所有数据（ABS + ENID + ABM + ALMC）
    TAMAGAWA_FRAME_LEN_ID_4 = 7,    // TAMAGAWA_CF_ID_4：读取单圈扩展数据（ABS0-ABS3）
    TAMAGAWA_FRAME_LEN_ID_5 = 9,    // TAMAGAWA_CF_ID_5：读取单圈 + 多圈扩展数据（ABS0-ABS3 + ABM0-ABM1）
    TAMAGAWA_FRAME_LEN_ID_7 = 2,    // TAMAGAWA_CF_ID_7：复位单圈计数 + 清除错误
    TAMAGAWA_FRAME_LEN_ID_8 = 2,    // TAMAGAWA_CF_ID_8：复位单圈计数
    TAMAGAWA_FRAME_LEN_ID_C = 2,    // TAMAGAWA_CF_ID_C：复位多圈计数 + 清除错误
    TAMAGAWA_FRAME_LEN_ID_6 = 4,    // TAMAGAWA_CF_ID_6：写入EEPROM
    TAMAGAWA_FRAME_LEN_ID_D = 4,    // TAMAGAWA_CF_ID_D：从EEPROM读取

    // KTM59xx编码器各CF_ID对应的帧长度（单位：字节）
    KTM59XX_FRAME_LEN_ID_1 = 4,    // KTM59XX_CF_ID_1：控制寄存器写入
    KTM59XX_FRAME_LEN_ID_2 = 4,    // KTM59XX_CF_ID_2：控制寄存器读取
    KTM59XX_FRAME_LEN_ID_3 = 8,    // KTM59XX_CF_ID_3：角度和内部信号读取

    KTM59xx_FRAME_LEN_TX = 8,    // KTM59xx 数据帧发送长度
    KTM59xx_FRAME_LEN_TX_BW = 8 * KTM59xx_FRAME_LEN_TX,
    KTM59xx_FRAME_LEN_RX = 8,    // KTM59xx 数据帧接收长度
    KTM59xx_FRAME_LEN_RX_BW = 8 * KTM59xx_FRAME_LEN_RX,
    KTM59xx_FRAME_LEN_ANGLE_BW = 24,    // KTM59xx 角度数据位宽
    KTM59xx_FRAME_LEN_RC_BW = 0,        // KTM59xx 内部信号数据位宽
    KTM59xx_FRAME_LEN_STATUS_BW = 2,    // KTM59xx 状态数据位宽
    KTM59xx_FRAME_LEN_CRC_BW = 8,       // KTM59xx CRC校验位宽
    KTM59xx_FRAME_LEN_DATA_BW = KTM59xx_FRAME_LEN_ANGLE_BW + KTM59xx_FRAME_LEN_RC_BW + KTM59xx_FRAME_LEN_STATUS_BW, // KTM59xx 数据帧数据位宽
    KTM59xx_FRAME_LEN_TOTAL_BW = KTM59xx_FRAME_LEN_DATA_BW + KTM59xx_FRAME_LEN_CRC_BW, // KTM59xx 数据帧总位宽

    // BISSC SMC40S BISS-C编码器 各CF_ID对应的帧长度（单位：字节）
    SMC40S_FRAME_LEN_ID_0 = 4,           // SMC40S_CF_ID_0：读取单圈数据

    SMC40S_FRAME_LEN_ACK_BW = 6,         // SMC40S 数据帧应答位宽
    SMC40S_FRAME_LEN_START_BW = 1,       // SMC40S 数据帧起始位宽
    SMC40S_FRAME_LEN_CDS_BW = 1,         // SMC40S 数据帧命令位宽
    SMC40S_FRAME_LEN_DATA_BW = 19,       // SMC40S 数据帧数据位宽
    SMC40S_FRAME_LEN_ERROR_BW = 1,       // SMC40S 数据帧错误位宽
    SMC40S_FRAME_LEN_WARNING_BW = 1,     // SMC40S 数据帧警告位宽
    SMC40S_FRAME_LEN_CRC_BW = 6,         // SMC40S 数据帧CRC校验位宽
    SMC40S_FRAME_LEN_TOTAL_BW = SMC40S_FRAME_LEN_DATA_BW + SMC40S_FRAME_LEN_ERROR_BW + SMC40S_FRAME_LEN_WARNING_BW + SMC40S_FRAME_LEN_CRC_BW, // SMC40S 数据帧总位宽

    // 其他编码器类型
    // ...
} EncoderFrameLen_t; // 编码器数据帧长度

typedef union
{
    uint8_t val;
    struct
    {
        uint8_t a_dir : 1;              // bit0：编码器A计数方向 0-默认, 1-取反
        uint8_t b_dir : 1;              // bit1：编码器B计数方向 0-默认, 1-取反
        uint8_t turns_overflow_0 : 1;   // bit2：多圈值溢出坐标为0/分辨率选项
        uint8_t l_cnt_2_m_turns : 1;    // bit3：负载端单圈作为值电机端多圈值选项

        uint8_t reserved : 4;
    } bits;
} Options_t; // 编码器配置选项

typedef struct EncoderDataInfo_t EncoderDataInfo_t;
struct EncoderDataInfo_t
{
    ENCODER_ID id;                              // 编码器编号
    uint8_t type;                               // 编码器类型

    TIM_HandleTypeDef *tim_handle;              // TIM句柄指针
    UART_HandleTypeDef *uart_handle;            // UART句柄指针
    SPI_HandleTypeDef *spi_handle;              // SPI句柄指针

    uint32_t abz_ab_cnt;                        // ABZ编码器AB相计数值
    bool abz_z_first_flag;                      // ABZ编码器Z相首次计数值标志位
    uint32_t abz_z_first_ab_cnt;                // ABZ编码器Z相首次计数值
    uint32_t abz_z_last_ab_cnt;                 // ABZ编码器Z相末次计数值
    uint8_t data_raw[ENCODER_FRAME_MAX_LEN];    // 编码器数据帧
    EncoderFrameLen_t frame_len;                // 数据帧长度
    EncoderCf_t cf;                             // 控制字段
    uint8_t sf;                                 // 状态字段
    uint8_t almc;                               // 错误状态字段
    uint8_t enid;                               // 编码器ID
    uint8_t check_val;                          // 编码器校验值
    uint8_t err_cnt;                            // 错误计数

    Options_t options;                          // 编码器配置选项
    // 一个常规编码器含一套位置反馈数据，仅使用编码器A相关参数
    // 一个特殊编码器含两套位置反馈数据，分别对应编码器A和B相关参数
    uint32_t a_single_res;                      // 编码器A单圈分辨率
    uint32_t a_single_less_factor;              // 编码器A单圈分辨率缩降倍数
    uint32_t a_multi_res;                       // 编码器A多圈分辨率
    uint32_t a_single_raw;                      // 编码器A单圈绝对值原始数据
    int64_t  a_multi_raw;                       // 编码器A多圈绝对值原始数据
    uint32_t b_single_res;                      // 编码器B单圈分辨率
    uint32_t b_single_less_factor;              // 编码器B单圈分辨率缩降倍数
    uint32_t b_multi_res;                       // 编码器B多圈分辨率
    uint32_t b_single_raw;                      // 编码器B单圈绝对值原始数据
    int64_t  b_multi_raw;                       // 编码器B多圈绝对值原始数据
    // 编码器单圈值和多圈值为实际电机或负载端的位置反馈值
    volatile uint32_t single_cnt;               // 编码器单圈值
    volatile int64_t multi_turns;               // 编码器多圈值

    uint32_t real_motor_turns_res;              // 实际电机端编码器多圈分辨率

    void (*init)(EncoderDataInfo_t *enc_data);  // 编码器初始化函数指针
    void (*read)(EncoderDataInfo_t *enc_data);  // 编码器数据读取函数指针
    void (*process)(EncoderDataInfo_t *enc_data); // 编码器数据处理函数指针
};

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
#define ENCODER_CONNECTED_ID        (0xCE)  // 当未读取编码器ID时，位置解析成功后强制设为0xCE（Connected Encoder）
// 编码器校验值最终异或值
#define KTM5XXX_CRC8_FINAL_XOR      (0xFF)  // KTM5XXX校验值最终异或值
#define SMC40S_CRC6_FINAL_XOR       (0x43)  // SMC40S校验值最终异或值

// 其他参数
#define ENCODER_ABZ_ERROR_RATIO     (0.05f) // 编码器ABZ通信错误最大偏差比例（基于分辨率）

void EncoderDataInit(void);
void EncoderDataRead(void);
void EncoderDataProcess(void);

uint32_t get_encoder_cnt(ENCODER_ID const enc_id);
int64_t get_encoder_turns(ENCODER_ID const enc_id);
bool get_encoder_status(ENCODER_ID const enc_id);
void set_encoder_options(ENCODER_ID enc_id, uint8_t const options);
void set_encoder_a_resolution(ENCODER_ID const enc_id, uint32_t const single_res, \
                                  uint32_t const multi_res, uint32_t const single_less_factor);
void set_encoder_b_resolution(ENCODER_ID const enc_id, uint32_t const single_res, \
                                  uint32_t const multi_res, uint32_t const single_less_factor);

#endif // DRV_ENCODER_H
