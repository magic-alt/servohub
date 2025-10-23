#include "version.h"
#include "can_drv.h"
#include "bsp_can.h"
#include "canopen_drv.h"
#include "motor_handle.h"

#pragma region CANOPEN 相关变量

can_tx_buffer_t can_tx_buffer;
uint8_t fdcan_rx_msg[8];
/* 定时器TIM相关变量 */
static TIMEVAL last_counter_val = 0;
static TIMEVAL elapsed_time = 0;

#pragma endregion

// HAL_FDCAN_AddMessageToTxFifoQ(&CAN_FDCAN_HANDLE, &TxHeader, TxData);
extern uint32_t master_cia402_read_callback(uint16_t index, uint8_t subindex, void *data);
extern uint32_t master_cia402_write_callback(uint16_t index, uint8_t subindex, void *data);

#ifdef USE_CANOPEN
uint32_t kCanID = 0x01; // CANOPEN 默认ID
#else
uint32_t kCanID = 0x15; // Define the CAN ID for communication
#endif

uint32_t kCanBaudrate = 1000000; // Default baudrate set to 1M
uint32_t kCanMgCounts = 0;       // CAN接收消息计数

FDCAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
FDCAN_TxHeaderTypeDef TxHeader;
uint8_t TxData[8];

uint8_t FDCAN_Resetflag;

