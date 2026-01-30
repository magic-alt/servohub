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
FDCAN_DeviceTypeDef* bsp_fdcan_get_fdcan_handle(void)
{
    return &bsp_fdcan;
}

/**
 * @brief 初始化FDCAN
 * @details 1. 配置接收滤波器
 *          2. 配置全局滤波规则（拒绝不匹配帧和远程帧）
 *          3. 启动FDCAN模块并激活接收中断
 */
void bsp_fdcan_init(void)
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
#endif /* USE_CANOPEN */
    // 配置接收滤波器：标准ID，掩码模式，接收所有ID
    bsp_fdcan.sFilterConfig.IdType = FDCAN_STANDARD_ID;             // 使用标准ID
    bsp_fdcan.sFilterConfig.FilterIndex = 0;                        // 滤波器索引
    bsp_fdcan.sFilterConfig.FilterType = FDCAN_FILTER_MASK;         // 掩码过滤模式
    bsp_fdcan.sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // 过滤后的数据送入FIFO0
    if (HAL_FDCAN_ConfigFilter(bsp_fdcan.handle, &bsp_fdcan.sFilterConfig) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }

#ifdef USE_CAN_PASSTHROUGH
    // 配置透传接收滤波器FIFO1
    bsp_fdcan.sFilterConfig.IdType = FDCAN_EXTENDED_ID;             // 使用扩展ID
    bsp_fdcan.sFilterConfig.FilterType = FDCAN_FILTER_MASK;         // 掩码过滤模式
    bsp_fdcan.sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO1; // 过滤后的数据送入FIFO1
    /* ================= Filter 0：全局广播 =================
     * flag = 2 (10b) 2bit
     * 只匹配 flag 字段
     */
    bsp_fdcan.sFilterConfig.FilterIndex = 0;                        // 滤波器索引
    bsp_fdcan.sFilterConfig.FilterID1   = (2U << CANID_FLAG_SHIFT);
    bsp_fdcan.sFilterConfig.FilterID2   = CANID_FLAG_MASK;
    if (HAL_FDCAN_ConfigFilter(bsp_fdcan.handle, &bsp_fdcan.sFilterConfig) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }

    /* ================= Filter 1：系统内广播 =================
     * flag = 1 (01b) 2bit
     * 匹配 flag + sysid
     */
    bsp_fdcan.sFilterConfig.FilterIndex = 1;
    bsp_fdcan.sFilterConfig.FilterID1   = (1U << CANID_FLAG_SHIFT) | ((uint32_t)get_app_Sys_id() << CANID_SYSID_SHIFT);
    bsp_fdcan.sFilterConfig.FilterID2   = CANID_FLAG_MASK | CANID_SYSID_MASK;
    if (HAL_FDCAN_ConfigFilter(bsp_fdcan.handle, &bsp_fdcan.sFilterConfig) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }

    /* ================= Filter 2：单设备通信 =================
     * compid = 0xFF (1111 1111b) 8bit
     * sysid  = 0x1F    (1 1111b) 5bit
     * 匹配 compid + sysid
     */
    bsp_fdcan.sFilterConfig.FilterIndex = 2;
    bsp_fdcan.sFilterConfig.FilterID1   = ((uint32_t)get_app_Comp_id() << CANID_COMPID_SHIFT) | ((uint32_t)get_app_Sys_id() << CANID_SYSID_SHIFT);
    bsp_fdcan.sFilterConfig.FilterID2   = CANID_COMPID_MASK | CANID_SYSID_MASK;
    if (HAL_FDCAN_ConfigFilter(bsp_fdcan.handle, &bsp_fdcan.sFilterConfig) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }
#endif /* USE_CAN_PASSTHROUGH */

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
#ifdef USE_CAN_PASSTHROUGH
    // 激活FIFO1新消息中断
    if (HAL_FDCAN_ActivateNotification(bsp_fdcan.handle, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }
#endif /* USE_CAN_PASSTHROUGH */
    // 启动FDCAN模块
    if (HAL_FDCAN_Start(bsp_fdcan.handle) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }
}

/**
 * @brief 设置CAN ID
 * @param id: 要设置的CAN ID
 * @note 同时更新发送帧头的ID，CANopen协议下保存重启后生效
 */
void bsp_fdcan_set_id(uint32_t id)
{
    bsp_fdcan.id = id;
    bsp_fdcan.tx_can.Identifier = id;
    bsp_fdcan.tx_fdcan.Identifier = id;
}

/**
 * @brief 获取当前CAN ID
 * @return 当前CAN ID
 */
uint32_t bsp_fdcan_get_id(void)
{
    return bsp_fdcan.id;
}

