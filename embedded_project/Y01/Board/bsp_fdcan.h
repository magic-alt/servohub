#ifndef __BSP_FDCAN_H
#define __BSP_FDCAN_H

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FDCAN_DATA_LEN_MAX          (64u)

typedef enum {
    // ... Other CAN baudrates
    FDCAN_BAUDRATE_125K_BPS = 125000u,
    FDCAN_BAUDRATE_250K_BPS = 250000u,
    FDCAN_BAUDRATE_500K_BPS = 500000u,
    FDCAN_BAUDRATE_1M_BPS   = 1000000u
    // ... Other CAN baudrates
} FDCAN_BaudrateTypeDef;

/**
 * @brief FDCAN设备结构体
 */
typedef struct {
    FDCAN_HandleTypeDef *handle;        // FDCAN句柄指针
    FDCAN_FilterTypeDef sFilterConfig;  // 过滤器配置
    FDCAN_RxHeaderTypeDef rx_header;    // 接收帧头
    FDCAN_TxHeaderTypeDef tx_header;    // 发送帧头
    FDCAN_BaudrateTypeDef baudrate;     // 波特率
    uint32_t id;                        // CAN通信ID
    uint32_t mg_counts;                 // 接收消息计数器
    uint8_t rx_data[FDCAN_DATA_LEN_MAX];// 接收数据缓冲区
    uint8_t tx_data[FDCAN_DATA_LEN_MAX];// 发送数据缓冲区
} FDCAN_DeviceTypeDef;


FDCAN_DeviceTypeDef* fdcan_get_bsp_fdcan(void);
void fdcan_init(void);
HAL_StatusTypeDef fdcan_send_message(FDCAN_DeviceTypeDef* bsp_fdcan, uint32_t id, \
                                    uint8_t rtr, uint8_t* data, uint8_t len);
void fdcan_set_id(uint32_t can_id);
uint32_t fdcan_get_id(void);
void fdcan_set_baudrate(uint32_t baudrate);
uint32_t fdcan_get_baudrate(void);
uint32_t fdcan_get_mg_counts(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_FDCAN_H */
