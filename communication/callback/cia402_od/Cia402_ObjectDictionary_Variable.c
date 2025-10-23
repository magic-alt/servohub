#include "Cia402_ObjectDictionary_Variable.h"

/* USER CODE BEGIN AREA 0 */
#include "cia402_fsm.h"
#include "coordinate_conversion.h"
#include "data_param.h"

//64位转32位，符号位处理
INTEGER32 limit_64_to_32(int64_t val_64)
{
    int32_t val_32 = val_64;
    if(val_64 & 0x8000000000000000){
        val_32 |= 0x80000000;
    }
    else {
        val_32 &= 0x7FFFFFFF;
    }
    return val_32;
}

/* USER CODE END AREA 0 */

PDS_FSA kPDS_FSA;
Factor_group kFactor_group;
Profile_position_mode kProfile_position_mode;
Homing_mode kHoming_mode;
Position_control_function kPosition_control_function;
Profile_velocity_mode kProfile_velocity_mode;
Profile_torque_mode kProfile_torque_mode;
Manufacturer kManufacturer;

UNS32 set_Controlword(UNS16 val){
    /* USER CODE BEGIN set_Controlword 0 */
    /* USER CODE END set_Controlword 0 */
    kPDS_FSA.Controlword = val;
    /* USER CODE BEGIN set_Controlword 1 */
    controlword_change_PDAS_FSA();//cia402的控制字只影响PDS_FSA的状态机
    /* USER CODE END set_Controlword 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Controlword(void){
    /* USER CODE BEGIN get_Controlword */
    /* USER CODE END get_Controlword */
    return kPDS_FSA.Controlword;
}

UNS32 set_Statusword(UNS16 val){
    /* USER CODE BEGIN set_Statusword 0 */
    //cia402的控制字只能由PDS_FSA的状态机修改
    /* USER CODE END set_Statusword 0 */
    kPDS_FSA.Statusword = val;
    /* USER CODE BEGIN set_Statusword 1 */
    /* USER CODE END set_Statusword 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Statusword(void){
    /* USER CODE BEGIN get_Statusword */
    /* USER CODE END get_Statusword */
    return kPDS_FSA.Statusword;
}

UNS32 set_Error_code(UNS16 val){
    /* USER CODE BEGIN set_Error_code 0 */
    //cia402的错误码只能由PDS_FSA的状态机修改
    /* USER CODE END set_Error_code 0 */
    kPDS_FSA.Error_code = val;
    /* USER CODE BEGIN set_Error_code 1 */
    /* USER CODE END set_Error_code 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Error_code(void){
    /* USER CODE BEGIN get_Error_code */
    /* USER CODE END get_Error_code */
    return kPDS_FSA.Error_code;
}

UNS32 set_Quick_stop_option_code(INTEGER16 val){
    /* USER CODE BEGIN set_Quick_stop_option_code 0 */
    set_app_Quick_stop_option_code(val);
    /* USER CODE END set_Quick_stop_option_code 0 */
    kPDS_FSA.Quick_stop_option_code = val;
    /* USER CODE BEGIN set_Quick_stop_option_code 1 */
    /* USER CODE END set_Quick_stop_option_code 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Quick_stop_option_code(void){
    /* USER CODE BEGIN get_Quick_stop_option_code */
    kPDS_FSA.Quick_stop_option_code = get_app_Quick_stop_option_code(); 
    /* USER CODE END get_Quick_stop_option_code */
    return kPDS_FSA.Quick_stop_option_code;
}

UNS32 set_Modes_of_operation(INTEGER8 val){
    /* USER CODE BEGIN set_Modes_of_operation 0 */
    /* USER CODE END set_Modes_of_operation 0 */
    kPDS_FSA.Modes_of_operation = val;
    /* USER CODE BEGIN set_Modes_of_operation 1 */
    //目前支持的cia402模式:PP,PV,PT,HM,MIT
    switch(kPDS_FSA.Modes_of_operation){
        case kOd6060_PPM:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_POSITION);
            break;
        case kOd6060_PVM:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_SPEED);
            break;
        case kOd6060_TPM:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_TORQUE);
            break;
        case kOd6060_HM:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_HOMING);
            break;
        case kOd6060_MIT:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_MIT);
            break;
        default:
            break;
    }
    /* USER CODE END set_Modes_of_operation 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER8 get_Modes_of_operation(void){
    /* USER CODE BEGIN get_Modes_of_operation */
    //目前支持的cia402模式:PP,PV,PT,HM,MIT
    switch(get_app_Modes_of_operation()){
        case MOTOR_CTL_SM_MODE_POSITION:
            kPDS_FSA.Modes_of_operation = kOd6060_PPM;
            break;
        case MOTOR_CTL_SM_MODE_SPEED:
            kPDS_FSA.Modes_of_operation = kOd6060_PVM;
            break;
        case MOTOR_CTL_SM_MODE_TORQUE:
            kPDS_FSA.Modes_of_operation = kOd6060_TPM;
            break;
        case MOTOR_CTL_SM_MODE_HOMING:
            kPDS_FSA.Modes_of_operation = kOd6060_HM;
            break;
        case MOTOR_CTL_SM_MODE_MIT:
            kPDS_FSA.Modes_of_operation = kOd6060_MIT;
            break;
        default:
            break;
    }
    /* USER CODE END get_Modes_of_operation */
    return kPDS_FSA.Modes_of_operation;
}

UNS32 set_Modes_of_operation_display(INTEGER8 val){
    /* USER CODE BEGIN set_Modes_of_operation_display 0 */
    /* USER CODE END set_Modes_of_operation_display 0 */
    kPDS_FSA.Modes_of_operation_display = val;
    /* USER CODE BEGIN set_Modes_of_operation_display 1 */
    /* USER CODE END set_Modes_of_operation_display 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER8 get_Modes_of_operation_display(void){
    /* USER CODE BEGIN get_Modes_of_operation_display */
    switch(get_app_Modes_of_operation_display()){
        case MOTOR_CTL_SM_MODE_POSITION:
            kPDS_FSA.Modes_of_operation_display = kOd6060_PPM;
            break;
        case MOTOR_CTL_SM_MODE_SPEED:
            kPDS_FSA.Modes_of_operation_display = kOd6060_PVM;
            break;
        case MOTOR_CTL_SM_MODE_TORQUE:
            kPDS_FSA.Modes_of_operation_display = kOd6060_TPM;
            break;
        case MOTOR_CTL_SM_MODE_HOMING:
            kPDS_FSA.Modes_of_operation_display = kOd6060_HM;
            break;
        case MOTOR_CTL_SM_MODE_MIT:
            kPDS_FSA.Modes_of_operation_display = kOd6060_MIT;
            break;
        default:
            break;
    }
    /* USER CODE END get_Modes_of_operation_display */
    return kPDS_FSA.Modes_of_operation_display;
}

UNS32 set_Position_encoder_resolution(UNS8 val){
    /* USER CODE BEGIN set_Position_encoder_resolution 0 */
    /* USER CODE END set_Position_encoder_resolution 0 */
    kFactor_group.Position_encoder_resolution = val;
    /* USER CODE BEGIN set_Position_encoder_resolution 1 */
    /* USER CODE END set_Position_encoder_resolution 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Position_encoder_resolution(void){
    /* USER CODE BEGIN get_Position_encoder_resolution */
    /* USER CODE END get_Position_encoder_resolution */
    return kFactor_group.Position_encoder_resolution;
}

UNS32 set_Position_encoder_resolution_Encoder_increments(UNS32 val){
    /* USER CODE BEGIN set_Position_encoder_resolution_Encoder_increments 0 */
    /* USER CODE END set_Position_encoder_resolution_Encoder_increments 0 */
    kFactor_group.Position_encoder_resolution_Encoder_increments = val;
    /* USER CODE BEGIN set_Position_encoder_resolution_Encoder_increments 1 */
    set_app_Load_Encoder_resolution(val);   //设置负载端编码器分辨率
    /* USER CODE END set_Position_encoder_resolution_Encoder_increments 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Position_encoder_resolution_Encoder_increments(void){
    /* USER CODE BEGIN get_Position_encoder_resolution_Encoder_increments */
    kFactor_group.Position_encoder_resolution_Encoder_increments = get_app_Load_Encoder_resolution();
    /* USER CODE END get_Position_encoder_resolution_Encoder_increments */
    return kFactor_group.Position_encoder_resolution_Encoder_increments;
}

