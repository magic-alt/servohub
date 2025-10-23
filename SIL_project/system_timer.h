#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
}
#endif

#define SYS_TIMER_RECORD_MAX_INDEX      10
typedef struct
{
    uint32_t now_records[SYS_TIMER_RECORD_MAX_INDEX];
    uint32_t duration_records[SYS_TIMER_RECORD_MAX_INDEX];
    uint32_t sys_freq_Mhz;
    float sys_freq_Mhz_inv;
} SysTimer_t;

// #define CURRENT_LOOP_CYCLE_INDEX 0  // 电流环周期
// #define POSITION_LOOP_CYCLE_INDEX 1 // 位置环周期

// #define CURRENT_LOOP_TIME_INDEX 2   // 电流环时间
// #define POSITION_LOOP_TIME_INDEX 3  // 位置环时间

// #define TIM_1MS_CYCLE_INDEX 4       // 1ms定时器任务周期
// #define TIM_1MS_TIME_INDEX 5        // 1ms定时器任务时间

void sys_timer_init(void);
void set_time_record_start(uint8_t index);
void set_time_record_stop(uint8_t index);
void sys_delay_us(uint32_t us);
void sys_delay_ms(uint32_t ms);
uint32_t get_time_duration_records(uint8_t index);
float get_sys_timer_freq_Mhz_inv(void);

#ifdef __cplusplus
}
#endif

#endif