/**
 * @brief 设置CAN波特率
 * @param baudrate: 目标波特率（支持125000、250000、500000、1000000）
 * @note 基于80MHz时钟计算参数，无匹配波特率则设置失败报错
 */
void bsp_fdcan_set_baudrate(uint32_t baudrate)
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
    bsp_fdcan.handle->Init.ExtFiltersNbr = 3;                    // 3个扩展滤波器
    bsp_fdcan.handle->Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION; // TX FIFO模式

    // 初始化FDCAN，失败则恢复默认波特率
    if (HAL_FDCAN_Init(bsp_fdcan.handle) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
        return;
    }

    bsp_fdcan.baudrate = baudrate;

    // 通过设置波特率，初始化
    bsp_fdcan_init();
}

/**
 * @brief 获取当前波特率
 * @return 当前波特率
 */
uint32_t bsp_fdcan_get_baudrate(void)
{
    return bsp_fdcan.baudrate;
}

/**
 * @brief 获取接收消息累计计数
 * @return 累计接收消息数量（从1开始计数）
 */
uint32_t bsp_fdcan_get_mg_counts(void)
{
    return bsp_fdcan.mg_counts;
}

/**
 * @brief  发送一帧 标准CAN 数据帧（标准ID）
 * @note   可发送任意长度（0~8字节）数据
 * 
 * @param  bsp_fdcan 指向要发送的 FDCAN 应用结构体
 * @param  id        发送帧的ID（11位或29位，根据 is_ide 确定）
 * @param  is_ide    是否启用扩展ID（true为扩展ID，false为标准ID）
 * @param  is_rtr    是否为远程帧（true为远程帧，false为数据帧）
 * @param  data      指向要发送的数据缓冲区
 * @param  len       实际要发送的数据长度（单位：字节，范围 0~8）
 * 
 * @retval HAL_StatusTypeDef
 *         - HAL_OK         成功发送
 *         - HAL_ERROR      参数非法或发送失败（如长度超限、硬件故障等）
 */
HAL_StatusTypeDef bsp_can_send_message(FDCAN_DeviceTypeDef* bsp_fdcan,
                                       uint32_t id,
                                       bool is_ide,
                                       bool is_rtr,
                                       uint8_t* data,
                                       uint8_t len)
{
    if (bsp_fdcan == NULL || data == NULL || len > CAN_DATA_LEN_MAX)
    {
        return HAL_ERROR;
    }

    bsp_fdcan->tx_can.Identifier         = id;
    bsp_fdcan->tx_can.IdType             = is_ide ? FDCAN_EXTENDED_ID : FDCAN_STANDARD_ID;
    bsp_fdcan->tx_can.TxFrameType        = is_rtr ? FDCAN_REMOTE_FRAME : FDCAN_DATA_FRAME;
    bsp_fdcan->tx_can.DataLength         = bsp_fdcan_bytes_to_dlc(len);
    bsp_fdcan->tx_can.ErrorStateIndicator= FDCAN_ESI_ACTIVE;
    bsp_fdcan->tx_can.BitRateSwitch      = FDCAN_BRS_OFF;
    bsp_fdcan->tx_can.FDFormat           = FDCAN_CLASSIC_CAN; //FDCAN格式发送 FDCAN_CLASSIC_CAN
    bsp_fdcan->tx_can.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    bsp_fdcan->tx_can.MessageMarker      = 0;

    return HAL_FDCAN_AddMessageToTxFifoQ(bsp_fdcan->handle, &bsp_fdcan->tx_can, data);
}

/**
 * @brief  发送一帧 CAN FD 数据帧
 * @note   可发送任意长度（0~64字节）数据，函数内部自动选择合法DLC编码
 *         支持更改 ID 类型（标准ID/扩展ID）和 BitRateSwitch（速率切换），采用 FDCAN_FD_CAN 格式
 *         使用发送FIFO队列（非事件队列）
 * 
 * @param  bsp_fdcan 指向要发送的 FDCAN 应用结构体
 * @param  id        发送帧的ID（11位或29位，根据 is_ide 确定）
 * @param  is_ide    是否启用扩展ID（true为扩展ID，false为标准ID）
 * @param  is_brs    是否启用可变波特率（true为启用，false为禁用）
 * @param  data      指向要发送的数据缓冲区
 * @param  len       实际要发送的数据长度（单位：字节，范围 0~64）
 * 
 * @retval HAL_StatusTypeDef
 *         - HAL_OK         成功发送
 *         - HAL_ERROR      参数非法或发送失败（如长度超限、硬件故障等）
 */