UNS32 set_Position_encoder_resolution_Motor_revolutions(UNS32 val){
    /* USER CODE BEGIN set_Position_encoder_resolution_Motor_revolutions 0 */
    /* USER CODE END set_Position_encoder_resolution_Motor_revolutions 0 */
    kFactor_group.Position_encoder_resolution_Motor_revolutions = val;
    /* USER CODE BEGIN set_Position_encoder_resolution_Motor_revolutions 1 */
    set_app_Motor_Encoder_resolution(val);  //设置电机端编码器分辨率
    /* USER CODE END set_Position_encoder_resolution_Motor_revolutions 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Position_encoder_resolution_Motor_revolutions(void){
    /* USER CODE BEGIN get_Position_encoder_resolution_Motor_revolutions */
    kFactor_group.Position_encoder_resolution_Motor_revolutions = get_app_Motor_Encoder_resolution();
    /* USER CODE END get_Position_encoder_resolution_Motor_revolutions */
    return kFactor_group.Position_encoder_resolution_Motor_revolutions;
}

UNS32 set_Gear_ratio(UNS8 val){
    /* USER CODE BEGIN set_Gear_ratio 0 */
    /* USER CODE END set_Gear_ratio 0 */
    kFactor_group.Gear_ratio = val;
    /* USER CODE BEGIN set_Gear_ratio 1 */
    /* USER CODE END set_Gear_ratio 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Gear_ratio(void){
    /* USER CODE BEGIN get_Gear_ratio */
    /* USER CODE END get_Gear_ratio */
    return kFactor_group.Gear_ratio;
}

UNS32 set_Motor_revolutions(UNS32 val){
    /* USER CODE BEGIN set_Motor_revolutions 0 */
    /* USER CODE END set_Motor_revolutions 0 */
    kFactor_group.Motor_revolutions = val;
    /* USER CODE BEGIN set_Motor_revolutions 1 */
    //电子齿轮比分母
    set_app_Reduction_Ratio_den(val);
    /* USER CODE END set_Motor_revolutions 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Motor_revolutions(void){
    /* USER CODE BEGIN get_Motor_revolutions */
    kFactor_group.Motor_revolutions = get_app_Reduction_Ratio_den();
    /* USER CODE END get_Motor_revolutions */
    return kFactor_group.Motor_revolutions;
}

UNS32 set_Shaft_revolutions(UNS32 val){
    /* USER CODE BEGIN set_Shaft_revolutions 0 */
    /* USER CODE END set_Shaft_revolutions 0 */
    kFactor_group.Shaft_revolutions = val;
    /* USER CODE BEGIN set_Shaft_revolutions 1 */
    //电子齿轮比分子
    set_app_Reduction_Ratio_num(val);
    /* USER CODE END set_Shaft_revolutions 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Shaft_revolutions(void){
    /* USER CODE BEGIN get_Shaft_revolutions */
    kFactor_group.Shaft_revolutions = get_app_Reduction_Ratio_num();
    /* USER CODE END get_Shaft_revolutions */
    return kFactor_group.Shaft_revolutions;
}

UNS32 set_Polarity(UNS8 val){
    /* USER CODE BEGIN set_Polarity 0 */
    /* USER CODE END set_Polarity 0 */
    kFactor_group.Polarity = val;
    /* USER CODE BEGIN set_Polarity 1 */
    set_app_Polarity(val);
    /* USER CODE END set_Polarity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Polarity(void){
    /* USER CODE BEGIN get_Polarity */
    kFactor_group.Polarity = get_app_Polarity();
    /* USER CODE END get_Polarity */
    return kFactor_group.Polarity;
}

UNS32 set_Target_position(INTEGER32 val){
    /* USER CODE BEGIN set_Target_position 0 */
    /* USER CODE END set_Target_position 0 */
    kProfile_position_mode.Target_position = val;
    /* USER CODE BEGIN set_Target_position 1 */
    set_app_Target_position(val);
    /* USER CODE END set_Target_position 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Target_position(void){
    /* USER CODE BEGIN get_Target_position */
    kProfile_position_mode.Target_position = get_app_Target_position();
    /* USER CODE END get_Target_position */
    return kProfile_position_mode.Target_position;
}

UNS32 set_Position_range_limit(UNS8 val){
    /* USER CODE BEGIN set_Position_range_limit 0 */
    /* USER CODE END set_Position_range_limit 0 */
    kProfile_position_mode.Position_range_limit = val;
    /* USER CODE BEGIN set_Position_range_limit 1 */
    /* USER CODE END set_Position_range_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Position_range_limit(void){
    /* USER CODE BEGIN get_Position_range_limit */
    /* USER CODE END get_Position_range_limit */
    return kProfile_position_mode.Position_range_limit;
}

UNS32 set_Position_range_limit_Minimal_position_limit(INTEGER32 val){
    /* USER CODE BEGIN set_Position_range_limit_Minimal_position_limit 0 */
    /* USER CODE END set_Position_range_limit_Minimal_position_limit 0 */
    kProfile_position_mode.Position_range_limit_Minimal_position_limit = val;
    /* USER CODE BEGIN set_Position_range_limit_Minimal_position_limit 1 */
    set_app_Position_range_limit_Minimal_position_limit(val);
    /* USER CODE END set_Position_range_limit_Minimal_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_range_limit_Minimal_position_limit(void){
    /* USER CODE BEGIN get_Position_range_limit_Minimal_position_limit */
    kProfile_position_mode.Position_range_limit_Minimal_position_limit = limit_64_to_32(get_app_Position_range_limit_Minimal_position_limit());
    /* USER CODE END get_Position_range_limit_Minimal_position_limit */
    return kProfile_position_mode.Position_range_limit_Minimal_position_limit;
}

UNS32 set_Position_range_limit_Maximal_position_limit(INTEGER32 val){
    /* USER CODE BEGIN set_Position_range_limit_Maximal_position_limit 0 */
    /* USER CODE END set_Position_range_limit_Maximal_position_limit 0 */
    kProfile_position_mode.Position_range_limit_Maximal_position_limit = val;
    /* USER CODE BEGIN set_Position_range_limit_Maximal_position_limit 1 */
    set_app_Position_range_limit_Maximal_position_limit(val);
    /* USER CODE END set_Position_range_limit_Maximal_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_range_limit_Maximal_position_limit(void){
    /* USER CODE BEGIN get_Position_range_limit_Maximal_position_limit */
    kProfile_position_mode.Position_range_limit_Maximal_position_limit = limit_64_to_32(get_app_Position_range_limit_Maximal_position_limit());
    /* USER CODE END get_Position_range_limit_Maximal_position_limit */
    return kProfile_position_mode.Position_range_limit_Maximal_position_limit;
}

UNS32 set_Software_position_limit(UNS8 val){
    /* USER CODE BEGIN set_Software_position_limit 0 */
    /* USER CODE END set_Software_position_limit 0 */
    kProfile_position_mode.Software_position_limit = val;
    /* USER CODE BEGIN set_Software_position_limit 1 */
    /* USER CODE END set_Software_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Software_position_limit(void){
    /* USER CODE BEGIN get_Software_position_limit */
    /* USER CODE END get_Software_position_limit */
    return kProfile_position_mode.Software_position_limit;
}

UNS32 set_Software_position_limit_Minimal_position_limit(INTEGER32 val){
    /* USER CODE BEGIN set_Software_position_limit_Minimal_position_limit 0 */
    /* USER CODE END set_Software_position_limit_Minimal_position_limit 0 */
    kProfile_position_mode.Software_position_limit_Minimal_position_limit = val;
    /* USER CODE BEGIN set_Software_position_limit_Minimal_position_limit 1 */
    set_app_Software_position_limit_Minimal_position_limit(val);
    /* USER CODE END set_Software_position_limit_Minimal_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Software_position_limit_Minimal_position_limit(void){
    /* USER CODE BEGIN get_Software_position_limit_Minimal_position_limit */
    kProfile_position_mode.Software_position_limit_Minimal_position_limit = limit_64_to_32(get_app_Software_position_limit_Minimal_position_limit());
    /* USER CODE END get_Software_position_limit_Minimal_position_limit */
    return kProfile_position_mode.Software_position_limit_Minimal_position_limit;
}