void can_reset_init(void)
{

    /* USER CODE BEGIN FDCAN2_Init 0 */
    uint32_t NowCanid = can_device_get_id();
    uint32_t NowBaudrate = can_device_get_baudrate();

    __HAL_RCC_FDCAN_RELEASE_RESET();
    /* USER CODE END FDCAN2_Init 0 */

    /* USER CODE BEGIN FDCAN2_Init 1 */

    /* USER CODE END FDCAN2_Init 1 */
    CAN_FDCAN_HANDLE.Instance = FDCAN1;
    CAN_FDCAN_HANDLE.Init.FrameFormat = FDCAN_FRAME_FD_BRS;
    CAN_FDCAN_HANDLE.Init.Mode = FDCAN_MODE_NORMAL;
    CAN_FDCAN_HANDLE.Init.AutoRetransmission = DISABLE;
    CAN_FDCAN_HANDLE.Init.TransmitPause = DISABLE;
    CAN_FDCAN_HANDLE.Init.ProtocolException = ENABLE;
    CAN_FDCAN_HANDLE.Init.NominalPrescaler = 8;
    CAN_FDCAN_HANDLE.Init.NominalSyncJumpWidth = 2;
    CAN_FDCAN_HANDLE.Init.NominalTimeSeg1 = 7;
    CAN_FDCAN_HANDLE.Init.NominalTimeSeg2 = 2;
    CAN_FDCAN_HANDLE.Init.DataPrescaler = 8;
    CAN_FDCAN_HANDLE.Init.DataSyncJumpWidth = 1;
    CAN_FDCAN_HANDLE.Init.DataTimeSeg1 = 7;
    CAN_FDCAN_HANDLE.Init.DataTimeSeg2 = 2;
    CAN_FDCAN_HANDLE.Init.MessageRAMOffset = 0;
    CAN_FDCAN_HANDLE.Init.StdFiltersNbr = 1;
    CAN_FDCAN_HANDLE.Init.ExtFiltersNbr = 0;
    CAN_FDCAN_HANDLE.Init.RxFifo0ElmtsNbr = 8;
    CAN_FDCAN_HANDLE.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_64;
    CAN_FDCAN_HANDLE.Init.RxFifo1ElmtsNbr = 3;
    CAN_FDCAN_HANDLE.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_64;
    CAN_FDCAN_HANDLE.Init.RxBuffersNbr = 8;
    CAN_FDCAN_HANDLE.Init.RxBufferSize = FDCAN_DATA_BYTES_64;
    CAN_FDCAN_HANDLE.Init.TxEventsNbr = 0;
    CAN_FDCAN_HANDLE.Init.TxBuffersNbr = 0;
    CAN_FDCAN_HANDLE.Init.TxFifoQueueElmtsNbr = 8;
    CAN_FDCAN_HANDLE.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
    CAN_FDCAN_HANDLE.Init.TxElmtSize = FDCAN_DATA_BYTES_64;
    if (HAL_FDCAN_Init(&CAN_FDCAN_HANDLE) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN FDCAN2_Init 2 */
    can_device_set_id(NowCanid);
    can_device_set_baudrate(NowBaudrate);
    /* USER CODE END FDCAN2_Init 2 */
}

void check_can_error(void)
{
    FDCAN_ErrorCountersTypeDef EanErrorCount;
    HAL_FDCAN_GetErrorCounters(&CAN_FDCAN_HANDLE, &EanErrorCount);

    if (FDCAN_Resetflag == 1)
    {
        can_reset_init();
        FDCAN_Resetflag = 0;
    }

    if ((EanErrorCount.RxErrorCnt > 100) || (EanErrorCount.TxErrorCnt > 100))
    {
        __HAL_RCC_FDCAN_FORCE_RESET();
        FDCAN_Resetflag = 1;
    }
}



void FDCANFilterConfig(FDCAN_HandleTypeDef* hdcan, uint8_t index, uint32_t can_id, uint32_t msg_id)
{
    FDCAN_FilterTypeDef sFilterConfig;
	
    sFilterConfig.IdType = FDCAN_STANDARD_ID;      		//  配置为过滤标准帧
    sFilterConfig.FilterIndex = index;                 	//  过滤器的索引号
    sFilterConfig.FilterType = FDCAN_FILTER_MASK; 		//  过滤方式： 掩码
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = msg_id + (uint8_t)can_id;	// (0x15 + 0x700) 0x715，即只通过0x715的ID的帧;
    sFilterConfig.FilterID2 = 0x7FF; 					//  标准帧为11位ID，严格匹配ID
	
	if(HAL_FDCAN_ConfigFilter(hdcan, &sFilterConfig) != HAL_OK)	
	{
		Error_Handler();
	}
}

void FDCANFilterApp(void)
{
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 1, can_device_get_id(), 0x80);	// 080段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 2, can_device_get_id(), 0x100);	// 100段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 3, can_device_get_id(), 0x180);	// 180段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 4, can_device_get_id(), 0x200);	// 200段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 5, can_device_get_id(), 0x280);	// 280段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 6, can_device_get_id(), 0x300);	// 300段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 7, can_device_get_id(), 0x380);	// 380段匹配	
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 8, can_device_get_id(), 0x400);	// 400段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 9, can_device_get_id(), 0x480);	// 480段匹配	
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 10, can_device_get_id(), 0x500);	// 500段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 11, can_device_get_id(), 0x580);	// 580段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 12, can_device_get_id(), 0x600);	// 600段匹配
	FDCANFilterConfig(&CAN_FDCAN_HANDLE, 13, can_device_get_id(), 0x700);	// 700段匹配
}

