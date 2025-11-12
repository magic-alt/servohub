#include "drv_can_app.h"

#ifdef USE_CAN
#include "bsp_fdcan.h"

#if defined (USE_CANOPEN)
#include "SlaveOD.h"
#define CANOPEN_MSG_QUEUE_SIZE      8
typedef struct
{
    TIMEVAL elapsed_time;
    TIMEVAL last_counter_val;
    // 发送失败，待发送消息缓存队列
    uint8_t msg_pending_head;
    uint8_t msg_pending_tail;
    Message msg_pending_fifo[CANOPEN_MSG_QUEUE_SIZE];
} FDCAN_CanopenTypeDef;
static inline void fdcan_canopen_init(FDCAN_DeviceTypeDef* bsp_fdcan);
static inline void fdcan_canopen_hendle(FDCAN_DeviceTypeDef* bsp_fdcan);
#elif defined (USE_ENCOS)
static inline void fdcan_encos_handle(FDCAN_DeviceTypeDef* bsp_fdcan);
#elif defined (USE_CUSTOM)
static inline void fdcan_custom_handle(FDCAN_DeviceTypeDef* bsp_fdcan);
#else // CAN + CiA402
static inline void fdcan_cia402_handle(FDCAN_DeviceTypeDef* bsp_fdcan);
#endif

typedef struct
{
    FDCAN_DeviceTypeDef* p_fdcan;
    // CANopen data start
#ifdef USE_CANOPEN
    FDCAN_CanopenTypeDef canopen;
#endif
    // CANopen data end

    // ... User defined data of the application
} FDCAN_AppTypeDef;

static FDCAN_AppTypeDef drv_can_app =
{
    .p_fdcan = NULL,
    // CANopen data start
#ifdef USE_CANOPEN
    .canopen = {0, 0, 0, 0, {0}},
#endif
    // CANopen data end

    // ... Init user defined data of the application
};


void fdcan_app_init(void)
{
    //fdcan_init(); // 已在更新波特率时初始化，此处不需要再初始化
    drv_can_app.p_fdcan = fdcan_get_bsp_fdcan();
#ifdef USE_CANOPEN
    fdcan_canopen_init(drv_can_app.p_fdcan);
#endif
}

void fdcan_app_fifo0_handle(FDCAN_HandleTypeDef* hfdcan)
{
    // Check if FDCAN handle is valid
    if (drv_can_app.p_fdcan == NULL || drv_can_app.p_fdcan->handle != hfdcan)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
        return;
    }

    // Get message from RX FIFO
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &drv_can_app.p_fdcan->rx_header, drv_can_app.p_fdcan->rx_data) != HAL_OK)
    {
        //Error_Handler();
        return;
    }
    #if defined (USE_CANOPEN)
        fdcan_canopen_hendle(drv_can_app.p_fdcan);
    #elif defined (USE_ENCOS)
        fdcan_encos_handle(drv_can_app.p_fdcan);
    #elif defined (USE_CUSTOM)
        fdcan_custom_handle(drv_can_app.p_fdcan);
    #else // CAN + CiA402
        fdcan_cia402_handle(drv_can_app.p_fdcan);
    #endif
}

void fdcan_app_fifo1_handle(FDCAN_HandleTypeDef* hfdcan)
{
    return; // TODO：FIFO1处理
}

#ifdef USE_CANOPEN
/**
 * @brief 初始化CANopen协议栈
 * @param bsp_fdcan Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_canopen_init(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    if (bsp_fdcan == NULL)
    {
        return;
    }
    HAL_TIM_Base_Start_IT(&CANOPEN_TIM_HANDLE);
    setNodeId(&SlaveOD_Data, bsp_fdcan->id);
    setState(&SlaveOD_Data, Initialisation);
    setState(&SlaveOD_Data, Operational);
}

/**
 * @brief 设置下一个定时器值
 * @param value 下一个定时器值
 */
void setTimer(TIMEVAL value)
{
    TIMEVAL timer = __HAL_TIM_GetCounter(&CANOPEN_TIM_HANDLE);

    drv_can_app.canopen.elapsed_time += timer - drv_can_app.canopen.last_counter_val;
    drv_can_app.canopen.last_counter_val = CANOPEN_TIM_ARR - value;
    __HAL_TIM_SetCounter(&CANOPEN_TIM_HANDLE, CANOPEN_TIM_ARR - value);
    HAL_TIM_Base_Start_IT(&CANOPEN_TIM_HANDLE);
}

/**
 * @brief 获取已过去的时间
 * @return 已过去的时间
 */
TIMEVAL getElapsedTime(void)
{
    TIMEVAL timer = __HAL_TIM_GetCounter(&CANOPEN_TIM_HANDLE);

    if (timer < drv_can_app.canopen.last_counter_val)
    {
        timer += CANOPEN_TIM_ARR;
    }

    return drv_can_app.canopen.elapsed_time + (timer - drv_can_app.canopen.last_counter_val);
}

/**
 * @brief CANopen协议定时器调度任务
 * @param None
 * @return None
 */
void CANopen_DispatchFromISR(void)
{
    // 若已外部判断清除中断标志位，无需重复清除
    drv_can_app.canopen.last_counter_val = 0;
    drv_can_app.canopen.elapsed_time = 0;
    TimeDispatch();
}

/**
 * @brief 发送CANopen消息
 * @param notused 未使用参数
 * @param message Pointer to Message structure
 * @return 发送状态（1成功，0失败）
 */
