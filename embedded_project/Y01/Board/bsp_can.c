#include "bsp_can.h"
#include <stdio.h>
#include <string.h>

#if IS_CAN_SLAVE
#include "mavlink_callback.h"
#endif


static uint8_t CalculateDLC(uint8_t dataSize);
static uint16_t CalculatePacketCount(uint16_t total_len);

FDCAN_Frame_TypeDef kFDCanFra = {
    .isPacketComplete = 1,
    .packet_count	= 1,
    .can_tx_id = CAN_EXT_ID_TX,
    .can_rx_id = CAN_EXT_ID_RX,
    .fdcan_rxdata = {0},
    .host_mode = HOST_485,
};


void BspFDCanInit(void)
{
	FDCAN_FilterTypeDef sFilterConfig = {0};

	sFilterConfig.IdType = FDCAN_STANDARD_ID;							// 指定消息类型是标准ID还是扩展ID
	sFilterConfig.FilterIndex = 0;												// 指定要初始化的筛选器编号
	sFilterConfig.FilterType = FDCAN_FILTER_MASK;					// 筛选模式（位匹配）
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;	// 处理筛选结果的方式
	sFilterConfig.FilterID1 = 0x601; 								// 标准ID时，0 到 0x7FF，掩码模式时，它是要筛选的ID
	sFilterConfig.FilterID2 = 0x7FF; 											// 标准ID时，0 到 0x7FF，掩码模式时，它是掩码（严格）

	// 配置FDCAN的筛选器0
	if(HAL_FDCAN_ConfigFilter(&CAN_FDCAN_HANDLE, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

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

}

/**
	* @brief 通过FDCAN发送标准id数据帧
  * @note
  * @param can_id 						11位标准id
	* @param msg 								字符串
	* @param length_code  			This parameter can be a value of @ref FDCAN_data_length_code
	* @retval 返回0表示发送成功
  */
void FDCanSendMsg(uint32_t can_id, uint8_t *msg, uint32_t length_code)
{
		// 初始化Tx报头
		kFDCanFra.TxHead.Identifier = can_id;
		kFDCanFra.TxHead.IdType = FDCAN_EXTENDED_ID;					// 发送标准ID
		kFDCanFra.TxHead.TxFrameType = FDCAN_DATA_FRAME;				// 数据帧
		kFDCanFra.TxHead.DataLength = length_code;						// 数据长度
		kFDCanFra.TxHead.ErrorStateIndicator = FDCAN_ESI_ACTIVE;		// 传输节点处于错误活动状态
		kFDCanFra.TxHead.BitRateSwitch = FDCAN_BRS_ON; 					// 在进行比特率切换的情况下发送FDCAN帧
		kFDCanFra.TxHead.FDFormat = FDCAN_FD_CAN;						// 以FDCAN格式发送帧
		kFDCanFra.TxHead.TxEventFifoControl = FDCAN_NO_TX_EVENTS; 		// 不存储Tx事件
		kFDCanFra.TxHead.MessageMarker = 0;								//指定复制到Tx事件FIFO元素中的消息标记，用于标识Tx消息状态。	

	if(HAL_FDCAN_AddMessageToTxFifoQ(&CAN_FDCAN_HANDLE, &kFDCanFra.TxHead, msg) != HAL_OK)
	{
		// 复位can外设
		HAL_FDCAN_Stop(&CAN_FDCAN_HANDLE);
		HAL_FDCAN_Start(&CAN_FDCAN_HANDLE);	// 必须线先初始化can，然后开始
    }
}


void FDCanPacketSend(uint8_t *rx_data, uint16_t len) 
{
	if(!rx_data || len > RECV_BUFF_SIZE)	// 输入参数检测
	{
		return;
	}

	if(kFDCanFra.host_mode == HOST_CAN)
	{
		if (len <= MAX_FRAME_SIZE)
		{
			// 3.1 小于等于64字节，直接转发
			FDCanSendMsg(kFDCanFra.can_tx_id, rx_data, CalculateDLC(len));
		}
		else
		{
			// 3.2 大于64字节，进行分包转发
			int32_t remaining_len = len;
			uint16_t offset = 0;

			while (remaining_len > 0)
			{
				uint16_t current_frame_len = (remaining_len > MAX_FRAME_SIZE) ? MAX_FRAME_SIZE : remaining_len;

				FDCanSendMsg(kFDCanFra.can_tx_id, &rx_data[offset], CalculateDLC(current_frame_len));

				// 更新剩余长度和偏移量
				remaining_len -= current_frame_len;	// 小于等于0退出循环

				offset += current_frame_len;
			}
		}
	}
}


// 通过FDCAN接收标准id数据帧（中断方式）
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    if((hfdcan->Instance == CAN_FDCAN_HANDLE.Instance) && ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != 0))
    {
        // 1.获取can rx fifo 数据
        HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &kFDCanFra.RxHead, kFDCanFra.fdcan_rxdata);
        // 2. 自定义数据处理函数
        FDCan_RxFifo0RxHandler_callback(kFDCanFra.RxHead.RxFrameType, kFDCanFra.fdcan_rxdata, sizeof(kFDCanFra.fdcan_rxdata));
    }
}

