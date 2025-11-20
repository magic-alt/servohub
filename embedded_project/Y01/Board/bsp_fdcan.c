#include "bsp_fdcan.h"

static FDCAN_DeviceTypeDef bsp_fdcan = {
    .handle = &CAN_FDCAN_HANDLE,        // 绑定FDCAN句柄
    .id = 0x15,                         // 默认CAN ID
    .baudrate = FDCAN_BAUDRATE_1M_BPS,  // 默认波特率1Mbps
    .mg_counts = 0,                     // 初始计数0
};

/**
 * @brief 获取FDCAN驱动实例
 * @return FDCAN_DeviceTypeDef* FDCAN驱动实例指针
 */
FDCAN_DeviceTypeDef* fdcan_get_bsp_fdcan(void)
{
    return &bsp_fdcan;
}

/**
 * @brief 初始化FDCAN
 * @details 1. 配置接收滤波器
 *          2. 配置全局滤波规则（拒绝不匹配帧和远程帧）
 *          3. 启动FDCAN模块并激活接收中断
 */
void fdcan_init(void)
{
#ifdef USE_CANOPEN
    // CANopen协议，节点号最大为127
    if (bsp_fdcan.id > 0x7F)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
        return;
    }
    bsp_fdcan.sFilterConfig.FilterID1 = bsp_fdcan.id;               // 基准ID：高4位任意（设为0），低7位为目标节点号
    bsp_fdcan.sFilterConfig.FilterID2 = 0x07F;                      // 掩码：高4位0（不关心功能码），低7位1（严格匹配节点号）
#else //其他CAN协议
    bsp_fdcan.sFilterConfig.FilterID1 = 0x000;                      // 过滤ID（掩码模式下为基准ID）
    bsp_fdcan.sFilterConfig.FilterID2 = 0x000;                      // 掩码为0，不过滤任何ID
    // 初始化发送帧头
    bsp_fdcan.tx_header.Identifier = bsp_fdcan.id;                  // 发送ID使用当前设备ID
    bsp_fdcan.tx_header.IdType = FDCAN_STANDARD_ID;                 // 标准ID
    bsp_fdcan.tx_header.TxFrameType = FDCAN_DATA_FRAME;             // 数据帧
    bsp_fdcan.tx_header.DataLength = FDCAN_DLC_BYTES_8;             // 数据长度8字节
    bsp_fdcan.tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;     // 错误状态指示激活
    bsp_fdcan.tx_header.BitRateSwitch = FDCAN_BRS_OFF;              // 关闭波特率切换
    bsp_fdcan.tx_header.FDFormat = FDCAN_CLASSIC_CAN;               // 传统CAN模式
    bsp_fdcan.tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;    // 不使用发送事件FIFO
    bsp_fdcan.tx_header.MessageMarker = 0;                          // 消息标记