void can_device_init(void)
{
#ifdef USE_CANOPEN
    FDCAN_FilterTypeDef sFilterConfig;

    /* Configure Rx filter */
    sFilterConfig.IdType = FDCAN_STANDARD_ID;      //  配置为过滤标准帧
    sFilterConfig.FilterIndex = 0;                 //  过滤器的索引号
    sFilterConfig.FilterType = FDCAN_FILTER_MASK; //  过滤方式为范围，即从FilterID1~FilterID2之间的值
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x000;
    sFilterConfig.FilterID2 = 0x7ff; //  标准帧为11位ID，即0x7ff，目前配置为接收所有帧

    /*Configure the FDCAN reception filter*/
    if (HAL_FDCAN_ConfigFilter(&CAN_FDCAN_HANDLE, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    FDCANFilterApp();	// CANOPEN过滤器配置

    sFilterConfig.IdType = FDCAN_EXTENDED_ID;								// 指定消息类型是标准ID还是扩展ID
    sFilterConfig.FilterIndex = 0;													// 指定要初始化的筛选器编号
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;						// 筛选模式（位匹配）
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;		// 处理筛选结果的方式
    sFilterConfig.FilterID1 = 0x6001; 												// 标准ID时，0 到 0x7FF，掩码模式时，它是要筛选的ID
    sFilterConfig.FilterID2 = 0x7FFF; 												// 标准ID时，0 到 0x7FF，掩码模式时，它是掩码（严格）		

    // 配置FDCAN的筛选器1
    if(HAL_FDCAN_ConfigFilter(&CAN_FDCAN_HANDLE, &sFilterConfig) != HAL_OK)	
    {
        Error_Handler();
    }

    // 配置FDCAN1的全局过滤器：不收过滤掉的标准id数据帧，不收过滤掉的扩展id数据帧，收过滤好的标准id遥控帧，不收扩展id遥控帧
    if (HAL_FDCAN_ConfigGlobalFilter(&CAN_FDCAN_HANDLE, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
    {
        Error_Handler();
    }

    // 开启RX FIFO0的新消息中断
    if (HAL_FDCAN_ActivateNotification(&CAN_FDCAN_HANDLE, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
        Error_Handler();
    }

    // 开启RX FIFO1的新消息中断
    if (HAL_FDCAN_ActivateNotification(&CAN_FDCAN_HANDLE, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_FDCAN_Start(&CAN_FDCAN_HANDLE) != HAL_OK)
    {
        Error_Handler();
    }

    // 还应增加读取用户参数设置ID 支持nodeID配置
    setNodeId(&SlaveOD_Data, kCanID);
    setState(&SlaveOD_Data, Initialisation);
    setState(&SlaveOD_Data, Pre_operational);
    setState(&SlaveOD_Data, Operational);

    // Initialize the CAN buffer
    can_tx_buffer.buf_st = TX_BUFFER_SIZE - 1;
    can_tx_buffer.buf_ed = 0;
    can_tx_buffer.buf_empty = 1;

#else

    FDCAN_FilterTypeDef sFilterConfig;

    /* Configure Rx filter */
    sFilterConfig.IdType = FDCAN_STANDARD_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x55;
    sFilterConfig.FilterID2 = 0x00; // 只要 ID2配置 0 就不会过滤任何一个ID

    if (HAL_FDCAN_ConfigFilter(&CAN_FDCAN_HANDLE, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

	sFilterConfig.IdType = FDCAN_EXTENDED_ID;							// 指定消息类型是标准ID还是扩展ID
	sFilterConfig.FilterIndex = 0;										// 指定要初始化的筛选器编号
	sFilterConfig.FilterType = FDCAN_FILTER_MASK;						// 筛选模式（位匹配）
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;				// 处理筛选结果的方式
	sFilterConfig.FilterID1 = 0x6001; 									// 标准ID时，0 到 0x7FF，掩码模式时，它是要筛选的ID
	sFilterConfig.FilterID2 = 0x7FFF; 									// 标准ID时，0 到 0x7FF，掩码模式时，它是掩码（严格）		

	// 配置FDCAN的筛选器1
	if(HAL_FDCAN_ConfigFilter(&CAN_FDCAN_HANDLE, &sFilterConfig) != HAL_OK)	
	{
		Error_Handler();
	}


    /* Configure global filter:
        Filter all remote frames with STD and EXT ID
        Reject non matching frames with STD ID and EXT ID */
    if (HAL_FDCAN_ConfigGlobalFilter(&CAN_FDCAN_HANDLE, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
    {
        Error_Handler();
    }

    /* Start the FDCAN module */
    if (HAL_FDCAN_Start(&CAN_FDCAN_HANDLE) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(&CAN_FDCAN_HANDLE, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
        Error_Handler();
    }

	// 开启RX FIFO1的新消息中断
	if (HAL_FDCAN_ActivateNotification(&CAN_FDCAN_HANDLE, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}

    if (HAL_FDCAN_ActivateNotification(&CAN_FDCAN_HANDLE, FDCAN_IT_BUS_OFF, 0) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_FDCAN_ActivateNotification(&CAN_FDCAN_HANDLE, FDCAN_IT_ERROR_PASSIVE, 0) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_FDCAN_ActivateNotification(&CAN_FDCAN_HANDLE, FDCAN_IT_ERROR_WARNING, 0) != HAL_OK)
    {
        Error_Handler();
    }

    /* Prepare Tx Header */
    TxHeader.Identifier = kCanID;
    TxHeader.IdType = FDCAN_STANDARD_ID;
    TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    TxHeader.DataLength = FDCAN_DLC_BYTES_8;
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker = 0;

#endif
}

uint32_t can_device_get_id(void)
{
    return kCanID;
}
uint32_t can_device_get_baudrate(void)
{
    return kCanBaudrate;
}

void can_device_set_id(uint32_t can_id)
{
    kCanID = can_id;
    TxHeader.Identifier = kCanID;
}

void can_device_set_baudrate(uint32_t baudrate)
{
//TODO：增加波特率设置

    kCanBaudrate = baudrate;
    switch (baudrate)
    {
    case 500000:
    {
        CAN_FDCAN_HANDLE.Instance = FDCAN1;
        CAN_FDCAN_HANDLE.Init.FrameFormat = FDCAN_FRAME_FD_BRS;
        CAN_FDCAN_HANDLE.Init.Mode = FDCAN_MODE_NORMAL;
        CAN_FDCAN_HANDLE.Init.AutoRetransmission = ENABLE;
        CAN_FDCAN_HANDLE.Init.TransmitPause = ENABLE;
        CAN_FDCAN_HANDLE.Init.ProtocolException = ENABLE;
        CAN_FDCAN_HANDLE.Init.NominalPrescaler = 16;
        CAN_FDCAN_HANDLE.Init.NominalSyncJumpWidth = 2;
        CAN_FDCAN_HANDLE.Init.NominalTimeSeg1 = 7;
        CAN_FDCAN_HANDLE.Init.NominalTimeSeg2 = 2;
        CAN_FDCAN_HANDLE.Init.DataPrescaler = 16; 
        CAN_FDCAN_HANDLE.Init.DataSyncJumpWidth = 1;
        CAN_FDCAN_HANDLE.Init.DataTimeSeg1 = 7;
        CAN_FDCAN_HANDLE.Init.DataTimeSeg2 = 2;
        CAN_FDCAN_HANDLE.Init.MessageRAMOffset = 0;
        CAN_FDCAN_HANDLE.Init.StdFiltersNbr = 128;
        CAN_FDCAN_HANDLE.Init.ExtFiltersNbr = 64;
        CAN_FDCAN_HANDLE.Init.RxFifo0ElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.RxFifo1ElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.RxBuffersNbr = 8;
        CAN_FDCAN_HANDLE.Init.RxBufferSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.TxEventsNbr = 0;
        CAN_FDCAN_HANDLE.Init.TxBuffersNbr = 0;
        CAN_FDCAN_HANDLE.Init.TxFifoQueueElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
        CAN_FDCAN_HANDLE.Init.TxElmtSize = FDCAN_DATA_BYTES_64;
        if (HAL_FDCAN_Init(&CAN_FDCAN_HANDLE) != HAL_OK)
        {
            Error_Handler();
            kCanBaudrate = 1000000; // 如果初始化失败，设置为默认波特率
        }
    }

    break;
    case 1000000:
    {
        CAN_FDCAN_HANDLE.Instance = FDCAN1;
        CAN_FDCAN_HANDLE.Init.FrameFormat = FDCAN_FRAME_FD_BRS;
        CAN_FDCAN_HANDLE.Init.Mode = FDCAN_MODE_NORMAL;
        CAN_FDCAN_HANDLE.Init.AutoRetransmission = ENABLE;
        CAN_FDCAN_HANDLE.Init.TransmitPause = ENABLE;
        CAN_FDCAN_HANDLE.Init.ProtocolException = ENABLE;
        CAN_FDCAN_HANDLE.Init.NominalPrescaler = 8;
        CAN_FDCAN_HANDLE.Init.NominalSyncJumpWidth = 2;
        CAN_FDCAN_HANDLE.Init.NominalTimeSeg1 = 7;
        CAN_FDCAN_HANDLE.Init.NominalTimeSeg2 = 2;
        CAN_FDCAN_HANDLE.Init.DataPrescaler = 8;
        CAN_FDCAN_HANDLE.Init.DataSyncJumpWidth = 1;
        CAN_FDCAN_HANDLE.Init.DataTimeSeg1 = 7;
        CAN_FDCAN_HANDLE.Init.DataTimeSeg2 = 2;
        CAN_FDCAN_HANDLE.Init.MessageRAMOffset = 0;
        CAN_FDCAN_HANDLE.Init.StdFiltersNbr = 128;
        CAN_FDCAN_HANDLE.Init.ExtFiltersNbr = 64;
        CAN_FDCAN_HANDLE.Init.RxFifo0ElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.RxFifo1ElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.RxBuffersNbr = 8;
        CAN_FDCAN_HANDLE.Init.RxBufferSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.TxEventsNbr = 0;
        CAN_FDCAN_HANDLE.Init.TxBuffersNbr = 0;
        CAN_FDCAN_HANDLE.Init.TxFifoQueueElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
        CAN_FDCAN_HANDLE.Init.TxElmtSize = FDCAN_DATA_BYTES_64;
        if (HAL_FDCAN_Init(&CAN_FDCAN_HANDLE) != HAL_OK)
        {
            Error_Handler();
            kCanBaudrate = 1000000; // 如果初始化失败，设置为默认波特率
        }
    }

    break;
    default: // 其他默认 按 1M波特率设置
    {
        CAN_FDCAN_HANDLE.Instance = FDCAN1;
        CAN_FDCAN_HANDLE.Init.FrameFormat = FDCAN_FRAME_FD_BRS;
        CAN_FDCAN_HANDLE.Init.Mode = FDCAN_MODE_NORMAL;
        CAN_FDCAN_HANDLE.Init.AutoRetransmission = ENABLE;
        CAN_FDCAN_HANDLE.Init.TransmitPause = ENABLE;
        CAN_FDCAN_HANDLE.Init.ProtocolException = ENABLE;
        CAN_FDCAN_HANDLE.Init.NominalPrescaler = 8;
        CAN_FDCAN_HANDLE.Init.NominalSyncJumpWidth = 2;
        CAN_FDCAN_HANDLE.Init.NominalTimeSeg1 = 7;
        CAN_FDCAN_HANDLE.Init.NominalTimeSeg2 = 2;
        CAN_FDCAN_HANDLE.Init.DataPrescaler = 8;
        CAN_FDCAN_HANDLE.Init.DataSyncJumpWidth = 1;
        CAN_FDCAN_HANDLE.Init.DataTimeSeg1 = 7;
        CAN_FDCAN_HANDLE.Init.DataTimeSeg2 = 2;
        CAN_FDCAN_HANDLE.Init.MessageRAMOffset = 0;
        CAN_FDCAN_HANDLE.Init.StdFiltersNbr = 128;
        CAN_FDCAN_HANDLE.Init.ExtFiltersNbr = 64;
        CAN_FDCAN_HANDLE.Init.RxFifo0ElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.RxFifo1ElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.RxBuffersNbr = 8;
        CAN_FDCAN_HANDLE.Init.RxBufferSize = FDCAN_DATA_BYTES_64;
        CAN_FDCAN_HANDLE.Init.TxEventsNbr = 0;
        CAN_FDCAN_HANDLE.Init.TxBuffersNbr = 0;
        CAN_FDCAN_HANDLE.Init.TxFifoQueueElmtsNbr = 32;
        CAN_FDCAN_HANDLE.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
        CAN_FDCAN_HANDLE.Init.TxElmtSize = FDCAN_DATA_BYTES_64;
        if (HAL_FDCAN_Init(&CAN_FDCAN_HANDLE) != HAL_OK)
        {
            Error_Handler();
            kCanBaudrate = 1000000; // 如果初始化失败，设置为默认波特率
        }
    }

    break;
    }

    can_device_init();
}

// 读取can消息报文累计计数值
uint32_t can_device_get_mg_counts(void)
{
    return kCanMgCounts;
}

/**
 * @brief  Rx FIFO 0 callback.
 * @param  hfdcan: pointer to an FDCAN_HandleTypeDef structure that contains
 *         the configuration information for the specified FDCAN.
 * @param  RxFifo0ITs: indicates which Rx FIFO 0 interrupts are signalled.
 *         This parameter can be any combination of @arg FDCAN_Rx_Fifo0_Interrupts.
 * @retval None
 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
#ifdef USE_CANOPEN
    if ((hfdcan->Instance == FDCAN1) && ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET))
    {
        memset(fdcan_rx_msg, 0, sizeof(fdcan_rx_msg));
        HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, fdcan_rx_msg);
        Message Rx_Message = {0};
        Rx_Message.cob_id = RxHeader.Identifier;
        Rx_Message.rtr = (RxHeader.RxFrameType == FDCAN_DATA_FRAME) ? 0 : 1;
        Rx_Message.len = RxHeader.DataLength;

        memcpy(Rx_Message.data, fdcan_rx_msg, RxHeader.DataLength);

        canDispatch(&SlaveOD_Data, &Rx_Message);

        HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
    }

#else

    uint8_t rw = 0;
    uint16_t index = 0;
    uint8_t sub_index = 0;
    uint32_t data = 0;
    uint32_t AbortCode = 0;

    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
    {
        /* Retrieve Rx messages from RX FIFO0 */
        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
        {
            Error_Handler();
        }

    #ifdef ENCOS_CAN_FREE
        EncosCanMessage Rx_Message = {0};
        Rx_Message.cob_id = RxHeader.Identifier;

        if (RxHeader.Identifier == kCanID)
        {
            kCanMgCounts++;
            if (0 == kCanMgCounts) // 一旦开始计数 则从 1开始 到 最大值
            {
                kCanMgCounts++;
            }
        }

        Rx_Message.rtr = (RxHeader.RxFrameType == FDCAN_DATA_FRAME) ? 0 : 1;
        Rx_Message.len = RxHeader.DataLength;
        memcpy(Rx_Message.data, RxData, RxHeader.DataLength);
        // 自定义协议处理
        canframe_handle(&Rx_Message);
    #endif

    #ifdef USE_CANFD
        if (RxHeader.Identifier == kCanID)
        {
            kCanMgCounts++;
            if (0 == kCanMgCounts) // 一旦开始计数 则从 1开始 到 最大值
            {
                kCanMgCounts++;
            }
        }
        // TODO: CANFD自定义实现，以下为测试代码，接收到数据后直接发送回去
        memcpy(TxData, RxData, RxHeader.DataLength);
        HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TxHeader, TxData);
    #endif

    #ifdef USE_CAN
        if (RxHeader.Identifier == kCanID)
        {
            kCanMgCounts++;
            if (0 == kCanMgCounts) // 一旦开始计数 则从 1开始 到 最大值
            {
                kCanMgCounts++;
            }

            // 数据区长度不满足
            if (RxHeader.DataLength < 5)
            {
                return;
            }

            rw = RxData[0];
            index = RxData[1] | (RxData[2] << 8);
            sub_index = RxData[3];

            switch (RxHeader.DataLength - 4)
            {
            case 1: // 1字节
                data = RxData[4];
                break;
            case 2: // 2字节
                data = RxData[4] | (RxData[5] << 8);
                break;
            case 4: // 4字节
                data = RxData[4] | (RxData[5] << 8) | (RxData[6] << 16) | (RxData[7] << 24);
                break;
            default:
                break;
            }

            if (rw == 1) {
                AbortCode = master_cia402_write_callback(index, sub_index, &data);
            }
            else if (rw == 0) {
                AbortCode = master_cia402_read_callback(index, sub_index, &data);
            }

            if (AbortCode) {
                rw = 0x80;  // 读写错误
                data = AbortCode; // 错误码
            }

            TxData[0] = rw;
            TxData[1] = index & 0xFF;
            TxData[2] = (index >> 8) & 0xFF;
            TxData[3] = sub_index;
            TxData[4] = data & 0xFF;
            TxData[5] = (data >> 8) & 0xFF;
            TxData[6] = (data >> 16) & 0xFF;
            TxData[7] = (data >> 24) & 0xFF;
            HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TxHeader, TxData);
        }
    #endif
    }
#endif
}

void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan)
{
    if (hfdcan->Instance == FDCAN2)
    {
        can_reset_init();
    }
}

#pragma region CANopen SlaveOD Callbacks

UNS32 SlaveOD_Read_Callback(uint16_t index, uint8_t subindex, void *data)
{
    return master_cia402_read_callback(index, subindex, data);;
}

UNS32 SlaveOD_Write_Callback(uint16_t index, uint8_t subindex, void *data)
{
    return master_cia402_write_callback(index, subindex, data);
}

void setTimer(TIMEVAL value)
{
    uint32_t timer = __HAL_TIM_GetCounter(CANOPEN_TIMx); // Copy the value of the running timer

    elapsed_time += timer - last_counter_val;
    last_counter_val = CANOPEN_TIM_PERIOD - value;
    __HAL_TIM_SetCounter(CANOPEN_TIMx, CANOPEN_TIM_PERIOD - value);
    HAL_TIM_Base_Start_IT(CANOPEN_TIMx);
}

TIMEVAL getElapsedTime(void)
{
    uint32_t timer = __HAL_TIM_GetCounter(CANOPEN_TIMx);

    if (timer < last_counter_val)
        timer += CANOPEN_TIM_PERIOD;

    TIMEVAL elapsed = timer - last_counter_val + elapsed_time;

    return elapsed;
}

void TIMx_DispatchFromISR(void)
{
    last_counter_val = 0;
    elapsed_time = 0;
    TimeDispatch();
}

uint8_t canSend(CAN_PORT notused, Message *message)
{
    uint8_t data[8] = {0};
    TxHeader.Identifier = message->cob_id;
    TxHeader.IdType = FDCAN_STANDARD_ID;
    TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    TxHeader.DataLength = message->len;
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker = 0;

    memcpy(data, message->data, message->len);
    if (HAL_FDCAN_AddMessageToTxFifoQ(&CAN_FDCAN_HANDLE, &TxHeader, data) != HAL_OK)
    {
        // HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_15);//测试发送失败
        if ((can_tx_buffer.buf_ed == can_tx_buffer.buf_st) && (can_tx_buffer.buf_empty == 0))
        {
            return 0;
        }
        else
        {
            can_tx_buffer.buf[can_tx_buffer.buf_ed] = *message;
            can_tx_buffer.buf_empty = 0;
            can_tx_buffer.buf_ed++;
            if (can_tx_buffer.buf_ed == TX_BUFFER_SIZE)
            {
                // 可添加错误报警处理累计发送失败
                can_tx_buffer.buf_ed = 0;
            }
        }
    }
    return 1;
}
#pragma endregion