// can中断数据处理回召
void FDCan_RxFifo0RxHandler_callback(uint32_t RxFrameType, uint8_t *Data, uint32_t DataLength)
{
	if(RxFrameType == FDCAN_DATA_FRAME) // 数据帧
	{
		// 1.识别mavlink数据帧解析出数据，大小，校验位，以及指令
		if(Data[0] == MAVLINK_STX && kFDCanFra.isPacketComplete == 1)
		{
			// 2. 协议数据解析
			kFDCanFra.rxFram.magic 		= Data[0];
			kFDCanFra.rxFram.len 		= Data[1];
			kFDCanFra.rxFram.seq 		= Data[2];
			kFDCanFra.rxFram.sysid 		= Data[3];
			kFDCanFra.rxFram.compid 	= Data[4];
			kFDCanFra.rxFram.msgid 		= Data[5];

			memcpy(kFDCanFra.rxFram.payload, &Data[6], kFDCanFra.rxFram.len);

			// 3.计算分包次数
			kFDCanFra.packet_count = CalculatePacketCount(kFDCanFra.rxFram.len + 8);

			memcpy(kFDCanFra.rx_buff, Data, DataLength);

			if(kFDCanFra.packet_count == 1)
			{
				kFDCanFra.rxFram.checksum.bytes.low 	= Data[kFDCanFra.rxFram.len + 6];
				kFDCanFra.rxFram.checksum.bytes.high = Data[kFDCanFra.rxFram.len + 7];

				// 3.1 如果只有1包数据则直接发送
			#if IS_CAN_SLAVE
				mavlink_recv_callback((uint8_t *)kFDCanFra.rx_buff, kFDCanFra.rxFram.len + 8);
				if(kFDCanFra.host_mode == HOST_485) kFDCanFra.host_mode = HOST_CAN;	// 切换CAN控制
			#else
				BspUsartDmaSend((uint8_t *)kFDCanFra.rx_buff, kFDCanFra.rxFram.len + 8);	// dma tx 发送数据,数据长度+固定长度
			#endif
				kFDCanFra.packet_sen_cnt++;
			}
			else
			{

				kFDCanFra.isPacketComplete = 0;		// 有后续包
				kFDCanFra.packet_index = 1;			// 分包索引
			}

		}

		// 分包数据
		else if(kFDCanFra.isPacketComplete == 0)
		{
			// 分包数据未接收完
			if(kFDCanFra.packet_index < kFDCanFra.packet_count)
			{
				memcpy(&kFDCanFra.rx_buff[kFDCanFra.packet_index * MAX_FRAME_SIZE], Data, DataLength);
				memcpy(kFDCanFra.rxFram.payload, &Data[6 + kFDCanFra.packet_index * MAX_FRAME_SIZE], DataLength);	// 有效信息填充
				kFDCanFra.packet_index++;

				if(kFDCanFra.packet_index == kFDCanFra.packet_count)
				{ // 分包数据接收完
					kFDCanFra.rxFram.checksum.bytes.low = kFDCanFra.rx_buff[kFDCanFra.rxFram.len + 6];
					kFDCanFra.rxFram.checksum.bytes.high = kFDCanFra.rx_buff[kFDCanFra.rxFram.len + 7];

					kFDCanFra.isPacketComplete = 1;		// 全部传完
					kFDCanFra.packet_count	= 1;
					kFDCanFra.packet_index = 1;			// 分包重置

				#if IS_CAN_SLAVE
					mavlink_recv_callback((uint8_t *)kFDCanFra.rx_buff, kFDCanFra.rxFram.len + 8);
					if(kFDCanFra.host_mode == HOST_485) kFDCanFra.host_mode = HOST_CAN;	// 切换CAN控制
				#else
					BspUsartDmaSend((uint8_t *)kFDCanFra.rx_buff, kFDCanFra.rxFram.len + 8);	// dma tx 发送数据,数据长度+固定长度
				#endif

					kFDCanFra.packet_sen_cnt++;
				}
			}
		}
	}
}


/**
 * @brief 根据数据大小计算 DLC（数据长度码）
 * @param dataSize 数据大小（字节）
 * @return DLC 值
 */
static uint8_t CalculateDLC(uint8_t dataSize)
{
    if (dataSize <= 8) return dataSize;
    if (dataSize <= 12) return 9;
    if (dataSize <= 16) return 10;
    if (dataSize <= 20) return 11;
    if (dataSize <= 24) return 12;
    if (dataSize <= 32) return 13;
    if (dataSize <= 48) return 14;
    return 15;
}


static uint16_t CalculatePacketCount(uint16_t total_len) {
	
    // 计算分包次数，向上取整
    return (total_len + MAX_FRAME_SIZE - 1) / MAX_FRAME_SIZE;
}



/* ENDLINE ------------------------------------------------------------------*/	
