#ifndef BOARD_H
#define BOARD_H

#include "main.h"

#include "motor_ctl_loop.h"
#include "mavlink_callback.h"

#include "system_init.h"
#include "system_timer.h"
#include "drv_encoder.h"
#include "drv_spi_flash.h"

typedef struct
{
    uint16_t adc1_raw_buffer[3];
    uint16_t adc2_raw_buffer[3];
    uint16_t adc3_raw_buffer[3];
    float dc_bus_voltage_val;
    float dc_bus_current_val;
    float motor_temp_val;
    float mos_temp_val;
    float mcu_temp[3];
    volatile float uvw_current[3];
    volatile float uvw_target_voltage[3];
    volatile uint32_t motor_cnt;
    volatile uint32_t load_cnt;
    volatile int64_t motor_turns;
    volatile int64_t load_turns;
    bool pwm_en_state;
    bool pwm_ready_state;
    uint32_t pwm_state_cnt;
} BspData;


#pragma region // MCU 外设寄存器映射
#pragma region // ANALOG
#define ADC_REFERENCE_V             (3.3f)      // ADC参考电压(V)
#define ADC_REFERENCE_MV            (3300)      // ADC参考电压(mV)
#define ADC_RESOLTION               (65536.0f)  // ADC采样分辨率(16位)

#define UVW_CURRENT_U_HANDLE        (hadc1)
#define UVW_CURRENT_V_HANDLE        (hadc2)
#define UVW_CURRENT_W_HANDLE        (hadc3)
#define UVW_CURRENT_U_CHANNEL       (UVW_CURRENT_U_HANDLE.Instance->JDR1)
#define UVW_CURRENT_V_CHANNEL       (UVW_CURRENT_V_HANDLE.Instance->JDR1)
#define UVW_CURRENT_W_CHANNEL       (UVW_CURRENT_W_HANDLE.Instance->JDR1)
#define CURRENT_LOOP_IRQ_TASK       HAL_ADCEx_InjectedConvCpltCallback

#define ADC1_REGULAR_RANK_NUMBER    (2)
#define ADC2_REGULAR_RANK_NUMBER    (2)
#define ADC3_REGULAR_RANK_NUMBER    (2)

#define DC_BUS_VOLTAGE_HANDLE       (hadc1)
#define DC_BUS_CURRENT_HANDLE       (hadc1)
#define DC_BUS_VOLTAGE_RANK1_INDEX  (0)
#define DC_BUS_CURRENT_RANK2_INDEX  (1)
#define TEMP_MOS_HANDLE             (hadc2)
#define USER_ADC1_HANDLE            (hadc2)
#define TEMP_MOS_RANK1_INDEX        (0)
#define USER_ADC1_RANK2_INDEX       (1)
#define TEMP_MCU_HANDLE             (hadc3)
#define TEMP_MOTOR_HANDLE           (hadc3)
#define TEMP_MCU_RANK1_INDEX        (0)
#define TEMP_MOTOR_RANK2_INDEX      (1)
#pragma endregion // ANALOG

#pragma region // TIMERS
#define PWM_TIM_ARR                 (6000u)  // PWM定时器ARR值，此宏可直接用于CubeMX配置框（No Check）
#define PWM_TIM_ARR_HALF            (3000u)  // PWM定时器ARR值的一半，此宏可直接用于CubeMX配置框（No Check）
#define PWM_TIM_ARR_P_LIMIT         (5400u)  // PWM定时器ARR上限值（PWM_TIM_ARR * 90%）
#define PWM_TIM_ARR_LIMIT_HALF      (2700u)  // PWM定时器ARR上限值的一半
#define PWM_TIM_ARR_N_LIMIT         (0u)     // PWM定时器ARR下限值（0）

#define PWM_TIM_HANDLE              (htim1)
#define PWM_TIM_U_CHANNEL           (TIM_CHANNEL_1)
#define PWM_TIM_V_CHANNEL           (TIM_CHANNEL_2)
#define PWM_TIM_W_CHANNEL           (TIM_CHANNEL_3)
#define PWM_TIM_U_CCR_VAL           (PWM_TIM_HANDLE.Instance->CCR1)
#define PWM_TIM_V_CCR_VAL           (PWM_TIM_HANDLE.Instance->CCR2)
#define PWM_TIM_W_CCR_VAL           (PWM_TIM_HANDLE.Instance->CCR3)
#define PWM_TIM_BREAK_IRQ_HANDLE    HAL_TIMEx_BreakCallback

#define BRAKE_PWM_TIM_HANDLE        (htim2)             //PWM抱闸IO输出定时器
#define ENCODER_ABZ_TIM_HANDLE      (htim3)             //ABZ增量式编码器定时器
#define ENCODER_ABZ_TIM_Z_CHANNEL   (TIM_CHANNEL_3)     //ABZ增量式编码器定时器Z相捕获通道
#define CANOPEN_TIM_HANDLE          (htim6)             //CANopen定时器
#define ECAT_LAN9252_TIM_HANDLE     (htim7)             //EtherCAT定时器
#define NRT_TASK_TIM_HANDLE         (htim13)            //非实时(1ms)任务定时器
#define NRT_CAN_ECAT_IRQ_TASK       HAL_TIM_PeriodElapsedCallback
#pragma endregion // TIMERS

#pragma region // CONNECTIVITY
#define CAN_FDCAN_HANDLE            (hfdcan1)

#define ECAT_LAN9252_QSPI_HANDLE    (hqspi)

