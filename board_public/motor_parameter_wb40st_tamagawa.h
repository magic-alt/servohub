#ifndef MOTOR_PARAMETER_WB40ST_TAMAGAWA_H
#define MOTOR_PARAMETER_WB40ST_TAMAGAWA_H

// 整个模组参数，电机参数、编码器参数、减速器参数

#ifdef __cplusplus
extern "C"
{
#endif

// 电机、编码器参数
#define PMSM_J (5.0E-6F)                            // 电机转动惯量
#define PMSM_Lp2p (0.38e-03F)                       // 相间电感
#define PMSM_Rp2p (0.4F)                            // 相间电阻
#define PMSM_RATED_CURRENT (6.5F)                   // 电机额定电流
#define PMSM_PEAK_CURRENT (19.5F)                   // 电机峰值电流
#define PMSM_PN (5.0F)                              // 极对数
#define PMSM_SPEED_MAX_RPM (6000.0F)                // 电机最大转速
#define PMSM_TORQUE_CONSTANT_MNM_A (50.0F)          // 电机转矩常数 mN*M/A
#define PMSM_ENC_LINE_ORG (131072u)                 // 电机端编码器原始分辨率
#define PMSM_ENC_LINE_LESS_BITS (0u)                // 电机端编码器原始分辨率 降位位数
#define PMSM_ENC_LINE_P_N (PMSM_ENC_LINE_ORG >> \
                    PMSM_ENC_LINE_LESS_BITS)        // 电机端编码器实际分辨率
#define PMSM_LOAD_ENC_LINE_ORG (131072u)            // 负载端编码器原始分辨率
#define PMSM_LOAD_ENC_LINE_LESS_BITS (0u)           // 负载端编码器原始分辨率 降位位数
#define PMSM_LOAD_ENC_LINE_P_N (PMSM_LOAD_ENC_LINE_ORG >> \
                    PMSM_LOAD_ENC_LINE_LESS_BITS)   // 负载端编码器实际分辨率
#define PMSM_ENC_MULTI_LINE_P_N (0u)                // 电机端编码器多圈分辨率
#define PMSM_LOAD_ENC_MULTI_LINE_P_N (0u)           // 负载端编码器多圈分辨率
#define PMSM_MOTOR_ENC_DIR (1)                      // 电机端编码器方向  1 正方向  -1 反方向
#define PMSM_LOAD_ENC_DIR (1)                       // 负载端编码器方向  1 正方向  -1 反方向

#define MOTOR_HIGH_TEMP_FAULT_THRESHOLD (145.0f)    // 电机过温保护阈值
#define MOTOR_LOW_TEMP_FAULT_THRESHOLD (-40.0f)     // 电机低温保护阈值
#define MOTOR_HIGH_TEMP_WARING_THRESHOLD (120.0f)   // 电机过温警告阈值
#define MOTOR_LOW_TEMP_WARING_THRESHOLD (-20.0f)    // 电机低温警告阈值

// 电流环参数
#define CURRENT_CTL_CONFIG_KP_LD (6.33e-01f)              // d轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LD (1.05e+03f)              // d轴电流环积分增益
#define CURRENT_CTL_CONFIG_KP_LQ (6.33e-01f)              // q轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LQ (1.05e+03f)              // q轴电流环积分增益
#define CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX (1.0F)      // 最大占空比
#define CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION (4.0f) // 电角度补偿系数
#define CURRENT_CTL_CONFIG_PHASE_DIR (1)                  // 电机相序 1:abc -1:cba

// 位置速度环参数
#define POS_SPEED_CTL_CONFIG_KP_P (1.47e+02f) // 位置环比例增益
#define POS_SPEED_CTL_CONFIG_KI_S (1.47e+02f) // 速度环积分增益
#define POS_SPEED_CTL_CONFIG_KP_S (1.18e-01f) // 速度环比例增益
#define POS_SPEED_CTL_CONFIG_J_KT (1.00e-04f) // 惯性系数
#define POS_SPEED_CTL_CONFIG_AFF (0.0f)       // 加速度前馈增益
#define POS_SPEED_CTL_CONFIG_VFF (1.0f)       // 速度前馈增益

// 负载扰动观测器
#define POS_SPEED_CTL_CONFIG_DOB_ENABLE (0)        // 负载扰动观测器使能
#define POS_SPEED_CTL_CONFIG_DOB_WN_HZ (4.00e+02f) // 负载扰动观测器角频率

// 速度观测器带宽
#define SPEED_OBS_PLL_WN_HZ (9.60e+02f)

// 减速比参数
#define GEAR_RATIO_NUM (1) // 减速比分子
#define GEAR_RATIO_DEN (1) // 减速比分母
#define GEAR_RATIO (1.0f)  // 减速比

// 温度传感器参数
#define MOTOR_TEMP_SENSOR_K             (-0.31283F) // (0℃-120℃)/(ADC(0) - ADC(120))
#define MOTOR_TEMP_SENSOR_BIAS          (645.72F)   // 0℃ 时候 偏置值

// 抱闸相关参数
#define BRAKE_ENGAGE_TIME (0.0f)               // 抱闸延迟时间
#define BRAKE_RELEASE_TIME (0.0f)              // 松闸延迟时间
#define DYNAMIC_BRAKE_SPEED_THRESHOLD (100.0f) // 抱闸制动速度阈值
#define BRAKE_RELEASE_HOLD_VOLTAGE (12.0f)     // 松闸保持电压

// 编码器校准相关参数
#define ENC_CALI_FRE (1000)
#define ENC_CALI_MAX_CURRENT (10.0f) // 最大校准增益，IF模式该值表示10A电流

#define ENC_CALI_TIME_PERIOD (500) // 500ms周期运行
#define ENC_CALI_FRE_INC (0.5f)    // 每个周期增加0.5Hz

#define ENC_CALI_SPEED_0 (10.0f)    // 第一阶段目标转速（Hz）
#define ENC_CALI_SPEED_1 (20.0f)    // 第二阶段目标转速（Hz）
#define ENC_CALI_SPEED_SW_0 (30.0f) // 达到30RPM打开编码器校准模式
#define ENC_CALI_SPEED_SW_1 (40.0f) // 达到30RPM打开编码器校准模式

#define ENC_CALI_CHECK_CNT (6) // 编码器状态查询周期s
#define ENC_CALI_TIMEOUT (600) // 启动app120s后编码器校准模式超时

#ifdef __cplusplus
}
#endif

#endif // MOTOR_PARAMETER_WB40ST_TAMAGAWA_H
