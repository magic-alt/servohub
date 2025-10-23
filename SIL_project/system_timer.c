#include "system_timer.h"

static SysTimer_t sys_timer = {
    .sys_freq_Mhz = 0,
    .sys_freq_Mhz_inv = 0,
    .now_records = {0},
    .duration_records = {0},
};

void sys_timer_init(void)
{
    
}

void set_timer_record_start(uint8_t index)
{
    
}

void set_timer_record_stop(uint8_t index)
{
    
}

uint32_t get_time_duration_records(uint8_t index)
{
    return 1;
}

static uint32_t sys_timer_get_ticks(void)
{
    return 1;
}

void sys_blocking_delay_us(uint32_t us)
{
    
}

void sys_blocking_delay_ms(uint32_t ms)
{
    
}

float get_sys_timer_freq_Mhz_inv(void)
{
    return sys_timer.sys_freq_Mhz_inv;
}