#define ENCODER1_SPI_HANDLE         (hspi1)
#define ENCODER2_SPI_HANDLE         (hspi2)
#define AF_SPI_HANDLE               (hspi3)
#define DRV_SPI_HANDLE              (AF_SPI_HANDLE)
#define DRV_SPI_CS_ENABLE()         (HAL_GPIO_WritePin(DRV_AF_SPI_NSS_GPIO_Port, DRV_AF_SPI_NSS_Pin, GPIO_PIN_RESET))
#define DRV_SPI_CS_DISABLE()        (HAL_GPIO_WritePin(DRV_AF_SPI_NSS_GPIO_Port, DRV_AF_SPI_NSS_Pin, GPIO_PIN_SET))
#define FLASH_SPI_HANDLE            (AF_SPI_HANDLE)
#define FLASH_SPI_CS_ENABLE()       (HAL_GPIO_WritePin(FLASH_AF_SPI_NSS_GPIO_Port, FLASH_AF_SPI_NSS_Pin, GPIO_PIN_RESET))
#define FLASH_SPI_CS_DISABLE()      (HAL_GPIO_WritePin(FLASH_AF_SPI_NSS_GPIO_Port, FLASH_AF_SPI_NSS_Pin, GPIO_PIN_SET))

#define ENCODER_DUAL_UART_HANDLE    (huart4)
#define ENCODER1_UART_HANDLE        (huart4)
#define ENCODER2_UART_HANDLE        (huart8)

#define HOST_UART_HANDLE            (huart2)
#define HOST_UART_IRQ_TASK          USART2_IRQHandler
#define HOST_UART_ERROR_HANDLE      HAL_UART_ErrorCallback

#define USER_IIC_HANDLE             (hi2c1)
#define USER_USART_HANDLE           (husart1)

#define USER_SPI_HANDLE             (hspi6)
#define USER_SPI_CS_ENABLE()        (HAL_GPIO_WritePin(USER_SPI_NSS_GPIO_Port, USER_SPI_NSS_Pin, GPIO_PIN_RESET))
#define USER_SPI_CS_DISABLE()       (HAL_GPIO_WritePin(USER_SPI_NSS_GPIO_Port, USER_SPI_NSS_Pin, GPIO_PIN_SET))
#pragma endregion // CONNECTIVITY

#pragma region // GPIO
#define DRV_GATE_ENABLE()           (HAL_GPIO_WritePin(DRV_EN_GATE_GPIO_Port, DRV_EN_GATE_Pin, GPIO_PIN_SET))
#define DRV_GATE_DISABLE()          (HAL_GPIO_WritePin(DRV_EN_GATE_GPIO_Port, DRV_EN_GATE_Pin, GPIO_PIN_RESET))

#define ECAT_IRQ_EXTI_LINE          (ECAT_IRQ_Pin)
#define ECAT_IRQ_ECTI_IRQN          (ECAT_IRQ_EXTI_IRQn)
#define ECAT_SYNC0_EXTI_LINE        (ECAT_SYNC0_Pin)
#define ECAT_SYNC0_EXTI_IRQN        (ECAT_SYNC0_EXTI_IRQn)
#define ECAT_SYNC1_EXTI_LINE        (ECAT_SYNC1_Pin)
#define ECAT_SYNC1_EXTI_IRQN        (ECAT_SYNC1_EXTI_IRQn)
#define ECAT_EXTI_IRQ_TASK          HAL_GPIO_EXTI_Callback


#define LED_RED_ON()                (HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET))
#define LED_RED_OFF()               (HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET))
#define LED_RED_TOGGLE()            (HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin))
#define LED_BLUE_ON()               (HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET))
#define LED_BLUE_OFF()              (HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET))
#define LED_BLUE_TOGGLE()           (HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin))

#define USER_IO1_READ()             (HAL_GPIO_ReadPin(USER_IO1_GPIO_Port, USER_IO1_Pin))
#define USER_IO1_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO1_GPIO_Port, USER_IO1_Pin, (GPIO_PinState)pin_state))
#define USER_IO2_READ()             (HAL_GPIO_ReadPin(USER_IO2_GPIO_Port, USER_IO2_Pin))
#define USER_IO2_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO2_GPIO_Port, USER_IO2_Pin, (GPIO_PinState)pin_state))
#define USER_IO3_READ()             (HAL_GPIO_ReadPin(USER_IO3_GPIO_Port, USER_IO3_Pin))
#define USER_IO3_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO3_GPIO_Port, USER_IO3_Pin, (GPIO_PinState)pin_state))
#define USER_IO4_READ()             (HAL_GPIO_ReadPin(USER_IO4_GPIO_Port, USER_IO4_Pin))
#define USER_IO4_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO4_GPIO_Port, USER_IO4_Pin, (GPIO_PinState)pin_state))
#define USER_IO5_READ()             (HAL_GPIO_ReadPin(USER_IO5_GPIO_Port, USER_IO5_Pin))
#define USER_IO5_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO5_GPIO_Port, USER_IO5_Pin, (GPIO_PinState)pin_state))
#define USER_IO6_READ()             (HAL_GPIO_ReadPin(USER_IO6_GPIO_Port, USER_IO6_Pin))
#define USER_IO6_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO6_GPIO_Port, USER_IO6_Pin, (GPIO_PinState)pin_state))
#define USER_IO7_READ()             (HAL_GPIO_ReadPin(USER_IO7_GPIO_Port, USER_IO7_Pin))
#define USER_IO7_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO7_GPIO_Port, USER_IO7_Pin, (GPIO_PinState)pin_state))
#pragma endregion // GPIO

#pragma endregion // MCU 外设寄存器映射

extern BspData kBspData;

void BspInit(void);
void mavlink_send_data(uint8_t *pdata, uint32_t len);

#ifdef __cplusplus
extern "C"
{
#endif


#ifdef __cplusplus
}
#endif


#endif// BOARD_H
