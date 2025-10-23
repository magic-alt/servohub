#ifndef CANOPEN_DRV_H
#define CANOPEN_DRV_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "version.h"

#include "time.h"
#include "SlaveOD.h"
#include "data.h"
#include "states.h"
#include "can.h"
#include "canfestival.h"
#include "main.h"
#include "board.h"
//该文件的接口配置 根据cubeMX Time设置进行修改
#define CANOPEN_TIMx              (TIM_HandleTypeDef *)&CANOPEN_TIM_HANDLE
#define CANOPEN_TIM_PERIOD        999         //(1000-1) 定时周期 与cubeMX中设置相同
#define TX_BUFFER_SIZE 16

typedef struct
{
    Message buf[TX_BUFFER_SIZE];
    uint8_t buf_st;
    uint8_t buf_ed;
    uint8_t buf_empty;
}can_tx_buffer_t;
extern can_tx_buffer_t can_tx_buffer;
extern uint8_t fdcan_rx_msg[8];

extern FDCAN_RxHeaderTypeDef RxHeader;
extern FDCAN_TxHeaderTypeDef TxHeader;

void TIMx_DispatchFromISR(void);
UNS32 SlaveOD_Read_Callback(uint16_t index, uint8_t subindex, void *data);
UNS32 SlaveOD_Write_Callback(uint16_t index, uint8_t subindex, void *data);


#ifdef __cplusplus
}
#endif

#endif /* CANOPEN_DRV_H */