#endif
    // 配置接收滤波器：标准ID，掩码模式，接收所有ID
    bsp_fdcan.sFilterConfig.IdType = FDCAN_STANDARD_ID;             // 使用标准ID
    bsp_fdcan.sFilterConfig.FilterIndex = 0;                        // 滤波器索引
    bsp_fdcan.sFilterConfig.FilterType = FDCAN_FILTER_MASK;         // 掩码过滤模式
    bsp_fdcan.sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // 过滤后的数据送入FIFO0
    if (HAL_FDCAN_ConfigFilter(bsp_fdcan.handle, &bsp_fdcan.sFilterConfig) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }
    // 配置全局滤波：拒绝所有不匹配的标准/扩展帧和远程帧
    if (HAL_FDCAN_ConfigGlobalFilter(bsp_fdcan.handle, \
                                    FDCAN_REJECT, FDCAN_REJECT, \
                                    FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }
    // 激活FIFO0新消息中断
    if (HAL_FDCAN_ActivateNotification(bsp_fdcan.handle, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }
    // 启动FDCAN模块
    if (HAL_FDCAN_Start(bsp_fdcan.handle) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }
}

HAL_StatusTypeDef fdcan_send_message(FDCAN_DeviceTypeDef* bsp_fdcan, uint32_t id, \
                                    uint8_t rtr, uint8_t* data, uint8_t len)
{
    if (bsp_fdcan == NULL || data == NULL || len > FDCAN_DATA_LEN_MAX)
    {
        return HAL_ERROR;
    }
    bsp_fdcan->tx_header.Identifier = id;
    bsp_fdcan->tx_header.IdType = FDCAN_STANDARD_ID;
    bsp_fdcan->tx_header.TxFrameType = rtr ? FDCAN_REMOTE_FRAME : FDCAN_DATA_FRAME;
    bsp_fdcan->tx_header.DataLength = len;

    return HAL_FDCAN_AddMessageToTxFifoQ(bsp_fdcan->handle, &bsp_fdcan->tx_header, data);
}

/**
 * @brief 设置CAN ID
 * @param id: 要设置的CAN ID
 * @note 同时更新发送帧头的ID，CANopen协议下保存重启后生效
 */
void fdcan_set_id(uint32_t id)
{
    bsp_fdcan.id = id;
    bsp_fdcan.tx_header.Identifier = id;
}

/**
 * @brief 获取当前CAN ID
 * @return 当前CAN ID
 */
uint32_t fdcan_get_id(void)
{
    return bsp_fdcan.id;
}

/**
 * @brief 设置CAN波特率
 * @param baudrate: 目标波特率（支持125000、250000、500000、1000000）
 * @note 基于80MHz时钟计算参数，无匹配波特率则设置失败报错
 */
void fdcan_set_baudrate(uint32_t baudrate)
{
    // 根据波特率配置时序参数（Nominal=仲裁段，Data=数据段，参数基于80MHz时钟）
    switch ((FDCAN_BaudrateTypeDef)baudrate)
    {
        case FDCAN_BAUDRATE_125K_BPS:
            // 80MHz / (16 * (1 + 31 + 8)) = 80MHz / (16*40) = 125000
            bsp_fdcan.handle->Init.NominalPrescaler = 16;
            bsp_fdcan.handle->Init.NominalSyncJumpWidth = 8;
            bsp_fdcan.handle->Init.NominalTimeSeg1 = 31;
            bsp_fdcan.handle->Init.NominalTimeSeg2 = 8;
            bsp_fdcan.handle->Init.DataPrescaler = 16;
            bsp_fdcan.handle->Init.DataSyncJumpWidth = 8;
            bsp_fdcan.handle->Init.DataTimeSeg1 = 31;
            bsp_fdcan.handle->Init.DataTimeSeg2 = 8;
            break;

        case FDCAN_BAUDRATE_250K_BPS:
            // 80MHz / (8 * (1 + 31 + 8)) = 80MHz / (8*40) = 250000
            bsp_fdcan.handle->Init.NominalPrescaler = 8;
            bsp_fdcan.handle->Init.NominalSyncJumpWidth = 8;
            bsp_fdcan.handle->Init.NominalTimeSeg1 = 31;
            bsp_fdcan.handle->Init.NominalTimeSeg2 = 8;
            bsp_fdcan.handle->Init.DataPrescaler = 8;
            bsp_fdcan.handle->Init.DataSyncJumpWidth = 8;
            bsp_fdcan.handle->Init.DataTimeSeg1 = 31;
            bsp_fdcan.handle->Init.DataTimeSeg2 = 8;
            break;

        case FDCAN_BAUDRATE_500K_BPS:
            // 80MHz / (10 * (1 + 28 + 5)) = 80MHz / (10*34) ≈ 500000
            bsp_fdcan.handle->Init.NominalPrescaler = 10;
            bsp_fdcan.handle->Init.NominalSyncJumpWidth = 5;
            bsp_fdcan.handle->Init.NominalTimeSeg1 = 28;
            bsp_fdcan.handle->Init.NominalTimeSeg2 = 5;
            bsp_fdcan.handle->Init.DataPrescaler = 10;
            bsp_fdcan.handle->Init.DataSyncJumpWidth = 5;
            bsp_fdcan.handle->Init.DataTimeSeg1 = 28;
            bsp_fdcan.handle->Init.DataTimeSeg2 = 5;
            break;

        case FDCAN_BAUDRATE_1M_BPS: // 1Mbps（默认）
            // 80MHz / (4 * (1 + 14 + 5)) = 80MHz / (4*20) = 1000000
            bsp_fdcan.handle->Init.NominalPrescaler = 4;
            bsp_fdcan.handle->Init.NominalSyncJumpWidth = 2;
            bsp_fdcan.handle->Init.NominalTimeSeg1 = 14;
            bsp_fdcan.handle->Init.NominalTimeSeg2 = 5;
            bsp_fdcan.handle->Init.DataPrescaler = 4;
            bsp_fdcan.handle->Init.DataSyncJumpWidth = 2;
            bsp_fdcan.handle->Init.DataTimeSeg1 = 14;
            bsp_fdcan.handle->Init.DataTimeSeg2 = 5;
            break;

        default:
            sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
            return;
    }

    // 配置FDCAN句柄参数（基于80MHz时钟）
    bsp_fdcan.handle->Instance = CAN_FDCAN_NUMBER;
    bsp_fdcan.handle->Init.FrameFormat = FDCAN_FRAME_FD_NO_BRS;  // 无速率切换的FD格式
    bsp_fdcan.handle->Init.Mode = FDCAN_MODE_NORMAL;             // 正常工作模式
    bsp_fdcan.handle->Init.AutoRetransmission = ENABLE;          // 启用自动重传
    bsp_fdcan.handle->Init.TransmitPause = ENABLE;               // 启用发送暂停
    bsp_fdcan.handle->Init.ProtocolException = DISABLE;          // 禁用协议异常处理
    bsp_fdcan.handle->Init.StdFiltersNbr = 1;                    // 1个标准滤波器
    bsp_fdcan.handle->Init.ExtFiltersNbr = 0;                    // 0个扩展滤波器
    bsp_fdcan.handle->Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION; // TX FIFO模式

    // 初始化FDCAN，失败则恢复默认波特率
    if (HAL_FDCAN_Init(bsp_fdcan.handle) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
        return;
    }

    bsp_fdcan.baudrate = baudrate;

    // 通过设置波特率，初始化
    fdcan_init();
}

/**
 * @brief 获取当前波特率
 * @return 当前波特率
 */
uint32_t fdcan_get_baudrate(void)
{
    return bsp_fdcan.baudrate;
}

/**
 * @brief 获取接收消息累计计数
 * @return 累计接收消息数量（从1开始计数）
 */
uint32_t fdcan_get_mg_counts(void)
{
    return bsp_fdcan.mg_counts;
}