UNS32 set_Software_position_limit_Maximal_position_limit(INTEGER32 val){
    /* USER CODE BEGIN set_Software_position_limit_Maximal_position_limit 0 */
    /* USER CODE END set_Software_position_limit_Maximal_position_limit 0 */
    kProfile_position_mode.Software_position_limit_Maximal_position_limit = val;
    /* USER CODE BEGIN set_Software_position_limit_Maximal_position_limit 1 */
    set_app_Software_position_limit_Maximal_position_limit(val);
    /* USER CODE END set_Software_position_limit_Maximal_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Software_position_limit_Maximal_position_limit(void){
    /* USER CODE BEGIN get_Software_position_limit_Maximal_position_limit */
    kProfile_position_mode.Software_position_limit_Maximal_position_limit = limit_64_to_32(get_app_Software_position_limit_Maximal_position_limit());
    /* USER CODE END get_Software_position_limit_Maximal_position_limit */
    return kProfile_position_mode.Software_position_limit_Maximal_position_limit;
}

UNS32 set_Max_Profile_velocity(UNS32 val){
    /* USER CODE BEGIN set_Max_Profile_velocity 0 */
    /* USER CODE END set_Max_Profile_velocity 0 */
    kProfile_position_mode.Max_Profile_velocity = val;
    /* USER CODE BEGIN set_Max_Profile_velocity 1 */
    // P/s转RPM
    set_app_Max_Profile_velocity((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Max_Profile_velocity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Max_Profile_velocity(void){
    /* USER CODE BEGIN get_Max_Profile_velocity */
    kProfile_position_mode.Max_Profile_velocity = get_app_Max_Profile_velocity() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Max_Profile_velocity */
    return kProfile_position_mode.Max_Profile_velocity;
}

UNS32 set_Max_motor_speed(UNS32 val){
    /* USER CODE BEGIN set_Max_motor_speed 0 */
    /* USER CODE END set_Max_motor_speed 0 */
    kProfile_position_mode.Max_motor_speed = val;
    /* USER CODE BEGIN set_Max_motor_speed 1 */
    set_app_Max_motor_speed((float)val);
    /* USER CODE END set_Max_motor_speed 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Max_motor_speed(void){
    /* USER CODE BEGIN get_Max_motor_speed */
    kProfile_position_mode.Max_motor_speed = get_app_Max_motor_speed();
    /* USER CODE END get_Max_motor_speed */
    return kProfile_position_mode.Max_motor_speed;
}

UNS32 set_Profile_velocity(UNS32 val){
    /* USER CODE BEGIN set_Profile_velocity 0 */
    /* USER CODE END set_Profile_velocity 0 */
    kProfile_position_mode.Profile_velocity = val;
    /* USER CODE BEGIN set_Profile_velocity 1 */
    // P/s转RPM
    set_app_Profile_velocity((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Profile_velocity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Profile_velocity(void){
    /* USER CODE BEGIN get_Profile_velocity */
    kProfile_position_mode.Profile_velocity = get_app_Profile_velocity() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Profile_velocity */
    return kProfile_position_mode.Profile_velocity;
}

UNS32 set_Profile_acceleration(UNS32 val){
    /* USER CODE BEGIN set_Profile_acceleration 0 */
    /* USER CODE END set_Profile_acceleration 0 */
    kProfile_position_mode.Profile_acceleration = val;
    /* USER CODE BEGIN set_Profile_acceleration 1 */
    // P/s/s转RPM/s
    set_app_Profile_acceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Profile_acceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Profile_acceleration(void){
    /* USER CODE BEGIN get_Profile_acceleration */
    kProfile_position_mode.Profile_acceleration = get_app_Profile_acceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Profile_acceleration */
    return kProfile_position_mode.Profile_acceleration;
}

UNS32 set_Profile_deceleration(UNS32 val){
    /* USER CODE BEGIN set_Profile_deceleration 0 */
    /* USER CODE END set_Profile_deceleration 0 */
    kProfile_position_mode.Profile_deceleration = val;
    /* USER CODE BEGIN set_Profile_deceleration 1 */
    // P/s/s转RPM/s
    set_app_Profile_deceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Profile_deceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Profile_deceleration(void){
    /* USER CODE BEGIN get_Profile_deceleration */
    kProfile_position_mode.Profile_deceleration = get_app_Profile_deceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Profile_deceleration */
    return kProfile_position_mode.Profile_deceleration;
}

UNS32 set_Quick_stop_deceleration(UNS32 val){
    /* USER CODE BEGIN set_Quick_stop_deceleration 0 */
    /* USER CODE END set_Quick_stop_deceleration 0 */
    kProfile_position_mode.Quick_stop_deceleration = val;
    /* USER CODE BEGIN set_Quick_stop_deceleration 1 */
    // P/s/s转RPM/s
    set_app_Quick_stop_deceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Quick_stop_deceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Quick_stop_deceleration(void){
    /* USER CODE BEGIN get_Quick_stop_deceleration */
    kProfile_position_mode.Quick_stop_deceleration = get_app_Quick_stop_deceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Quick_stop_deceleration */
    return kProfile_position_mode.Quick_stop_deceleration;
}

UNS32 set_Max_acceleration(UNS32 val){
    /* USER CODE BEGIN set_Max_acceleration 0 */
    /* USER CODE END set_Max_acceleration 0 */
    kProfile_position_mode.Max_acceleration = val;
    /* USER CODE BEGIN set_Max_acceleration 1 */
    // P/s/s转RPM/s
    set_app_Max_acceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Max_acceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Max_acceleration(void){
    /* USER CODE BEGIN get_Max_acceleration */
    kProfile_position_mode.Max_acceleration = get_app_Max_acceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Max_acceleration */
    return kProfile_position_mode.Max_acceleration;
}

UNS32 set_Max_deceleration(UNS32 val){
    /* USER CODE BEGIN set_Max_deceleration 0 */
    /* USER CODE END set_Max_deceleration 0 */
    kProfile_position_mode.Max_deceleration = val;
    /* USER CODE BEGIN set_Max_deceleration 1 */
    // P/s/s转RPM/s
    set_app_Max_deceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Max_deceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Max_deceleration(void){
    /* USER CODE BEGIN get_Max_deceleration */
    kProfile_position_mode.Max_deceleration = get_app_Max_deceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Max_deceleration */
    return kProfile_position_mode.Max_deceleration;
}

UNS32 set_Homing_method(INTEGER8 val){
    /* USER CODE BEGIN set_Homing_method 0 */
    /* USER CODE END set_Homing_method 0 */
    kHoming_mode.Homing_method = val;
    /* USER CODE BEGIN set_Homing_method 1 */
    set_app_Homing_method(val);
    /* USER CODE END set_Homing_method 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER8 get_Homing_method(void){
    /* USER CODE BEGIN get_Homing_method */
    kHoming_mode.Homing_method = get_app_Homing_method();
    /* USER CODE END get_Homing_method */
    return kHoming_mode.Homing_method;
}

UNS32 set_Position_demand_value(INTEGER32 val){
    /* USER CODE BEGIN set_Position_demand_value 0 */
    /* USER CODE END set_Position_demand_value 0 */
    kPosition_control_function.Position_demand_value = val;
    /* USER CODE BEGIN set_Position_demand_value 1 */
    /* USER CODE END set_Position_demand_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_demand_value(void){
    /* USER CODE BEGIN get_Position_demand_value */
    kPosition_control_function.Position_demand_value = get_app_Position_demand_value();
    /* USER CODE END get_Position_demand_value */
    return kPosition_control_function.Position_demand_value;
}

UNS32 set_Position_actual_value_inc(INTEGER32 val){
    /* USER CODE BEGIN set_Position_actual_value_inc 0 */
    /* USER CODE END set_Position_actual_value_inc 0 */
    kPosition_control_function.Position_actual_value_inc = val;
    /* USER CODE BEGIN set_Position_actual_value_inc 1 */
    /* USER CODE END set_Position_actual_value_inc 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_actual_value_inc(void){
    /* USER CODE BEGIN get_Position_actual_value_inc */
    kPosition_control_function.Position_actual_value_inc = get_app_Position_actual_value_inc();
    /* USER CODE END get_Position_actual_value_inc */
    return kPosition_control_function.Position_actual_value_inc;
}

UNS32 set_Position_actual_value(INTEGER32 val){
    /* USER CODE BEGIN set_Position_actual_value 0 */
    /* USER CODE END set_Position_actual_value 0 */
    kPosition_control_function.Position_actual_value = val;
    /* USER CODE BEGIN set_Position_actual_value 1 */
    /* USER CODE END set_Position_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_actual_value(void){
    /* USER CODE BEGIN get_Position_actual_value */
    kPosition_control_function.Position_actual_value = get_app_Position_actual_value();
    /* USER CODE END get_Position_actual_value */
    return kPosition_control_function.Position_actual_value;
}

UNS32 set_Following_error_window(UNS32 val){
    /* USER CODE BEGIN set_Following_error_window 0 */
    set_app_Following_error_window(val);
    /* USER CODE END set_Following_error_window 0 */
    kPosition_control_function.Following_error_window = val;
    /* USER CODE BEGIN set_Following_error_window 1 */
    /* USER CODE END set_Following_error_window 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Following_error_window(void){
    /* USER CODE BEGIN get_Following_error_window */
    kPosition_control_function.Following_error_window = get_app_Following_error_window();
    /* USER CODE END get_Following_error_window */
    return kPosition_control_function.Following_error_window;
}

UNS32 set_Following_error_time_Out(UNS16 val){
    /* USER CODE BEGIN set_Following_error_time_Out 0 */
    set_app_Following_error_time_Out((float)val * 0.001f);
    /* USER CODE END set_Following_error_time_Out 0 */
    kPosition_control_function.Following_error_time_Out = val;
    /* USER CODE BEGIN set_Following_error_time_Out 1 */
    /* USER CODE END set_Following_error_time_Out 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Following_error_time_Out(void){
    /* USER CODE BEGIN get_Following_error_time_Out */
    kPosition_control_function.Following_error_time_Out = get_app_Following_error_time_Out() * 1000;
    /* USER CODE END get_Following_error_time_Out */
    return kPosition_control_function.Following_error_time_Out;
}

UNS32 set_Position_window(UNS32 val){
    /* USER CODE BEGIN set_Position_window 0 */
    set_app_Position_window(val);
    /* USER CODE END set_Position_window 0 */
    kPosition_control_function.Position_window = val;
    /* USER CODE BEGIN set_Position_window 1 */
    /* USER CODE END set_Position_window 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Position_window(void){
    /* USER CODE BEGIN get_Position_window */
    kPosition_control_function.Position_window = get_app_Position_window();
    /* USER CODE END get_Position_window */
    return kPosition_control_function.Position_window;
}

UNS32 set_Position_window_time(UNS16 val){
    /* USER CODE BEGIN set_Position_window_time 0 */
    set_app_Position_window_time((float)val * 0.001f);
    /* USER CODE END set_Position_window_time 0 */
    kPosition_control_function.Position_window_time = val;
    /* USER CODE BEGIN set_Position_window_time 1 */
    /* USER CODE END set_Position_window_time 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Position_window_time(void){
    /* USER CODE BEGIN get_Position_window_time */
    kPosition_control_function.Position_window_time = get_app_Position_window_time() * 1000;
    /* USER CODE END get_Position_window_time */
    return kPosition_control_function.Position_window_time;
}

UNS32 set_Following_error_actual_value(INTEGER32 val){
    /* USER CODE BEGIN set_Following_error_actual_value 0 */
    /* USER CODE END set_Following_error_actual_value 0 */
    kPosition_control_function.Following_error_actual_value = val;
    /* USER CODE BEGIN set_Following_error_actual_value 1 */
    /* USER CODE END set_Following_error_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Following_error_actual_value(void){
    /* USER CODE BEGIN get_Following_error_actual_value */
    kPosition_control_function.Following_error_actual_value = get_app_Following_error_actual_value();
    /* USER CODE END get_Following_error_actual_value */
    return kPosition_control_function.Following_error_actual_value;
}

UNS32 set_Velocity_demand_value(INTEGER32 val){
    /* USER CODE BEGIN set_Velocity_demand_value 0 */
    /* USER CODE END set_Velocity_demand_value 0 */
    kProfile_velocity_mode.Velocity_demand_value = val;
    /* USER CODE BEGIN set_Velocity_demand_value 1 */
    /* USER CODE END set_Velocity_demand_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Velocity_demand_value(void){
    /* USER CODE BEGIN get_Velocity_demand_value */
    // RPM 转 P/s
    kProfile_velocity_mode.Velocity_demand_value = get_app_Velocity_demand_value() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Velocity_demand_value */
    return kProfile_velocity_mode.Velocity_demand_value;
}

UNS32 set_Velocity_actual_value(INTEGER32 val){
    /* USER CODE BEGIN set_Velocity_actual_value 0 */
    /* USER CODE END set_Velocity_actual_value 0 */
    kProfile_velocity_mode.Velocity_actual_value = val;
    /* USER CODE BEGIN set_Velocity_actual_value 1 */
    /* USER CODE END set_Velocity_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Velocity_actual_value(void){
    /* USER CODE BEGIN get_Velocity_actual_value */
    // P/s 转 RPM
    kProfile_velocity_mode.Velocity_actual_value = get_app_Velocity_actual_value() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Velocity_actual_value */
    return kProfile_velocity_mode.Velocity_actual_value;
}

UNS32 set_Velocity_window(UNS16 val){
    /* USER CODE BEGIN set_Velocity_window 0 */
    // P/s转RPM
    set_app_Velocity_window((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Velocity_window 0 */
    kProfile_velocity_mode.Velocity_window = val;
    /* USER CODE BEGIN set_Velocity_window 1 */
    /* USER CODE END set_Velocity_window 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Velocity_window(void){
    /* USER CODE BEGIN get_Velocity_window */
    kProfile_velocity_mode.Velocity_window = get_app_Velocity_window() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Velocity_window */
    return kProfile_velocity_mode.Velocity_window;
}

UNS32 set_Velocity_window_time(UNS16 val){
    /* USER CODE BEGIN set_Velocity_window_time 0 */
    set_app_Velocity_window_time((float)val * 0.001f);
    /* USER CODE END set_Velocity_window_time 0 */
    kProfile_velocity_mode.Velocity_window_time = val;
    /* USER CODE BEGIN set_Velocity_window_time 1 */
    /* USER CODE END set_Velocity_window_time 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Velocity_window_time(void){
    /* USER CODE BEGIN get_Velocity_window_time */
    kProfile_velocity_mode.Velocity_window_time = get_app_Velocity_window_time() * 1000;
    /* USER CODE END get_Velocity_window_time */
    return kProfile_velocity_mode.Velocity_window_time;
}

UNS32 set_Velocity_threshold(UNS16 val){
    /* USER CODE BEGIN set_Velocity_threshold 0 */
    // P/s转RPM
    set_app_Velocity_threshold((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Velocity_threshold 0 */
    kProfile_velocity_mode.Velocity_threshold = val;
    /* USER CODE BEGIN set_Velocity_threshold 1 */
    /* USER CODE END set_Velocity_threshold 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Velocity_threshold(void){
    /* USER CODE BEGIN get_Velocity_threshold */
    kProfile_velocity_mode.Velocity_threshold = get_app_Velocity_threshold() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Velocity_threshold */
    return kProfile_velocity_mode.Velocity_threshold;
}

UNS32 set_Velocity_threshold_time(UNS16 val){
    /* USER CODE BEGIN set_Velocity_threshold_time 0 */
    set_app_Velocity_threshold_time((float)val * 0.001f);
    /* USER CODE END set_Velocity_threshold_time 0 */
    kProfile_velocity_mode.Velocity_threshold_time = val;
    /* USER CODE BEGIN set_Velocity_threshold_time 1 */
    /* USER CODE END set_Velocity_threshold_time 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Velocity_threshold_time(void){
    /* USER CODE BEGIN get_Velocity_threshold_time */
    kProfile_velocity_mode.Velocity_threshold_time = get_app_Velocity_threshold_time() * 1000;
    /* USER CODE END get_Velocity_threshold_time */
    return kProfile_velocity_mode.Velocity_threshold_time;
}

UNS32 set_Target_velocity(INTEGER32 val){
    /* USER CODE BEGIN set_Target_velocity 0 */
    /* USER CODE END set_Target_velocity 0 */
    kProfile_velocity_mode.Target_velocity = val;
    /* USER CODE BEGIN set_Target_velocity 1 */
    // P/s 转 RPM
    set_app_Target_velocity((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Target_velocity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Target_velocity(void){
    /* USER CODE BEGIN get_Target_velocity */
    // RPM 转 P/s
    kProfile_velocity_mode.Target_velocity = get_app_Target_velocity() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Target_velocity */
    return kProfile_velocity_mode.Target_velocity;
}

UNS32 set_Target_torque(INTEGER16 val){
    /* USER CODE BEGIN set_Target_torque 0 */
    /* USER CODE END set_Target_torque 0 */
    kProfile_torque_mode.Target_torque = val;
    /* USER CODE BEGIN set_Target_torque 1 */
    // 额定电流千分比转实际电流
    set_app_Target_torque((float)val * get_app_Motor_rated_current() * kArms2Apeak * 0.001f);
    /* USER CODE END set_Target_torque 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Target_torque(void){
    /* USER CODE BEGIN get_Target_torque */
    kProfile_torque_mode.Target_torque = get_app_Target_torque() * 1000 / (get_app_Motor_rated_current() * kArms2Apeak);
    /* USER CODE END get_Target_torque */
    return kProfile_torque_mode.Target_torque;
}

UNS32 set_Max_torque(UNS16 val){
    /* USER CODE BEGIN set_Max_torque 0 */
    /* USER CODE END set_Max_torque 0 */
    kProfile_torque_mode.Max_torque = val;
    /* USER CODE BEGIN set_Max_torque 1 */
    // 额定电流千分比转实际电流
    set_app_Max_current((float)val * get_app_Motor_rated_current() * kArms2Apeak * 0.001f);
    /* USER CODE END set_Max_torque 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Max_torque(void){
    /* USER CODE BEGIN get_Max_torque */
    kProfile_torque_mode.Max_torque = get_app_Max_current() * 1000 / (get_app_Motor_rated_current() * kArms2Apeak);
    /* USER CODE END get_Max_torque */
    return kProfile_torque_mode.Max_torque;
}

UNS32 set_Max_current(UNS16 val){
    /* USER CODE BEGIN set_Max_current 0 */
    /* USER CODE END set_Max_current 0 */
    kProfile_torque_mode.Max_current = val;
    /* USER CODE BEGIN set_Max_current 1 */
    set_app_Max_current((float)val * get_app_Motor_rated_current() * kArms2Apeak * 0.001f);
    /* USER CODE END set_Max_current 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Max_current(void){
    /* USER CODE BEGIN get_Max_current */
    kProfile_torque_mode.Max_current = get_app_Max_current() * 1000 / (get_app_Motor_rated_current() * kArms2Apeak);
    /* USER CODE END get_Max_current */
    return kProfile_torque_mode.Max_current;
}

UNS32 set_Torque_demand_value(INTEGER16 val){
    /* USER CODE BEGIN set_Torque_demand_value 0 */
    /* USER CODE END set_Torque_demand_value 0 */
    kProfile_torque_mode.Torque_demand_value = val;
    /* USER CODE BEGIN set_Torque_demand_value 1 */
    /* USER CODE END set_Torque_demand_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Torque_demand_value(void){
    /* USER CODE BEGIN get_Torque_demand_value */
    kProfile_torque_mode.Torque_demand_value = get_app_Torque_demand_value();
    /* USER CODE END get_Torque_demand_value */
    return kProfile_torque_mode.Torque_demand_value;
}

UNS32 set_Motor_rated_current(UNS32 val){
    /* USER CODE BEGIN set_Motor_rated_current 0 */
    /* USER CODE END set_Motor_rated_current 0 */
    kProfile_torque_mode.Motor_rated_current = val;
    /* USER CODE BEGIN set_Motor_rated_current 1 */
    set_app_Motor_rated_current((float)val * 0.001f);
    /* USER CODE END set_Motor_rated_current 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Motor_rated_current(void){
    /* USER CODE BEGIN get_Motor_rated_current */
    kProfile_torque_mode.Motor_rated_current = get_app_Motor_rated_current() * 1000;
    /* USER CODE END get_Motor_rated_current */
    return kProfile_torque_mode.Motor_rated_current;
}

UNS32 set_Motor_rated_torque(UNS32 val){
    /* USER CODE BEGIN set_Motor_rated_torque 0 */
    /* USER CODE END set_Motor_rated_torque 0 */
    kProfile_torque_mode.Motor_rated_torque = val;
    /* USER CODE BEGIN set_Motor_rated_torque 1 */
    // mNm 转 Nm
    set_app_Motor_rated_torque((float)val * 0.001f);
    /* USER CODE END set_Motor_rated_torque 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Motor_rated_torque(void){
    /* USER CODE BEGIN get_Motor_rated_torque */
    kProfile_torque_mode.Motor_rated_torque = get_app_Motor_rated_torque() * 1000;
    /* USER CODE END get_Motor_rated_torque */
    return kProfile_torque_mode.Motor_rated_torque;
}

UNS32 set_Torque_actual_value(INTEGER16 val){
    /* USER CODE BEGIN set_Torque_actual_value 0 */
    /* USER CODE END set_Torque_actual_value 0 */
    kProfile_torque_mode.Torque_actual_value = val;
    /* USER CODE BEGIN set_Torque_actual_value 1 */
    /* USER CODE END set_Torque_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Torque_actual_value(void){
    /* USER CODE BEGIN get_Torque_actual_value */
    // 实际力矩转为额定力矩千分比
    kProfile_torque_mode.Torque_actual_value = get_app_Current_actual_value() * 1000 \
                                                / (get_app_Motor_rated_current() * kArms2Apeak);
    /* USER CODE END get_Torque_actual_value */
    return kProfile_torque_mode.Torque_actual_value;
}

UNS32 set_Current_actual_value(INTEGER16 val){
    /* USER CODE BEGIN set_Current_actual_value 0 */
    /* USER CODE END set_Current_actual_value 0 */
    kProfile_torque_mode.Current_actual_value = val;
    /* USER CODE BEGIN set_Current_actual_value 1 */
    /* USER CODE END set_Current_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Current_actual_value(void){
    /* USER CODE BEGIN get_Current_actual_value */
    kProfile_torque_mode.Current_actual_value = get_app_Current_actual_value() * 1000 \
                                                / (get_app_Motor_rated_current() * kArms2Apeak);
    /* USER CODE END get_Current_actual_value */
    return kProfile_torque_mode.Current_actual_value;
}

UNS32 set_DC_link_circuit_voltage(UNS32 val){
    /* USER CODE BEGIN set_DC_link_circuit_voltage 0 */
    /* USER CODE END set_DC_link_circuit_voltage 0 */
    kProfile_torque_mode.DC_link_circuit_voltage = val;
    /* USER CODE BEGIN set_DC_link_circuit_voltage 1 */
    /* USER CODE END set_DC_link_circuit_voltage 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_DC_link_circuit_voltage(void){
    /* USER CODE BEGIN get_DC_link_circuit_voltage */
    kProfile_torque_mode.DC_link_circuit_voltage = get_app_DC_link_circuit_voltage() * 1000;
    /* USER CODE END get_DC_link_circuit_voltage */
    return kProfile_torque_mode.DC_link_circuit_voltage;
}

UNS32 set_Torque_slope(UNS32 val){
    /* USER CODE BEGIN set_Torque_slope 0 */
    /* USER CODE END set_Torque_slope 0 */
    kProfile_torque_mode.Torque_slope = val;
    /* USER CODE BEGIN set_Torque_slope 1 */
    // 千分比转电流
    set_app_Torque_slope((float)val * get_app_Motor_rated_current() * kArms2Apeak * 0.001f);
    /* USER CODE END set_Torque_slope 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Torque_slope(void){
    /* USER CODE BEGIN get_Torque_slope */
    kProfile_torque_mode.Torque_slope = get_app_Torque_slope() * 1000 / (get_app_Motor_rated_current() * kArms2Apeak);
    /* USER CODE END get_Torque_slope */
    return kProfile_torque_mode.Torque_slope;
}

UNS32 set_Alarm_word(UNS32 val){
    /* USER CODE BEGIN set_Alarm_word 0 */
    /* USER CODE END set_Alarm_word 0 */
    kManufacturer.Alarm_word = val;
    /* USER CODE BEGIN set_Alarm_word 1 */
    /* USER CODE END set_Alarm_word 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Alarm_word(void){
    /* USER CODE BEGIN get_Alarm_word */
    /* USER CODE END get_Alarm_word */
    return kManufacturer.Alarm_word;
}

UNS32 set_MIT_feedforward_torque_current(INTEGER32 val){
    /* USER CODE BEGIN set_MIT_feedforward_torque_current 0 */
    /* USER CODE END set_MIT_feedforward_torque_current 0 */
    kManufacturer.MIT_feedforward_torque_current = val;
    /* USER CODE BEGIN set_MIT_feedforward_torque_current 1 */
    set_app_MIT_feedforward_torque_current((float)kManufacturer.MIT_feedforward_torque_current * 0.001);
    /* USER CODE END set_MIT_feedforward_torque_current 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_MIT_feedforward_torque_current(void){
    /* USER CODE BEGIN get_MIT_feedforward_torque_current */
    kManufacturer.MIT_feedforward_torque_current = get_app_MIT_feedforward_torque_current() * 1000.0f;
    /* USER CODE END get_MIT_feedforward_torque_current */
    return kManufacturer.MIT_feedforward_torque_current;
}

UNS32 set_MIT_target_position(INTEGER32 val){
    /* USER CODE BEGIN set_MIT_target_position 0 */
    /* USER CODE END set_MIT_target_position 0 */
    kManufacturer.MIT_target_position = val;
    /* USER CODE BEGIN set_MIT_target_position 1 */
    set_app_MIT_target_position(val);
    /* USER CODE END set_MIT_target_position 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_MIT_target_position(void){
    /* USER CODE BEGIN get_MIT_target_position */
    kManufacturer.MIT_target_position = get_app_MIT_target_position();
    /* USER CODE END get_MIT_target_position */
    return kManufacturer.MIT_target_position;
}

UNS32 set_MIT_max_current(INTEGER32 val){
    /* USER CODE BEGIN set_MIT_max_current 0 */
    /* USER CODE END set_MIT_max_current 0 */
    kManufacturer.MIT_max_current = val;
    /* USER CODE BEGIN set_MIT_max_current 1 */
    set_app_MIT_max_current((float)kManufacturer.MIT_max_current * 0.001);
    /* USER CODE END set_MIT_max_current 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_MIT_max_current(void){
    /* USER CODE BEGIN get_MIT_max_current */
    kManufacturer.MIT_max_current = get_app_MIT_max_current() * 1000.0f;
    /* USER CODE END get_MIT_max_current */
    return kManufacturer.MIT_max_current;
}

UNS32 set_MIT_target_velocity(INTEGER32 val){
    /* USER CODE BEGIN set_MIT_target_velocity 0 */
    /* USER CODE END set_MIT_target_velocity 0 */
    kManufacturer.MIT_target_velocity = val;
    /* USER CODE BEGIN set_MIT_target_velocity 1 */
    set_app_MIT_target_velocity((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_MIT_target_velocity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_MIT_target_velocity(void){
    /* USER CODE BEGIN get_MIT_target_velocity */
    kManufacturer.MIT_target_velocity = get_app_MIT_target_velocity() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_MIT_target_velocity */
    return kManufacturer.MIT_target_velocity;
}

UNS32 set_MIT_Kp(UNS32 val){
    /* USER CODE BEGIN set_MIT_Kp 0 */
    /* USER CODE END set_MIT_Kp 0 */
    kManufacturer.MIT_Kp = val;
    /* USER CODE BEGIN set_MIT_Kp 1 */
    //单位0.001 A/rad
    set_app_MIT_Kp((float)val * 0.001f);
    /* USER CODE END set_MIT_Kp 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_MIT_Kp(void){
    /* USER CODE BEGIN get_MIT_Kp */
    kManufacturer.MIT_Kp = get_app_MIT_Kp() * 1000.0f;
    /* USER CODE END get_MIT_Kp */
    return kManufacturer.MIT_Kp;
}

UNS32 set_MIT_Kd(UNS32 val){
    /* USER CODE BEGIN set_MIT_Kd 0 */
    /* USER CODE END set_MIT_Kd 0 */
    kManufacturer.MIT_Kd = val;
    /* USER CODE BEGIN set_MIT_Kd 1 */
    //单位0.001 A/(rad/s)
    set_app_MIT_Kd((float)val * 0.001f);
    /* USER CODE END set_MIT_Kd 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_MIT_Kd(void){
    /* USER CODE BEGIN get_MIT_Kd */
    kManufacturer.MIT_Kd = get_app_MIT_Kd() * 1000.0f;
    /* USER CODE END get_MIT_Kd */
    return kManufacturer.MIT_Kd;
}

UNS32 set_SysCmd(UNS8 val){
    /* USER CODE BEGIN set_SysCmd 0 */
    /* USER CODE END set_SysCmd 0 */
    kManufacturer.SysCmd = val;
    /* USER CODE BEGIN set_SysCmd 1 */
    set_app_SysCmd(val);
    /* USER CODE END set_SysCmd 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_SysCmd(void){
    /* USER CODE BEGIN get_SysCmd */
    kManufacturer.SysCmd = get_app_SysCmd();
    /* USER CODE END get_SysCmd */
    return kManufacturer.SysCmd;
}

UNS32 set_storage_status(INTEGER8 val){
    /* USER CODE BEGIN set_storage_status 0 */
    /* USER CODE END set_storage_status 0 */
    kManufacturer.storage_status = val;
    /* USER CODE BEGIN set_storage_status 1 */
    set_app_storage_status(val);
    /* USER CODE END set_storage_status 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER8 get_storage_status(void){
    /* USER CODE BEGIN get_storage_status */
    kManufacturer.storage_status = get_app_storage_status();
    /* USER CODE END get_storage_status */
    return kManufacturer.storage_status;
}

UNS32 set_Notch_filter_frq(uint8_t subindex, UNS16 val){
    /* USER CODE BEGIN set_Notch_filter_frq 0 */
    /* USER CODE END set_Notch_filter_frq 0 */
    kManufacturer.Notch_filter_frq[subindex] = val;
    /* USER CODE BEGIN set_Notch_filter_frq 1 */
    //单位：0.1hz
    kAxis1.notch_filter_config.frq[subindex] = (float)val * 0.1f;
    /* USER CODE END set_Notch_filter_frq 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Notch_filter_frq(uint8_t subindex){
    /* USER CODE BEGIN get_Notch_filter_frq */
    kManufacturer.Notch_filter_frq[subindex] = kAxis1.notch_filter_config.frq[subindex] * 10.0f;
    /* USER CODE END get_Notch_filter_frq */
    return kManufacturer.Notch_filter_frq[subindex];
}

UNS32 set_Notch_filter_width(uint8_t subindex, UNS16 val){
    /* USER CODE BEGIN set_Notch_filter_width 0 */
    /* USER CODE END set_Notch_filter_width 0 */
    kManufacturer.Notch_filter_width[subindex] = val;
    /* USER CODE BEGIN set_Notch_filter_width 1 */
    //单位0.1hz
    kAxis1.notch_filter_config.width[subindex] = (float)val * 0.1f;
    /* USER CODE END set_Notch_filter_width 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Notch_filter_width(uint8_t subindex){
    /* USER CODE BEGIN get_Notch_filter_width */
    kManufacturer.Notch_filter_width[subindex] = kAxis1.notch_filter_config.width[subindex] * 10.0f;
    /* USER CODE END get_Notch_filter_width */
    return kManufacturer.Notch_filter_width[subindex];
}

UNS32 set_Notch_filter_depth(uint8_t subindex, UNS16 val){
    /* USER CODE BEGIN set_Notch_filter_depth 0 */
    /* USER CODE END set_Notch_filter_depth 0 */
    kManufacturer.Notch_filter_depth[subindex] = val;
    /* USER CODE BEGIN set_Notch_filter_depth 1 */
    //单位：0.1db
    kAxis1.notch_filter_config.depth[subindex] = (float)val * 0.1f;
    /* USER CODE END set_Notch_filter_depth 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Notch_filter_depth(uint8_t subindex){
    /* USER CODE BEGIN get_Notch_filter_depth */
    kManufacturer.Notch_filter_depth[subindex] = kAxis1.notch_filter_config.depth[subindex] * 10.0f;
    /* USER CODE END get_Notch_filter_depth */
    return kManufacturer.Notch_filter_depth[subindex];
}

UNS32 set_Input_shaping_wn(UNS16 val){
    /* USER CODE BEGIN set_Input_shaping_wn 0 */
    /* USER CODE END set_Input_shaping_wn 0 */
    kManufacturer.Input_shaping_wn = val;
    /* USER CODE BEGIN set_Input_shaping_wn 1 */
    //单位：0.1HZ
    kAxis1.input_shaping_config.wn_Hz = (float)val * 0.1f;
    /* USER CODE END set_Input_shaping_wn 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Input_shaping_wn(void){
    /* USER CODE BEGIN get_Input_shaping_wn */
    kManufacturer.Input_shaping_wn = kAxis1.input_shaping_config.wn_Hz * 10.0f;
    /* USER CODE END get_Input_shaping_wn */
    return kManufacturer.Input_shaping_wn;
}

UNS32 set_Pos_speed_ctl_aff(UNS16 val){
    /* USER CODE BEGIN set_Pos_speed_ctl_aff 0 */
    /* USER CODE END set_Pos_speed_ctl_aff 0 */
    kManufacturer.Pos_speed_ctl_aff = val;
    /* USER CODE BEGIN set_Pos_speed_ctl_aff 1 */
    //单位：0.1%
    kAxis1.pos_speed_ctl_config.aff = (float)val * 0.001f;
    /* USER CODE END set_Pos_speed_ctl_aff 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Pos_speed_ctl_aff(void){
    /* USER CODE BEGIN get_Pos_speed_ctl_aff */
    kManufacturer.Pos_speed_ctl_aff = kAxis1.pos_speed_ctl_config.aff * 1000.0f;
    /* USER CODE END get_Pos_speed_ctl_aff */
    return kManufacturer.Pos_speed_ctl_aff;
}

UNS32 set_Pos_speed_ctl_vff(UNS16 val){
    /* USER CODE BEGIN set_Pos_speed_ctl_vff 0 */
    /* USER CODE END set_Pos_speed_ctl_vff 0 */
    kManufacturer.Pos_speed_ctl_vff = val;
    /* USER CODE BEGIN set_Pos_speed_ctl_vff 1 */
    //单位:0.1%
    kAxis1.pos_speed_ctl_config.vff = (float)val * 0.001f;
    /* USER CODE END set_Pos_speed_ctl_vff 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Pos_speed_ctl_vff(void){
    /* USER CODE BEGIN get_Pos_speed_ctl_vff */
    kManufacturer.Pos_speed_ctl_vff = kAxis1.pos_speed_ctl_config.vff * 1000.0f;
    /* USER CODE END get_Pos_speed_ctl_vff */
    return kManufacturer.Pos_speed_ctl_vff;
}

UNS32 set_Pos_speed_ctl_j_kt(UNS32 val){
    /* USER CODE BEGIN set_Pos_speed_ctl_j_kt 0 */
    /* USER CODE END set_Pos_speed_ctl_j_kt 0 */
    kManufacturer.Pos_speed_ctl_j_kt = val;
    /* USER CODE BEGIN set_Pos_speed_ctl_j_kt 1 */
    //单位：0.00001 kg*m^2/(N*m/A)
    kAxis1.pos_speed_ctl_config.j_kt = (float)val * 0.00001f;
    /* USER CODE END set_Pos_speed_ctl_j_kt 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Pos_speed_ctl_j_kt(void){
    /* USER CODE BEGIN get_Pos_speed_ctl_j_kt */
    kManufacturer.Pos_speed_ctl_j_kt = kAxis1.pos_speed_ctl_config.j_kt * 100000.0f;
    /* USER CODE END get_Pos_speed_ctl_j_kt */
    return kManufacturer.Pos_speed_ctl_j_kt;
}

UNS32 set_Pos_speed_ctl_ki_s(UNS32 val){
    /* USER CODE BEGIN set_Pos_speed_ctl_ki_s 0 */
    /* USER CODE END set_Pos_speed_ctl_ki_s 0 */
    kManufacturer.Pos_speed_ctl_ki_s = val;
    /* USER CODE BEGIN set_Pos_speed_ctl_ki_s 1 */
    //单位0.001 A/rad
    kAxis1.pos_speed_ctl_config.ki_s = (float)val * 0.001f;
    /* USER CODE END set_Pos_speed_ctl_ki_s 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Pos_speed_ctl_ki_s(void){
    /* USER CODE BEGIN get_Pos_speed_ctl_ki_s */
    kManufacturer.Pos_speed_ctl_ki_s = kAxis1.pos_speed_ctl_config.ki_s * 1000.0f;
    /* USER CODE END get_Pos_speed_ctl_ki_s */
    return kManufacturer.Pos_speed_ctl_ki_s;
}

UNS32 set_Pos_speed_ctl_kp_p(UNS16 val){
    /* USER CODE BEGIN set_Pos_speed_ctl_kp_p 0 */
    /* USER CODE END set_Pos_speed_ctl_kp_p 0 */
    kManufacturer.Pos_speed_ctl_kp_p = val;
    /* USER CODE BEGIN set_Pos_speed_ctl_kp_p 1 */
    //单位：0.1hz
    kAxis1.pos_speed_ctl_config.kp_p = (float)val * 0.1f;
    /* USER CODE END set_Pos_speed_ctl_kp_p 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Pos_speed_ctl_kp_p(void){
    /* USER CODE BEGIN get_Pos_speed_ctl_kp_p */
    kManufacturer.Pos_speed_ctl_kp_p = kAxis1.pos_speed_ctl_config.kp_p * 10.0f;
    /* USER CODE END get_Pos_speed_ctl_kp_p */
    return kManufacturer.Pos_speed_ctl_kp_p;
}

UNS32 set_Pos_speed_ctl_kp_s(UNS32 val){
    /* USER CODE BEGIN set_Pos_speed_ctl_kp_s 0 */
    /* USER CODE END set_Pos_speed_ctl_kp_s 0 */
    kManufacturer.Pos_speed_ctl_kp_s = val;
    /* USER CODE BEGIN set_Pos_speed_ctl_kp_s 1 */
    //单位：0.001 A/(rad/s)
    kAxis1.pos_speed_ctl_config.kp_s = (float)val * 0.001f;
    /* USER CODE END set_Pos_speed_ctl_kp_s 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Pos_speed_ctl_kp_s(void){
    /* USER CODE BEGIN get_Pos_speed_ctl_kp_s */
    kManufacturer.Pos_speed_ctl_kp_s = kAxis1.pos_speed_ctl_config.kp_s * 1000.0f;
    /* USER CODE END get_Pos_speed_ctl_kp_s */
    return kManufacturer.Pos_speed_ctl_kp_s;
}

UNS32 set_Pos_speed_ctl_dob_wn(UNS16 val){
    /* USER CODE BEGIN set_Pos_speed_ctl_dob_wn 0 */
    /* USER CODE END set_Pos_speed_ctl_dob_wn 0 */
    kManufacturer.Pos_speed_ctl_dob_wn = val;
    /* USER CODE BEGIN set_Pos_speed_ctl_dob_wn 1 */
    //单位：0.1hz
    kAxis1.pos_speed_ctl_config.dob_wn_Hz =  (float)val * 0.1f;
    /* USER CODE END set_Pos_speed_ctl_dob_wn 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Pos_speed_ctl_dob_wn(void){
    /* USER CODE BEGIN get_Pos_speed_ctl_dob_wn */
    kManufacturer.Pos_speed_ctl_dob_wn = kAxis1.pos_speed_ctl_config.dob_wn_Hz * 10.0f;
    /* USER CODE END get_Pos_speed_ctl_dob_wn */
    return kManufacturer.Pos_speed_ctl_dob_wn;
}

UNS32 set_Pos_speed_ctl_dob_enable(UNS8 val){
    /* USER CODE BEGIN set_Pos_speed_ctl_dob_enable 0 */
    /* USER CODE END set_Pos_speed_ctl_dob_enable 0 */
    kManufacturer.Pos_speed_ctl_dob_enable = val;
    /* USER CODE BEGIN set_Pos_speed_ctl_dob_enable 1 */
    kAxis1.pos_speed_ctl_config.dob_enable = val;
    /* USER CODE END set_Pos_speed_ctl_dob_enable 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Pos_speed_ctl_dob_enable(void){
    /* USER CODE BEGIN get_Pos_speed_ctl_dob_enable */
    kManufacturer.Pos_speed_ctl_dob_enable = kAxis1.pos_speed_ctl_config.dob_enable;
    /* USER CODE END get_Pos_speed_ctl_dob_enable */
    return kManufacturer.Pos_speed_ctl_dob_enable;
}

UNS32 set_Current_ctl_i_noise(UNS16 val){
    /* USER CODE BEGIN set_Current_ctl_i_noise 0 */
    /* USER CODE END set_Current_ctl_i_noise 0 */
    kManufacturer.Current_ctl_i_noise = val;
    /* USER CODE BEGIN set_Current_ctl_i_noise 1 */
    //单位:0.001A
    kAxis1.current_ctl_config.i_noise_A = (float)val * 0.001f;
    /* USER CODE END set_Current_ctl_i_noise 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Current_ctl_i_noise(void){
    /* USER CODE BEGIN get_Current_ctl_i_noise */
    kManufacturer.Current_ctl_i_noise = kAxis1.current_ctl_config.i_noise_A * 1000.0f;
    /* USER CODE END get_Current_ctl_i_noise */
    return kManufacturer.Current_ctl_i_noise;
}

UNS32 set_Current_ctl_comp_du(UNS16 val){
    /* USER CODE BEGIN set_Current_ctl_comp_du 0 */
    /* USER CODE END set_Current_ctl_comp_du 0 */
    kManufacturer.Current_ctl_comp_du = val;
    /* USER CODE BEGIN set_Current_ctl_comp_du 1 */
    //单位:0.001V
    kAxis1.current_ctl_config.comp_du_V = (float)val * 0.001f;
    /* USER CODE END set_Current_ctl_comp_du 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Current_ctl_comp_du(void){
    /* USER CODE BEGIN get_Current_ctl_comp_du */
    kManufacturer.Current_ctl_comp_du = kAxis1.current_ctl_config.comp_du_V * 1000.0f;
    /* USER CODE END get_Current_ctl_comp_du */
    return kManufacturer.Current_ctl_comp_du;
}

UNS32 set_Current_ctl_bandwidth_percentage(UNS16 val){
    /* USER CODE BEGIN set_Current_ctl_bandwidth_percentage 0 */
    /* USER CODE END set_Current_ctl_bandwidth_percentage 0 */
    kManufacturer.Current_ctl_bandwidth_percentage = val;
    /* USER CODE BEGIN set_Current_ctl_bandwidth_percentage 1 */
    //单位：0.1 %
    kAxis1.current_ctl_config.bandwidth_percentage = (float)val * 0.1f;
    /* USER CODE END set_Current_ctl_bandwidth_percentage 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Current_ctl_bandwidth_percentage(void){
    /* USER CODE BEGIN get_Current_ctl_bandwidth_percentage */
    kManufacturer.Current_ctl_bandwidth_percentage = kAxis1.current_ctl_config.bandwidth_percentage * 10.0f;
    /* USER CODE END get_Current_ctl_bandwidth_percentage */
    return kManufacturer.Current_ctl_bandwidth_percentage;
}

UNS32 set_Current_ctl_kp_ld(UNS16 val){
    /* USER CODE BEGIN set_Current_ctl_kp_ld 0 */
    /* USER CODE END set_Current_ctl_kp_ld 0 */
    kManufacturer.Current_ctl_kp_ld = val;
    /* USER CODE BEGIN set_Current_ctl_kp_ld 1 */
    //kp_ld单位:0.01 V/A
    kAxis1.current_ctl_config.kp_ld = (float)val * 0.01f;
    /* USER CODE END set_Current_ctl_kp_ld 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Current_ctl_kp_ld(void){
    /* USER CODE BEGIN get_Current_ctl_kp_ld */
    kManufacturer.Current_ctl_kp_ld = kAxis1.current_ctl_config.kp_ld * 100.0f;
    /* USER CODE END get_Current_ctl_kp_ld */
    return kManufacturer.Current_ctl_kp_ld;
}

UNS32 set_Current_ctl_ki_ld(UNS16 val){
    /* USER CODE BEGIN set_Current_ctl_ki_ld 0 */
    /* USER CODE END set_Current_ctl_ki_ld 0 */
    kManufacturer.Current_ctl_ki_ld = val;
    /* USER CODE BEGIN set_Current_ctl_ki_ld 1 */
    //ki_ld单位:0.01 V/(A*s)
    kAxis1.current_ctl_config.ki_ld = (float)val * 0.01f;
    /* USER CODE END set_Current_ctl_ki_ld 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Current_ctl_ki_ld(void){
    /* USER CODE BEGIN get_Current_ctl_ki_ld */
    kManufacturer.Current_ctl_ki_ld = kAxis1.current_ctl_config.ki_ld * 100.0f;
    /* USER CODE END get_Current_ctl_ki_ld */
    return kManufacturer.Current_ctl_ki_ld;
}

UNS32 set_Current_ctl_kp_lq(UNS16 val){
    /* USER CODE BEGIN set_Current_ctl_kp_lq 0 */
    /* USER CODE END set_Current_ctl_kp_lq 0 */
    kManufacturer.Current_ctl_kp_lq = val;
    /* USER CODE BEGIN set_Current_ctl_kp_lq 1 */
    //kp_lq单位:0.01 V/A
    kAxis1.current_ctl_config.kp_lq = (float)val * 0.01f;
    /* USER CODE END set_Current_ctl_kp_lq 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Current_ctl_kp_lq(void){
    /* USER CODE BEGIN get_Current_ctl_kp_lq */
    kManufacturer.Current_ctl_kp_lq = kAxis1.current_ctl_config.kp_lq * 100.0f;
    /* USER CODE END get_Current_ctl_kp_lq */
    return kManufacturer.Current_ctl_kp_lq;
}

UNS32 set_Current_ctl_ki_lq(UNS16 val){
    /* USER CODE BEGIN set_Current_ctl_ki_lq 0 */
    /* USER CODE END set_Current_ctl_ki_lq 0 */
    kManufacturer.Current_ctl_ki_lq = val;
    /* USER CODE BEGIN set_Current_ctl_ki_lq 1 */
    //ki_ld单位:0.01 V/(A*s)
    kAxis1.current_ctl_config.ki_ld = (float)val * 0.01f;
    /* USER CODE END set_Current_ctl_ki_lq 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Current_ctl_ki_lq(void){
    /* USER CODE BEGIN get_Current_ctl_ki_lq */
    kManufacturer.Current_ctl_ki_lq = kAxis1.current_ctl_config.ki_ld * 100.0f;
    /* USER CODE END get_Current_ctl_ki_lq */
    return kManufacturer.Current_ctl_ki_lq;
}

UNS32 set_Speed_obs_pll_wn(UNS16 val){
    /* USER CODE BEGIN set_Speed_obs_pll_wn 0 */
    /* USER CODE END set_Speed_obs_pll_wn 0 */
    kManufacturer.Speed_obs_pll_wn = val;
    /* USER CODE BEGIN set_Speed_obs_pll_wn 1 */
    //速度观测器带宽:单位0.1hz
    kAxis1.speed_obs_pll_config.wn_Hz = (float)val * 0.1f;
    /* USER CODE END set_Speed_obs_pll_wn 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Speed_obs_pll_wn(void){
    /* USER CODE BEGIN get_Speed_obs_pll_wn */
    kManufacturer.Speed_obs_pll_wn = kAxis1.speed_obs_pll_config.wn_Hz * 10.0f;
    /* USER CODE END get_Speed_obs_pll_wn */
    return kManufacturer.Speed_obs_pll_wn;
}

