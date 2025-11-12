#ifndef DRV_CAN_APP_H
#define DRV_CAN_APP_H

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef USE_CAN
void fdcan_app_init(void);
void fdcan_app_fifo0_handle(FDCAN_HandleTypeDef* hfdcan);
void fdcan_app_fifo1_handle(FDCAN_HandleTypeDef* hfdcan);

#ifdef USE_CANOPEN
void CANopen_DispatchFromISR(void);
#endif // USE_CANOPEN

#endif // USE_CAN
#ifdef __cplusplus
}
#endif

#endif // DRV_CAN_APP_H
