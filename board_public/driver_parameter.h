#ifndef DRIVER_PARAMETER_H
#define DRIVER_PARAMETER_H

// 整个驱动器硬件参数

#ifdef __cplusplus
extern "C"
{
#endif

// 转换因子用户根据硬件定义
#define ADC_REFERENCE_V (3.3f)              // ADC参考电压(V)
#define ADC_REFERENCE_MV (3300)             // ADC参考电压(mV)
#define ADC_RESOLTION (65535.0f)            // 采样ADC分辨率
#define UVW_CURRENT_SAMP_RES (0.002f)       // UVW电流采样电阻值 Ω
#define DC_BUS_CURRENT_SAMP_RES (0.001f)    // DC_BUS电流采样电阻值 Ω
#define UVW_CURRENT_SAMP_ADC_K (ADC_REFERENCE_V / ADC_RESOLTION / (20.0f * UVW_CURRENT_SAMP_RES))       //电流采样ADC转化系数
#define DC_BUS_CURRENT_SAMP_ADC_K (ADC_REFERENCE_V / ADC_RESOLTION / (20.0f * DC_BUS_CURRENT_SAMP_RES)) //电流采样ADC转化系数
#define DC_BUS_ADC_VOLTAGE_K (ADC_REFERENCE_V / ADC_RESOLTION * ((100.f + ADC_REFERENCE_V) / ADC_REFERENCE_V)) //3.3v参考电压，电阻分压比100K/3.3K，16bitADC
#define DC_BUS_ADC_VOLTAGE_BIAS (0.374f)
#define DC_BUS_ADC_CURRENT_BIAS (0.100f)

#define UVW_CURRENT_MID_VAL ((ADC_RESOLTION + 1.0f) * 0.5f) // 电流校准理论值（分辨率中间值）
#define UVW_CURRENT_ERROR_RANGE (0.1f) // 电流校准误差范围(10%)
#define UVW_CURRENT_DIRECTION (1.0f) // 电流采样方向 1：正向  -1：反向

// 硬件固有参数
#define CURRENT_FREQUENCY_HZ            (20000.0f)  // 电流环工作频率
#define POSITION_FREQUENCY_HZ           (10000.0f)  // 位置环工作频率
#define CURRENT_SAMP_NOISE_A            (0.3f)      // 电流采样噪声绝对值
#define VOLTAGE_COMPENSATION_V          (0.00f)     // 电压补偿值
#define DRIVER_RATED_CURRENT_A          (38.0F)     // 驱动器额定电流 iq峰值电流
#define DRIVER_PEAK_CURRENT_A           (76.0F)     // 驱动器峰值电流 iq峰值电流
#define DRIVER_OVERCURRENT_LIMIT_A      (100.0F)    // 驱动器过电流保护阈值
#define MOTOR_TO_IN_VOLTAGE_RATIO       (1.022f)    // TEMP_MOT到TEMP_MOT_IN的电压转换系数
#define MOTOR_TEMP_SENSOR_K             (-0.31283F) // (0℃-120℃)/(ADC(0) - ADC(120))
#define MOTOR_TEMP_SENSOR_BIAS          (645.72F)   // 0℃ 时候 偏置值
#define DRIVER_PWM_READY_TIME           (0)         // PWM使能后等待时间 (单位 位置环周期数)
#define MOS_TEMP_VOLTAGE_K              (3300.0f / ADC_RESOLTION) // MOS温度传感器电压转换系数
#define MOS_TEMP_SENSOR_K               (0.1f)      // MOS温度传感器温度系数
#define MOS_TEMP_SENSOR_BIAS            (500.0f)    // MOS温度传感器偏移值


// 硬件保护参数
#define UNDER_VOLTAGE_PROTECTION_V      (24.0f)     // 低压保护电压
#define OVER_VOLTAGE_PROTECTION_V       (70.0f)     // 高压保护电压

#define K_LPF_TEMP                      (0.3859f)   // 温度滤波系数  100HZ  1ms周期
#define MOTOR_NTC_FAULT_C               (600.0f * K_LPF_TEMP)    // 电机温度NTC传感器故障温度阈值
#define OVER_TEMP_PROTECTION_C          (115.0f)    // 高温保护温度
#define OVER_TEMP_WARNING_C             (105.0f)    // 高温警告温度
#define UNDER_TEMP_PROTECTION_C         (-40.0f)    // 低温保护温度
#define UNDER_TEMP_WARNING_C            (-25.0f)    // 低温警告温度


#ifdef __cplusplus
}
#endif

#endif // DRIVER_PARAMETER_H
