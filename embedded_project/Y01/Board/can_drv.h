#ifndef CAN_DRV_H
#define CAN_DRV_H

#ifdef __cplusplus
 extern "C" {
#endif
#include "board.h"

void check_can_error(void);
void can_device_init(void);
void can_device_set_id(uint32_t can_id);
void can_device_set_baudrate(uint32_t baudrate);
uint32_t can_device_get_id(void);
uint32_t can_device_get_baudrate(void);
uint32_t can_device_get_mg_counts(void);
#ifdef __cplusplus
}
#endif

#endif /* CAN_DRV_H */
