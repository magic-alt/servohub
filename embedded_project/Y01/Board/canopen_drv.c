#include "canopen_drv.h"

void can_device_init(void);

CO_Data SlaveData;

uint32_t NextTime = 0;
uint32_t time_cnt = 0;
uint32_t last_time_set = 0;
#define TIMER_MAX_COUNT 0xFFFF

#define nodeID 0x01

void canopen_init(void){
    can_device_init();
    HAL_TIM_Base_Start_IT(&CANOPEN_TIM_HANDLE);
    setNodeId(&SlaveData, nodeID);
    setState(&SlaveData, Initialisation);
    setState(&SlaveData, Operational);
}


//Set the next alarm
void setTimer (TIMEVAL value)
{
    NextTime = (time_cnt + value) % TIMER_MAX_COUNT;
}


// Get the elapsed time since the last occured alarm
TIMEVAL getElapsedTime (void){
    int ret=0;
    ret = (time_cnt > last_time_set) ? (time_cnt - last_time_set) : (time_cnt + TIMER_MAX_COUNT - last_time_set);
    last_time_set = time_cnt;
    
    return ret;
}


//系统创建1ms定时器周期调用timerForCan()
void timerForCan(void)
{
    time_cnt++;
    if (time_cnt >= TIMER_MAX_COUNT){
        time_cnt = 0;
    }
    if(time_cnt==NextTime){
        TimeDispatch();
    }
}


uint8_t canSend(CAN_PORT notused, Message *m){
    uint8_t i;
    CAN_TxHeaderTypeDef txHeader;
    uint8_t txData[8] = {0};
    uint32_t txMailbox;

    txHeader.StdId = m->cob_id;
    txHeader.ExtId = 0;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = m->rtr ? CAN_RTR_REMOTE : CAN_RTR_DATA;
    txHeader.DLC = m->len;
    txHeader.TransmitGlobalTime = DISABLE;

    for (i = 0; i < m->len; i++) {
        txData[i] = m->data[i];
    }

    if (HAL_CAN_AddTxMessage(&CAN_FDCAN_HANDLE, &txHeader, txData, &txMailbox) != HAL_OK) {
        return 0xFF;
    } else {
        return 0x00;
    }
}

void canRecv(CAN_RxHeaderTypeDef *pHeader, uint8_t aData[])
{
    uint8_t i;
    Message msg;
    
    memset(&msg, 0, sizeof(msg));
    
    msg.cob_id = pHeader->StdId;
    
    if(pHeader->RTR == CAN_RTR_REMOTE){
        msg.rtr = 1;
    }
    else if(pHeader->RTR == CAN_RTR_DATA){
        msg.rtr = 0;
    }

    msg.len = pHeader->DLC;

    for(i = 0; i < pHeader->DLC; i++)
        msg.data[i] = aData[i];
    
    canDispatch(&SlaveData, &msg);
}


void can_device_init(void)
{
    CAN_FilterTypeDef  can_filter;

    can_filter.FilterBank           = 0;
    can_filter.FilterMode           = CAN_FILTERMODE_IDMASK;
    can_filter.FilterScale          = CAN_FILTERSCALE_32BIT;
    can_filter.FilterIdHigh         = 0x0000;
    can_filter.FilterIdLow          = 0x0000;
    can_filter.FilterMaskIdHigh     = 0x0000;
    can_filter.FilterMaskIdLow      = 0x0000;
    can_filter.FilterFIFOAssignment = CAN_FilterFIFO0;
    can_filter.SlaveStartFilterBank = 0;
    can_filter.FilterActivation     = ENABLE;

    HAL_CAN_ConfigFilter(&CAN_FDCAN_HANDLE, &can_filter);
    while (HAL_CAN_ConfigFilter(&CAN_FDCAN_HANDLE, &can_filter) != HAL_OK);

    HAL_CAN_Start(&CAN_FDCAN_HANDLE);
    HAL_CAN_ActivateNotification(&CAN_FDCAN_HANDLE,CAN_IT_RX_FIFO0_MSG_PENDING);
}