uint8_t canSend(CAN_PORT notused, Message *message)
{
    if (message == NULL)
    {
        return 0; // failed
    }

    if (HAL_OK != fdcan_send_message(drv_can_app.p_fdcan, \
        message->cob_id, message->rtr, message->data, message->len))
    {
        // 若发送失败，缓存消息，可在定时器中断中尝试重新发送（按需求实现）
        if (((drv_can_app.canopen.msg_pending_tail + 1) % CANOPEN_MSG_QUEUE_SIZE) != \
            drv_can_app.canopen.msg_pending_head)
        {
            drv_can_app.canopen.msg_pending_fifo[drv_can_app.canopen.msg_pending_tail] = *message;
            drv_can_app.canopen.msg_pending_tail = (drv_can_app.canopen.msg_pending_tail + 1) % CANOPEN_MSG_QUEUE_SIZE;
        }
        else
        {
            // 队列已满，无法入队，报错CAN通讯错误
        }
        return 0; // failed to send message
    }

    return 1; //success
}

/**
 * @brief CAN + CANopen协议处理
 * @param hfdcan Pointer to FDCAN handle
 * @param bsp_fdcan Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_canopen_hendle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    // Initialize receive message structure
    Message rx_message = {0};

    // Convert FDCAN header to CANopen message format
    rx_message.cob_id = bsp_fdcan->rx_header.Identifier;
    rx_message.rtr = (bsp_fdcan->rx_header.RxFrameType == FDCAN_DATA_FRAME) ? 0 : 1;
    rx_message.len = bsp_fdcan->rx_header.DataLength;

    // Copy message data
    memcpy(rx_message.data, bsp_fdcan->rx_data, rx_message.len);

    // Dispatch message to object dictionary
    canDispatch(&SlaveOD_Data, &rx_message);

    // Re-enable RX FIFO0 notification
    HAL_FDCAN_ActivateNotification(bsp_fdcan->handle, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
}
#endif // USE_CANOPEN

#ifdef USE_ENCOS
/**
 * @brief CAN + ENCOS协议处理
 * @param hfdcan Pointer to FDCAN handle
 * @param bsp_fdcan Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_encos_handle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    return; // TODO
}
#endif // USE_ENCOS

#ifdef USE_CIA402
/**
 * @brief CAN + CIA402协议处理
 * @param hfdcan Pointer to FDCAN handle
 * @param FDCAN_DeviceTypeDef Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_cia402_handle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    // Check if message is for this device
    if (bsp_fdcan->rx_header.Identifier != bsp_fdcan->id)
    {
        return;
    }

    // Update message counter (ensure non-zero)
    bsp_fdcan->mg_counts = (bsp_fdcan->mg_counts == 0) ? 1 : bsp_fdcan->mg_counts + 1;

    // Validate minimum data length
    if (bsp_fdcan->rx_header.DataLength < 5)
    {
        return;
    }

    // Parse message header
    uint8_t is_write = bsp_fdcan->rx_data[0];
    uint16_t obj_index = bsp_fdcan->rx_data[1] | (bsp_fdcan->rx_data[2] << 8);
    uint8_t obj_subindex = bsp_fdcan->rx_data[3];
    uint32_t obj_data = 0;

    // Extract data based on length
    const uint8_t data_length = bsp_fdcan->rx_header.DataLength - 4;
    switch (data_length)
    {
        case 1: // 1 byte data
            obj_data = bsp_fdcan->rx_data[4];
            break;
        case 2: // 2 bytes data
            obj_data = bsp_fdcan->rx_data[4] | (bsp_fdcan->rx_data[5] << 8);
            break;
        case 4: // 4 bytes data
            obj_data = bsp_fdcan->rx_data[4] | (bsp_fdcan->rx_data[5] << 8) |
                      (bsp_fdcan->rx_data[6] << 16) | (bsp_fdcan->rx_data[7] << 24);
            break;
        default: // Unsupported length
            return;
    }

    // Process read/write request
    extern uint32_t master_cia402_read_callback(uint16_t index, uint8_t subindex, void *data);
    extern uint32_t master_cia402_write_callback(uint16_t index, uint8_t subindex, void *data);
    if (is_write == 1)
    {
        master_cia402_write_callback(obj_index, obj_subindex, &obj_data);
    }
    else if (is_write == 0)
    {
        master_cia402_read_callback(obj_index, obj_subindex, &obj_data);
    }
    else
    {
        return;
    }

    // Prepare response
    bsp_fdcan->tx_data[0] = is_write;
    bsp_fdcan->tx_data[1] = obj_index & 0xFF;
    bsp_fdcan->tx_data[2] = (obj_index >> 8) & 0xFF;
    bsp_fdcan->tx_data[3] = obj_subindex;
    bsp_fdcan->tx_data[4] = obj_data & 0xFF;
    bsp_fdcan->tx_data[5] = (obj_data >> 8) & 0xFF;
    bsp_fdcan->tx_data[6] = (obj_data >> 16) & 0xFF;
    bsp_fdcan->tx_data[7] = (obj_data >> 24) & 0xFF;

    // Send response
    HAL_FDCAN_AddMessageToTxFifoQ(bsp_fdcan->handle, &bsp_fdcan->tx_header, bsp_fdcan->tx_data);
}
#endif // USE_CIA402

#ifdef USE_CUSTOM
/**
 * @brief CAN/FDCAN + 用户自定义协议处理
 * @param hfdcan Pointer to FDCAN handle
 * @param FDCAN_DeviceTypeDef Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_custom_handle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    // Custom protocol handling logic：
    bsp_fdcan->tx_header.DataLength = bsp_fdcan->rx_header.DataLength;
    HAL_FDCAN_AddMessageToTxFifoQ(bsp_fdcan->handle, &bsp_fdcan->tx_header, bsp_fdcan->rx_data);
}
#endif // USE_CUSTOM

#endif // USE_CAN