HAL_StatusTypeDef bsp_fdcan_send_message(FDCAN_DeviceTypeDef* bsp_fdcan,
                                         uint32_t id,
                                         bool is_ide,
                                         bool is_brs,
                                         uint8_t *data,
                                         uint8_t len)
{
    if (bsp_fdcan == NULL || data == NULL || len > FDCAN_DATA_LEN_MAX)
    {
        return HAL_ERROR;
    }

    // 填充发送帧头
    bsp_fdcan->tx_fdcan.Identifier         = id;
    bsp_fdcan->tx_fdcan.IdType             = is_ide ? FDCAN_EXTENDED_ID : FDCAN_STANDARD_ID;
    bsp_fdcan->tx_fdcan.TxFrameType        = FDCAN_DATA_FRAME;      //数据帧
    bsp_fdcan->tx_fdcan.DataLength         = bsp_fdcan_bytes_to_dlc(len);
    bsp_fdcan->tx_fdcan.ErrorStateIndicator= FDCAN_ESI_ACTIVE;
    bsp_fdcan->tx_fdcan.BitRateSwitch      = is_brs ? FDCAN_BRS_ON : FDCAN_BRS_OFF;
    bsp_fdcan->tx_fdcan.FDFormat           = FDCAN_FD_CAN;          //FDCAN格式发送 FDCAN_FD_CAN
    bsp_fdcan->tx_fdcan.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    bsp_fdcan->tx_fdcan.MessageMarker      = 0;

    return HAL_FDCAN_AddMessageToTxFifoQ(bsp_fdcan->handle, &bsp_fdcan->tx_fdcan, data);
}

/**
  * @brief  将 FDCAN_DLC_BYTES_x 宏转换为实际字节数
  * @param  dlc: rxHeader.DataLength 的值
  * @retval 实际字节数 (0-64)
  */
uint8_t bsp_fdcan_dlc_to_bytes(uint32_t dlc)
{
    switch (dlc) {
        case FDCAN_DLC_BYTES_0:  return 0;
        case FDCAN_DLC_BYTES_1:  return 1;
        case FDCAN_DLC_BYTES_2:  return 2;
        case FDCAN_DLC_BYTES_3:  return 3;
        case FDCAN_DLC_BYTES_4:  return 4;
        case FDCAN_DLC_BYTES_5:  return 5;
        case FDCAN_DLC_BYTES_6:  return 6;
        case FDCAN_DLC_BYTES_7:  return 7;
        case FDCAN_DLC_BYTES_8:  return 8;
        case FDCAN_DLC_BYTES_12: return 12;
        case FDCAN_DLC_BYTES_16: return 16;
        case FDCAN_DLC_BYTES_20: return 20;
        case FDCAN_DLC_BYTES_24: return 24;
        case FDCAN_DLC_BYTES_32: return 32;
        case FDCAN_DLC_BYTES_48: return 48;
        case FDCAN_DLC_BYTES_64: return 64;
        default: return 0; // 异常情况
    }
}

/**
 * @brief  将字节数转换为 FDCAN DLC 标准编码
 * @note   根据 FDCAN 规范，将字节数映射为对应的 DLC 编码
 *         支持 0~64 字节数据长度，超出范围返回 FDCAN_DLC_BYTES_64
 * @param  bytes_len  要转换的字节数（范围 0~64）
 * @return FDCAN_DLC_xx 标准编码
 */
uint32_t bsp_fdcan_bytes_to_dlc(uint8_t bytes_len)
{
    if (bytes_len <= 0) {
        return FDCAN_DLC_BYTES_0;
    } else if (bytes_len <= 1) {
        return FDCAN_DLC_BYTES_1;
    } else if (bytes_len <= 2) {
        return FDCAN_DLC_BYTES_2;
    } else if (bytes_len <= 3) {
        return FDCAN_DLC_BYTES_3;
    } else if (bytes_len <= 4) {
        return FDCAN_DLC_BYTES_4;
    } else if (bytes_len <= 5) {
        return FDCAN_DLC_BYTES_5;
    } else if (bytes_len <= 6) {
        return FDCAN_DLC_BYTES_6;
    } else if (bytes_len <= 7) {
        return FDCAN_DLC_BYTES_7;
    } else if (bytes_len <= 8) {
        return FDCAN_DLC_BYTES_8;
    } else if (bytes_len <= 12) {
        return FDCAN_DLC_BYTES_12;
    } else if (bytes_len <= 16) {
        return FDCAN_DLC_BYTES_16;
    } else if (bytes_len <= 20) {
        return FDCAN_DLC_BYTES_20;
    } else if (bytes_len <= 24) {
        return FDCAN_DLC_BYTES_24;
    } else if (bytes_len <= 32) {
        return FDCAN_DLC_BYTES_32;
    } else if (bytes_len <= 48) {
        return FDCAN_DLC_BYTES_48;
    } else {
        return FDCAN_DLC_BYTES_64;
    }
}
