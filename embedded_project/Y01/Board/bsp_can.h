/**
  ******************************************************************************
  * @file    bsp_can.h
  * @brief   This file contains all the function prototypes for
  *          the bsp_usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_CAN_H
#define BSP_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "board.h"

#define IS_CAN_SLAVE		1

#define CAN_ID_NUM			1U					// 序号 默认1	(范围1~127)

#if IS_CAN_SLAVE
#define CAN_EXT_ID_TX		(0x7000 | CAN_ID_NUM)	// 发送ID（ID段0x6000 + 序号）
#define CAN_EXT_ID_RX		(0x6000 | CAN_ID_NUM)	// 接送ID（ID段0x7000 + 序号）
#else
#include "bsp_mavlink.h"
#include "bsp_usart.h"
#define CAN_EXT_ID_TX	(0x6000 | CAN_ID_NUM)	// 发送ID（ID段0x6000 + 序号）
#define CAN_EXT_ID_RX	(0x7000 | CAN_ID_NUM)	// 接送ID（ID段0x7000 + 序号）
#endif


#ifndef MAX_FRAME_SIZE
#define MAX_FRAME_SIZE 64
#endif


void BspFDCanInit(void);


void FDCanSendMsg(uint32_t can_id, uint8_t *msg, uint32_t length_code);
void FDCanPacketSend(uint8_t *rx_data, uint16_t len);
void FDCan_RxFifo0RxHandler_callback(uint32_t RxFrameType, uint8_t *Data, uint32_t DataLength);


#if IS_CAN_SLAVE

#ifndef MAVLINK_STX
#define MAVLINK_STX 254
#endif

#define RECV_BUFF_SIZE       (263)		// mavlink V1.0协议帧最大字节(帧头1+指令5+数据255+校验2)
#define MAVLINK_MAX_PAYLOAD_LEN 255 	///< Maximum payload length

typedef struct {

	uint8_t magic;   			///< protocol magic marker
	uint8_t len;     			///< Length of payload
	uint8_t seq;     			///< Sequence of packet
	uint8_t sysid;   			///< ID of message sender system/aircraft
	uint8_t compid;  			///< ID of the message sender component
	uint8_t msgid;   			///< ID of message in payload
	uint8_t payload[MAVLINK_MAX_PAYLOAD_LEN];	// payload

	union{
		uint16_t value; 		///< sent at end of packet
		struct
        {
			uint8_t low;  // 低8位
			uint8_t high; // 高8位
        } bytes;
    } checksum;
} mavlink_message_frame_t;
#endif



typedef enum {
    HOST_NONE,       // 无控制
    HOST_485,        // 485控制
    HOST_CAN         // CAN控制
} HostMode;

typedef struct {

	FDCAN_RxHeaderTypeDef RxHead;
	FDCAN_TxHeaderTypeDef TxHead;

	uint8_t packet_count; 				// 分包计数
	uint8_t packet_index; 				// 当前接收位置
	uint8_t isPacketComplete; 		// 分包接收完成标志位
	uint8_t	fdcan_rxdata[64];
	uint32_t can_rx_id;
	uint32_t can_tx_id;
	uint32_t packet_rev_cnt;
	uint32_t packet_sen_cnt;
	char rx_buff[RECV_BUFF_SIZE];
	mavlink_message_frame_t rxFram;	// 协议帧
	HostMode host_mode;

} FDCAN_Frame_TypeDef;

extern FDCAN_Frame_TypeDef kFDCanFra;

#ifdef __cplusplus
}
#endif

#endif	/* __BSP_CAN_H__ */

