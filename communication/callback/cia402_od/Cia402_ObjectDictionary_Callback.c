#include "Cia402_ObjectDictionary_Callback.h"

#define STATUS_WORD_ENABLE_MASK (0x0027)

UNS32 OD_0x6040_Controlword_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6040 0x00 WRITE 0 */
    
    /* USER CODE END 0x6040 0x00 WRITE 0 */
    abort_code = set_Controlword(*(UNS16*)value);
    /* USER CODE BEGIN 0x6040 0x00 WRITE 1 */
    
    /* USER CODE END 0x6040 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6040_Controlword_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6040 0x00 READ 0 */
    
    /* USER CODE END 0x6040 0x00 READ 0 */
    *(UNS16*)value = get_Controlword();
    /* USER CODE BEGIN 0x6040 0x00 READ 1 */
    
    /* USER CODE END 0x6040 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6041_Statusword_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6041 0x00 READ 0 */
    
    /* USER CODE END 0x6041 0x00 READ 0 */
    *(UNS16*)value = get_Statusword();
    /* USER CODE BEGIN 0x6041 0x00 READ 1 */
    
    /* USER CODE END 0x6041 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x603F_Error_code_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x603F 0x00 READ 0 */
    
    /* USER CODE END 0x603F 0x00 READ 0 */
    *(UNS16*)value = get_Error_code();
    /* USER CODE BEGIN 0x603F 0x00 READ 1 */
    
    /* USER CODE END 0x603F 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x605A_Quick_stop_option_code_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x605A 0x00 WRITE 0 */
    
    /* USER CODE END 0x605A 0x00 WRITE 0 */
    abort_code = set_Quick_stop_option_code(*(INTEGER16*)value);
    /* USER CODE BEGIN 0x605A 0x00 WRITE 1 */
    
    /* USER CODE END 0x605A 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x605A_Quick_stop_option_code_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x605A 0x00 READ 0 */
    
    /* USER CODE END 0x605A 0x00 READ 0 */
    *(INTEGER16*)value = get_Quick_stop_option_code();
    /* USER CODE BEGIN 0x605A 0x00 READ 1 */
    
    /* USER CODE END 0x605A 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6060_Modes_of_operation_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6060 0x00 WRITE 0 */
    
    /* USER CODE END 0x6060 0x00 WRITE 0 */
    abort_code = set_Modes_of_operation(*(INTEGER8*)value);
    /* USER CODE BEGIN 0x6060 0x00 WRITE 1 */
    
    /* USER CODE END 0x6060 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6060_Modes_of_operation_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6060 0x00 READ 0 */
    
    /* USER CODE END 0x6060 0x00 READ 0 */
    *(INTEGER8*)value = get_Modes_of_operation();
    /* USER CODE BEGIN 0x6060 0x00 READ 1 */
    
    /* USER CODE END 0x6060 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6061_Modes_of_operation_display_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6061 0x00 READ 0 */
    
    /* USER CODE END 0x6061 0x00 READ 0 */
    *(INTEGER8*)value = get_Modes_of_operation_display();
    /* USER CODE BEGIN 0x6061 0x00 READ 1 */
    
    /* USER CODE END 0x6061 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x608F_Position_encoder_resolution_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x608F 0x00 WRITE 0 */
    
    /* USER CODE END 0x608F 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x608F 0x00 WRITE 1 */
    
    /* USER CODE END 0x608F 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x608F 0x01 WRITE 0 */
    
    /* USER CODE END 0x608F 0x01 WRITE 0 */
            abort_code = set_Position_encoder_resolution_Encoder_increments(*(UNS32*)value);
    /* USER CODE BEGIN 0x608F 0x01 WRITE 1 */
    
    /* USER CODE END 0x608F 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x608F 0x02 WRITE 0 */
    
    /* USER CODE END 0x608F 0x02 WRITE 0 */
            abort_code = set_Position_encoder_resolution_Motor_revolutions(*(UNS32*)value);
    /* USER CODE BEGIN 0x608F 0x02 WRITE 1 */
    
    /* USER CODE END 0x608F 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x608F_Position_encoder_resolution_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x608F 0x00 READ 0 */
    
    /* USER CODE END 0x608F 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x608F 0x00 READ 1 */
    
    /* USER CODE END 0x608F 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x608F 0x01 READ 0 */
    
    /* USER CODE END 0x608F 0x01 READ 0 */
            *(UNS32*)value = get_Position_encoder_resolution_Encoder_increments();
    /* USER CODE BEGIN 0x608F 0x01 READ 1 */
    
    /* USER CODE END 0x608F 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x608F 0x02 READ 0 */
    
    /* USER CODE END 0x608F 0x02 READ 0 */
            *(UNS32*)value = get_Position_encoder_resolution_Motor_revolutions();
    /* USER CODE BEGIN 0x608F 0x02 READ 1 */
    
    /* USER CODE END 0x608F 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x6091_Gear_ratio_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x6091 0x00 WRITE 0 */
    
    /* USER CODE END 0x6091 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x6091 0x00 WRITE 1 */
    
    /* USER CODE END 0x6091 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x6091 0x01 WRITE 0 */
    
    /* USER CODE END 0x6091 0x01 WRITE 0 */
            abort_code = set_Motor_revolutions(*(UNS32*)value);
    /* USER CODE BEGIN 0x6091 0x01 WRITE 1 */
    
    /* USER CODE END 0x6091 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x6091 0x02 WRITE 0 */
    
    /* USER CODE END 0x6091 0x02 WRITE 0 */
            abort_code = set_Shaft_revolutions(*(UNS32*)value);
    /* USER CODE BEGIN 0x6091 0x02 WRITE 1 */
    
    /* USER CODE END 0x6091 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x6091_Gear_ratio_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x6091 0x00 READ 0 */
    
    /* USER CODE END 0x6091 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6091 0x00 READ 1 */
    
    /* USER CODE END 0x6091 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x6091 0x01 READ 0 */
    
    /* USER CODE END 0x6091 0x01 READ 0 */
            *(UNS32*)value = get_Motor_revolutions();
    /* USER CODE BEGIN 0x6091 0x01 READ 1 */
    
    /* USER CODE END 0x6091 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x6091 0x02 READ 0 */
    
    /* USER CODE END 0x6091 0x02 READ 0 */
            *(UNS32*)value = get_Shaft_revolutions();
    /* USER CODE BEGIN 0x6091 0x02 READ 1 */
    
    /* USER CODE END 0x6091 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607E_Polarity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if (*(UNS8*)value > 1)
    {
        return ABORT_CODE_VALUE_TOO_HIGH;
    }
    /* USER CODE BEGIN 0x607E 0x00 WRITE 0 */
    
    /* USER CODE END 0x607E 0x00 WRITE 0 */
    abort_code = set_Polarity(*(UNS8*)value);
    /* USER CODE BEGIN 0x607E 0x00 WRITE 1 */
    
    /* USER CODE END 0x607E 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x607E_Polarity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x607E 0x00 READ 0 */
    
    /* USER CODE END 0x607E 0x00 READ 0 */
    *(UNS8*)value = get_Polarity();
    /* USER CODE BEGIN 0x607E 0x00 READ 1 */
    
    /* USER CODE END 0x607E 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x607A_Target_position_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607A 0x00 WRITE 0 */
    
    /* USER CODE END 0x607A 0x00 WRITE 0 */
    abort_code = set_Target_position(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607A 0x00 WRITE 1 */
    
    /* USER CODE END 0x607A 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x607A_Target_position_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x607A 0x00 READ 0 */
    
    /* USER CODE END 0x607A 0x00 READ 0 */
    *(INTEGER32*)value = get_Target_position();
    /* USER CODE BEGIN 0x607A 0x00 READ 1 */
    
    /* USER CODE END 0x607A 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x607B_Position_range_limit_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x607B 0x00 WRITE 0 */
    
    /* USER CODE END 0x607B 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x607B 0x00 WRITE 1 */
    
    /* USER CODE END 0x607B 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x607B 0x01 WRITE 0 */
    
    /* USER CODE END 0x607B 0x01 WRITE 0 */
            abort_code = set_Position_range_limit_Minimal_position_limit(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607B 0x01 WRITE 1 */
    
    /* USER CODE END 0x607B 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x607B 0x02 WRITE 0 */
    
    /* USER CODE END 0x607B 0x02 WRITE 0 */
            abort_code = set_Position_range_limit_Maximal_position_limit(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607B 0x02 WRITE 1 */
    
    /* USER CODE END 0x607B 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607B_Position_range_limit_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x607B 0x00 READ 0 */
    
    /* USER CODE END 0x607B 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607B 0x00 READ 1 */
    
    /* USER CODE END 0x607B 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x607B 0x01 READ 0 */
    
    /* USER CODE END 0x607B 0x01 READ 0 */
            *(INTEGER32*)value = get_Position_range_limit_Minimal_position_limit();
    /* USER CODE BEGIN 0x607B 0x01 READ 1 */
    
    /* USER CODE END 0x607B 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x607B 0x02 READ 0 */
    
    /* USER CODE END 0x607B 0x02 READ 0 */
            *(INTEGER32*)value = get_Position_range_limit_Maximal_position_limit();
    /* USER CODE BEGIN 0x607B 0x02 READ 1 */
    
    /* USER CODE END 0x607B 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607D_Software_position_limit_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x607D 0x00 WRITE 0 */
    
    /* USER CODE END 0x607D 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x607D 0x00 WRITE 1 */
    
    /* USER CODE END 0x607D 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x607D 0x01 WRITE 0 */
    
    /* USER CODE END 0x607D 0x01 WRITE 0 */
            abort_code = set_Software_position_limit_Minimal_position_limit(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607D 0x01 WRITE 1 */
    
    /* USER CODE END 0x607D 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x607D 0x02 WRITE 0 */
    
    /* USER CODE END 0x607D 0x02 WRITE 0 */
            abort_code = set_Software_position_limit_Maximal_position_limit(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607D 0x02 WRITE 1 */
    
    /* USER CODE END 0x607D 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607D_Software_position_limit_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x607D 0x00 READ 0 */
    
    /* USER CODE END 0x607D 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607D 0x00 READ 1 */
    
    /* USER CODE END 0x607D 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x607D 0x01 READ 0 */
    
    /* USER CODE END 0x607D 0x01 READ 0 */
            *(INTEGER32*)value = get_Software_position_limit_Minimal_position_limit();
    /* USER CODE BEGIN 0x607D 0x01 READ 1 */
    
    /* USER CODE END 0x607D 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x607D 0x02 READ 0 */
    
    /* USER CODE END 0x607D 0x02 READ 0 */
            *(INTEGER32*)value = get_Software_position_limit_Maximal_position_limit();
    /* USER CODE BEGIN 0x607D 0x02 READ 1 */
    
    /* USER CODE END 0x607D 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607F_Max_Profile_velocity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607F 0x00 WRITE 0 */
    
    /* USER CODE END 0x607F 0x00 WRITE 0 */
    abort_code = set_Max_Profile_velocity(*(UNS32*)value);
    /* USER CODE BEGIN 0x607F 0x00 WRITE 1 */
    
    /* USER CODE END 0x607F 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x607F_Max_Profile_velocity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x607F 0x00 READ 0 */
    
    /* USER CODE END 0x607F 0x00 READ 0 */
    *(UNS32*)value = get_Max_Profile_velocity();
    /* USER CODE BEGIN 0x607F 0x00 READ 1 */
    
    /* USER CODE END 0x607F 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6080_Max_motor_speed_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6080 0x00 WRITE 0 */
    return ABORT_CODE_UNSUPPORTED_ACCESS;  // 暂不支持该字典
    /* USER CODE END 0x6080 0x00 WRITE 0 */
    abort_code = set_Max_motor_speed(*(UNS32*)value);
    /* USER CODE BEGIN 0x6080 0x00 WRITE 1 */

    /* USER CODE END 0x6080 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6080_Max_motor_speed_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6080 0x00 READ 0 */
    
    /* USER CODE END 0x6080 0x00 READ 0 */
    *(UNS32*)value = get_Max_motor_speed();
    /* USER CODE BEGIN 0x6080 0x00 READ 1 */
    *(UNS32*)value = 0;  // 暂不支持该字典，返回0
    /* USER CODE END 0x6080 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6081_Profile_velocity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6081 0x00 WRITE 0 */
    
    /* USER CODE END 0x6081 0x00 WRITE 0 */
    abort_code = set_Profile_velocity(*(UNS32*)value);
    /* USER CODE BEGIN 0x6081 0x00 WRITE 1 */
    
    /* USER CODE END 0x6081 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6081_Profile_velocity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6081 0x00 READ 0 */
    
    /* USER CODE END 0x6081 0x00 READ 0 */
    *(UNS32*)value = get_Profile_velocity();
    /* USER CODE BEGIN 0x6081 0x00 READ 1 */
    
    /* USER CODE END 0x6081 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6083_Profile_acceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6083 0x00 WRITE 0 */
    
    /* USER CODE END 0x6083 0x00 WRITE 0 */
    abort_code = set_Profile_acceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x6083 0x00 WRITE 1 */
    
    /* USER CODE END 0x6083 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6083_Profile_acceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6083 0x00 READ 0 */
    
    /* USER CODE END 0x6083 0x00 READ 0 */
    *(UNS32*)value = get_Profile_acceleration();
    /* USER CODE BEGIN 0x6083 0x00 READ 1 */
    
    /* USER CODE END 0x6083 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6084_Profile_deceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6084 0x00 WRITE 0 */
    
    /* USER CODE END 0x6084 0x00 WRITE 0 */
    abort_code = set_Profile_deceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x6084 0x00 WRITE 1 */
    
    /* USER CODE END 0x6084 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6084_Profile_deceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6084 0x00 READ 0 */
    
    /* USER CODE END 0x6084 0x00 READ 0 */
    *(UNS32*)value = get_Profile_deceleration();
    /* USER CODE BEGIN 0x6084 0x00 READ 1 */
    
    /* USER CODE END 0x6084 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6085_Quick_stop_deceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6085 0x00 WRITE 0 */
    
    /* USER CODE END 0x6085 0x00 WRITE 0 */
    abort_code = set_Quick_stop_deceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x6085 0x00 WRITE 1 */
    
    /* USER CODE END 0x6085 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6085_Quick_stop_deceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6085 0x00 READ 0 */
    
    /* USER CODE END 0x6085 0x00 READ 0 */
    *(UNS32*)value = get_Quick_stop_deceleration();
    /* USER CODE BEGIN 0x6085 0x00 READ 1 */
    
    /* USER CODE END 0x6085 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60C5_Max_acceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60C5 0x00 WRITE 0 */
    
    /* USER CODE END 0x60C5 0x00 WRITE 0 */
    abort_code = set_Max_acceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x60C5 0x00 WRITE 1 */
    
    /* USER CODE END 0x60C5 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60C5_Max_acceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60C5 0x00 READ 0 */
    
    /* USER CODE END 0x60C5 0x00 READ 0 */
    *(UNS32*)value = get_Max_acceleration();
    /* USER CODE BEGIN 0x60C5 0x00 READ 1 */
    
    /* USER CODE END 0x60C5 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60C6_Max_deceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60C6 0x00 WRITE 0 */
    
    /* USER CODE END 0x60C6 0x00 WRITE 0 */
    abort_code = set_Max_deceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x60C6 0x00 WRITE 1 */
    
    /* USER CODE END 0x60C6 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60C6_Max_deceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60C6 0x00 READ 0 */
    
    /* USER CODE END 0x60C6 0x00 READ 0 */
    *(UNS32*)value = get_Max_deceleration();
    /* USER CODE BEGIN 0x60C6 0x00 READ 1 */
    
    /* USER CODE END 0x60C6 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6098_Homing_method_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6098 0x00 WRITE 0 */
    
    /* USER CODE END 0x6098 0x00 WRITE 0 */
    abort_code = set_Homing_method(*(INTEGER8*)value);
    /* USER CODE BEGIN 0x6098 0x00 WRITE 1 */
    
    /* USER CODE END 0x6098 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6098_Homing_method_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6098 0x00 READ 0 */
    
    /* USER CODE END 0x6098 0x00 READ 0 */
    *(INTEGER8*)value = get_Homing_method();
    /* USER CODE BEGIN 0x6098 0x00 READ 1 */
    
    /* USER CODE END 0x6098 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6062_Position_demand_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6062 0x00 READ 0 */
    
    /* USER CODE END 0x6062 0x00 READ 0 */
    *(INTEGER32*)value = get_Position_demand_value();
    /* USER CODE BEGIN 0x6062 0x00 READ 1 */
    
    /* USER CODE END 0x6062 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6063_Position_actual_value_inc_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6063 0x00 READ 0 */
    
    /* USER CODE END 0x6063 0x00 READ 0 */
    *(INTEGER32*)value = get_Position_actual_value_inc();
    /* USER CODE BEGIN 0x6063 0x00 READ 1 */
    
    /* USER CODE END 0x6063 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6064_Position_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6064 0x00 READ 0 */
    
    /* USER CODE END 0x6064 0x00 READ 0 */
    *(INTEGER32*)value = get_Position_actual_value();
    /* USER CODE BEGIN 0x6064 0x00 READ 1 */
    
    /* USER CODE END 0x6064 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6065_Following_error_window_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6065 0x00 WRITE 0 */
    
    /* USER CODE END 0x6065 0x00 WRITE 0 */
    abort_code = set_Following_error_window(*(UNS32*)value);
    /* USER CODE BEGIN 0x6065 0x00 WRITE 1 */
    
    /* USER CODE END 0x6065 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6065_Following_error_window_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6065 0x00 READ 0 */
    
    /* USER CODE END 0x6065 0x00 READ 0 */
    *(UNS32*)value = get_Following_error_window();
    /* USER CODE BEGIN 0x6065 0x00 READ 1 */
    
    /* USER CODE END 0x6065 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6066_Following_error_time_Out_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6066 0x00 WRITE 0 */
    
    /* USER CODE END 0x6066 0x00 WRITE 0 */
    abort_code = set_Following_error_time_Out(*(UNS16*)value);
    /* USER CODE BEGIN 0x6066 0x00 WRITE 1 */
    
    /* USER CODE END 0x6066 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6066_Following_error_time_Out_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6066 0x00 READ 0 */
    
    /* USER CODE END 0x6066 0x00 READ 0 */
    *(UNS16*)value = get_Following_error_time_Out();
    /* USER CODE BEGIN 0x6066 0x00 READ 1 */
    
    /* USER CODE END 0x6066 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6067_Position_window_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6067 0x00 WRITE 0 */
    
    /* USER CODE END 0x6067 0x00 WRITE 0 */
    abort_code = set_Position_window(*(UNS32*)value);
    /* USER CODE BEGIN 0x6067 0x00 WRITE 1 */
    
    /* USER CODE END 0x6067 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6067_Position_window_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6067 0x00 READ 0 */
    
    /* USER CODE END 0x6067 0x00 READ 0 */
    *(UNS32*)value = get_Position_window();
    /* USER CODE BEGIN 0x6067 0x00 READ 1 */
    
    /* USER CODE END 0x6067 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6068_Position_window_time_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6068 0x00 WRITE 0 */
    
    /* USER CODE END 0x6068 0x00 WRITE 0 */
    abort_code = set_Position_window_time(*(UNS16*)value);
    /* USER CODE BEGIN 0x6068 0x00 WRITE 1 */
    
    /* USER CODE END 0x6068 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6068_Position_window_time_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6068 0x00 READ 0 */
    
    /* USER CODE END 0x6068 0x00 READ 0 */
    *(UNS16*)value = get_Position_window_time();
    /* USER CODE BEGIN 0x6068 0x00 READ 1 */
    
    /* USER CODE END 0x6068 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60F4_Following_error_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60F4 0x00 READ 0 */
    
    /* USER CODE END 0x60F4 0x00 READ 0 */
    *(INTEGER32*)value = get_Following_error_actual_value();
    /* USER CODE BEGIN 0x60F4 0x00 READ 1 */
    
    /* USER CODE END 0x60F4 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606B_Velocity_demand_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606B 0x00 READ 0 */
    
    /* USER CODE END 0x606B 0x00 READ 0 */
    *(INTEGER32*)value = get_Velocity_demand_value();
    /* USER CODE BEGIN 0x606B 0x00 READ 1 */
    
    /* USER CODE END 0x606B 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606C_Velocity_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606C 0x00 READ 0 */
    
    /* USER CODE END 0x606C 0x00 READ 0 */
    *(INTEGER32*)value = get_Velocity_actual_value();
    /* USER CODE BEGIN 0x606C 0x00 READ 1 */
    
    /* USER CODE END 0x606C 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606D_Velocity_window_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x606D 0x00 WRITE 0 */
    
    /* USER CODE END 0x606D 0x00 WRITE 0 */
    abort_code = set_Velocity_window(*(UNS16*)value);
    /* USER CODE BEGIN 0x606D 0x00 WRITE 1 */
    
    /* USER CODE END 0x606D 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x606D_Velocity_window_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606D 0x00 READ 0 */
    
    /* USER CODE END 0x606D 0x00 READ 0 */
    *(UNS16*)value = get_Velocity_window();
    /* USER CODE BEGIN 0x606D 0x00 READ 1 */
    
    /* USER CODE END 0x606D 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606E_Velocity_window_time_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x606E 0x00 WRITE 0 */
    
    /* USER CODE END 0x606E 0x00 WRITE 0 */
    abort_code = set_Velocity_window_time(*(UNS16*)value);
    /* USER CODE BEGIN 0x606E 0x00 WRITE 1 */
    
    /* USER CODE END 0x606E 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x606E_Velocity_window_time_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606E 0x00 READ 0 */
    
    /* USER CODE END 0x606E 0x00 READ 0 */
    *(UNS16*)value = get_Velocity_window_time();
    /* USER CODE BEGIN 0x606E 0x00 READ 1 */
    
    /* USER CODE END 0x606E 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606F_Velocity_threshold_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x606F 0x00 WRITE 0 */
    
    /* USER CODE END 0x606F 0x00 WRITE 0 */
    abort_code = set_Velocity_threshold(*(UNS16*)value);
    /* USER CODE BEGIN 0x606F 0x00 WRITE 1 */
    
    /* USER CODE END 0x606F 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x606F_Velocity_threshold_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606F 0x00 READ 0 */
    
    /* USER CODE END 0x606F 0x00 READ 0 */
    *(UNS16*)value = get_Velocity_threshold();
    /* USER CODE BEGIN 0x606F 0x00 READ 1 */
    
    /* USER CODE END 0x606F 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6070_Velocity_threshold_time_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6070 0x00 WRITE 0 */
    
    /* USER CODE END 0x6070 0x00 WRITE 0 */
    abort_code = set_Velocity_threshold_time(*(UNS16*)value);
    /* USER CODE BEGIN 0x6070 0x00 WRITE 1 */
    
    /* USER CODE END 0x6070 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6070_Velocity_threshold_time_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6070 0x00 READ 0 */
    
    /* USER CODE END 0x6070 0x00 READ 0 */
    *(UNS16*)value = get_Velocity_threshold_time();
    /* USER CODE BEGIN 0x6070 0x00 READ 1 */
    
    /* USER CODE END 0x6070 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60FF_Target_velocity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60FF 0x00 WRITE 0 */
    
    /* USER CODE END 0x60FF 0x00 WRITE 0 */
    abort_code = set_Target_velocity(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x60FF 0x00 WRITE 1 */
    
    /* USER CODE END 0x60FF 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60FF_Target_velocity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60FF 0x00 READ 0 */
    
    /* USER CODE END 0x60FF 0x00 READ 0 */
    *(INTEGER32*)value = get_Target_velocity();
    /* USER CODE BEGIN 0x60FF 0x00 READ 1 */
    
    /* USER CODE END 0x60FF 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6071_Target_torque_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6071 0x00 WRITE 0 */
    
    /* USER CODE END 0x6071 0x00 WRITE 0 */
    abort_code = set_Target_torque(*(INTEGER16*)value);
    /* USER CODE BEGIN 0x6071 0x00 WRITE 1 */
    
    /* USER CODE END 0x6071 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6071_Target_torque_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6071 0x00 READ 0 */
    
    /* USER CODE END 0x6071 0x00 READ 0 */
    *(INTEGER16*)value = get_Target_torque();
    /* USER CODE BEGIN 0x6071 0x00 READ 1 */
    
    /* USER CODE END 0x6071 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6072_Max_torque_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6072 0x00 WRITE 0 */
    
    /* USER CODE END 0x6072 0x00 WRITE 0 */
    abort_code = set_Max_torque(*(UNS16*)value);
    /* USER CODE BEGIN 0x6072 0x00 WRITE 1 */
    
    /* USER CODE END 0x6072 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6072_Max_torque_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6072 0x00 READ 0 */
    
    /* USER CODE END 0x6072 0x00 READ 0 */
    *(UNS16*)value = get_Max_torque();
    /* USER CODE BEGIN 0x6072 0x00 READ 1 */
    
    /* USER CODE END 0x6072 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6073_Max_current_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6073 0x00 WRITE 0 */
    
    /* USER CODE END 0x6073 0x00 WRITE 0 */
    abort_code = set_Max_current(*(UNS16*)value);
    /* USER CODE BEGIN 0x6073 0x00 WRITE 1 */
    
    /* USER CODE END 0x6073 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6073_Max_current_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6073 0x00 READ 0 */
    
    /* USER CODE END 0x6073 0x00 READ 0 */
    *(UNS16*)value = get_Max_current();
    /* USER CODE BEGIN 0x6073 0x00 READ 1 */
    
    /* USER CODE END 0x6073 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6074_Torque_demand_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6074 0x00 READ 0 */
    
    /* USER CODE END 0x6074 0x00 READ 0 */
    *(INTEGER16*)value = get_Torque_demand_value();
    /* USER CODE BEGIN 0x6074 0x00 READ 1 */
    
    /* USER CODE END 0x6074 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6075_Motor_rated_current_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6075 0x00 WRITE 0 */
    
    /* USER CODE END 0x6075 0x00 WRITE 0 */
    abort_code = set_Motor_rated_current(*(UNS32*)value);
    /* USER CODE BEGIN 0x6075 0x00 WRITE 1 */
    
    /* USER CODE END 0x6075 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6075_Motor_rated_current_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6075 0x00 READ 0 */
    
    /* USER CODE END 0x6075 0x00 READ 0 */
    *(UNS32*)value = get_Motor_rated_current();
    /* USER CODE BEGIN 0x6075 0x00 READ 1 */
    
    /* USER CODE END 0x6075 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6076_Motor_rated_torque_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6076 0x00 WRITE 0 */
    
    /* USER CODE END 0x6076 0x00 WRITE 0 */
    abort_code = set_Motor_rated_torque(*(UNS32*)value);
    /* USER CODE BEGIN 0x6076 0x00 WRITE 1 */
    
    /* USER CODE END 0x6076 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6076_Motor_rated_torque_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6076 0x00 READ 0 */
    
    /* USER CODE END 0x6076 0x00 READ 0 */
    *(UNS32*)value = get_Motor_rated_torque();
    /* USER CODE BEGIN 0x6076 0x00 READ 1 */
    
    /* USER CODE END 0x6076 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6077_Torque_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6077 0x00 READ 0 */
    
    /* USER CODE END 0x6077 0x00 READ 0 */
    *(INTEGER16*)value = get_Torque_actual_value();
    /* USER CODE BEGIN 0x6077 0x00 READ 1 */
    
    /* USER CODE END 0x6077 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6078_Current_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6078 0x00 READ 0 */
    
    /* USER CODE END 0x6078 0x00 READ 0 */
    *(INTEGER16*)value = get_Current_actual_value();
    /* USER CODE BEGIN 0x6078 0x00 READ 1 */
    
    /* USER CODE END 0x6078 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6079_DC_link_circuit_voltage_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6079 0x00 READ 0 */
    
    /* USER CODE END 0x6079 0x00 READ 0 */
    *(UNS32*)value = get_DC_link_circuit_voltage();
    /* USER CODE BEGIN 0x6079 0x00 READ 1 */
    
    /* USER CODE END 0x6079 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6087_Torque_slope_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6087 0x00 WRITE 0 */
    
    /* USER CODE END 0x6087 0x00 WRITE 0 */
    abort_code = set_Torque_slope(*(UNS32*)value);
    /* USER CODE BEGIN 0x6087 0x00 WRITE 1 */
    
    /* USER CODE END 0x6087 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6087_Torque_slope_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6087 0x00 READ 0 */
    
    /* USER CODE END 0x6087 0x00 READ 0 */
    *(UNS32*)value = get_Torque_slope();
    /* USER CODE BEGIN 0x6087 0x00 READ 1 */
    
    /* USER CODE END 0x6087 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3000_Alarm_word_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3000 0x00 READ 0 */
    
    /* USER CODE END 0x3000 0x00 READ 0 */
    *(UNS32*)value = get_Alarm_word();
    /* USER CODE BEGIN 0x3000 0x00 READ 1 */
    
    /* USER CODE END 0x3000 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3001_MIT_feedforward_torque_current_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3001 0x00 WRITE 0 */
    
    /* USER CODE END 0x3001 0x00 WRITE 0 */
    abort_code = set_MIT_feedforward_torque_current(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x3001 0x00 WRITE 1 */
    
    /* USER CODE END 0x3001 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3001_MIT_feedforward_torque_current_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3001 0x00 READ 0 */
    
    /* USER CODE END 0x3001 0x00 READ 0 */
    *(INTEGER32*)value = get_MIT_feedforward_torque_current();
    /* USER CODE BEGIN 0x3001 0x00 READ 1 */
    
    /* USER CODE END 0x3001 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3002_MIT_target_position_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3002 0x00 WRITE 0 */
    
    /* USER CODE END 0x3002 0x00 WRITE 0 */
    abort_code = set_MIT_target_position(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x3002 0x00 WRITE 1 */
    
    /* USER CODE END 0x3002 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3002_MIT_target_position_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3002 0x00 READ 0 */
    
    /* USER CODE END 0x3002 0x00 READ 0 */
    *(INTEGER32*)value = get_MIT_target_position();
    /* USER CODE BEGIN 0x3002 0x00 READ 1 */
    
    /* USER CODE END 0x3002 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3003_MIT_max_current_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3003 0x00 WRITE 0 */
    
    /* USER CODE END 0x3003 0x00 WRITE 0 */
    abort_code = set_MIT_max_current(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x3003 0x00 WRITE 1 */
    
    /* USER CODE END 0x3003 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3003_MIT_max_current_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3003 0x00 READ 0 */
    
    /* USER CODE END 0x3003 0x00 READ 0 */
    *(INTEGER32*)value = get_MIT_max_current();
    /* USER CODE BEGIN 0x3003 0x00 READ 1 */
    
    /* USER CODE END 0x3003 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3004_MIT_target_velocity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3004 0x00 WRITE 0 */
    
    /* USER CODE END 0x3004 0x00 WRITE 0 */
    abort_code = set_MIT_target_velocity(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x3004 0x00 WRITE 1 */
    
    /* USER CODE END 0x3004 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3004_MIT_target_velocity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3004 0x00 READ 0 */
    
    /* USER CODE END 0x3004 0x00 READ 0 */
    *(INTEGER32*)value = get_MIT_target_velocity();
    /* USER CODE BEGIN 0x3004 0x00 READ 1 */
    
    /* USER CODE END 0x3004 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3005_MIT_Kp_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3005 0x00 WRITE 0 */
    
    /* USER CODE END 0x3005 0x00 WRITE 0 */
    abort_code = set_MIT_Kp(*(UNS32*)value);
    /* USER CODE BEGIN 0x3005 0x00 WRITE 1 */
    
    /* USER CODE END 0x3005 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3005_MIT_Kp_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3005 0x00 READ 0 */
    
    /* USER CODE END 0x3005 0x00 READ 0 */
    *(UNS32*)value = get_MIT_Kp();
    /* USER CODE BEGIN 0x3005 0x00 READ 1 */
    
    /* USER CODE END 0x3005 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3006_MIT_Kd_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3006 0x00 WRITE 0 */
    
    /* USER CODE END 0x3006 0x00 WRITE 0 */
    abort_code = set_MIT_Kd(*(UNS32*)value);
    /* USER CODE BEGIN 0x3006 0x00 WRITE 1 */
    
    /* USER CODE END 0x3006 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3006_MIT_Kd_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3006 0x00 READ 0 */
    
    /* USER CODE END 0x3006 0x00 READ 0 */
    *(UNS32*)value = get_MIT_Kd();
    /* USER CODE BEGIN 0x3006 0x00 READ 1 */
    
    /* USER CODE END 0x3006 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3007_SysCmd_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3007 0x00 WRITE 0 */
    
    /* USER CODE END 0x3007 0x00 WRITE 0 */
    abort_code = set_SysCmd(*(UNS8*)value);
    /* USER CODE BEGIN 0x3007 0x00 WRITE 1 */
    
    /* USER CODE END 0x3007 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3007_SysCmd_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3007 0x00 READ 0 */
    
    /* USER CODE END 0x3007 0x00 READ 0 */
    *(UNS8*)value = get_SysCmd();
    /* USER CODE BEGIN 0x3007 0x00 READ 1 */
    
    /* USER CODE END 0x3007 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3008_storage_status_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3008 0x00 READ 0 */
    
    /* USER CODE END 0x3008 0x00 READ 0 */
    *(INTEGER8*)value = get_storage_status();
    /* USER CODE BEGIN 0x3008 0x00 READ 1 */
    
    /* USER CODE END 0x3008 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3009_Notch_filter_frq_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    if (*(UNS16*)value > 255)
    {
        return ABORT_CODE_VALUE_TOO_HIGH;
    }
    if(subindex == 0)
    {
        return ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    }
    if(subindex > 6)
    {
        return ABORT_CODE_SUB_INDEX_NOT_EXIST;
    }
    /* USER CODE BEGIN 0x3009 0x01 WRITE 0 */
    
    /* USER CODE END 0x3009 0x01 WRITE 0 */
    abort_code = set_Notch_filter_frq(subindex - 1, *(UNS16*)value);
    /* USER CODE BEGIN 0x3009 0x01 WRITE 1 */
    
    /* USER CODE END 0x3009 0x01 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3009_Notch_filter_frq_Read_Callback(UNS8 subindex, void *value)
{
    if(subindex == 0)
    {
        *(UNS8*)value = 6;
        return ABORT_CODE_SUCCESSFUL;
    }
    /* USER CODE BEGIN 0x3009 0x01 READ 0 */
    
    /* USER CODE END 0x3009 0x01 READ 0 */
    *(UNS16*)value = get_Notch_filter_frq(subindex - 1);
    /* USER CODE BEGIN 0x3009 0x01 READ 1 */
    
    /* USER CODE END 0x3009 0x01 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x300A_Notch_filter_width_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    if (*(UNS16*)value > 255)
    {
        return ABORT_CODE_VALUE_TOO_HIGH;
    }
    if(subindex == 0)
    {
        return ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    }
    if(subindex > 6)
    {
        return ABORT_CODE_SUB_INDEX_NOT_EXIST;
    }
    /* USER CODE BEGIN 0x300A 0x01 WRITE 0 */
    
    /* USER CODE END 0x300A 0x01 WRITE 0 */
    abort_code = set_Notch_filter_width(subindex - 1, *(UNS16*)value);
    /* USER CODE BEGIN 0x300A 0x01 WRITE 1 */
    
    /* USER CODE END 0x300A 0x01 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x300A_Notch_filter_width_Read_Callback(UNS8 subindex, void *value)
{
    if(subindex == 0)
    {
        *(UNS8*)value = 6;
        return ABORT_CODE_SUCCESSFUL;
    }
    /* USER CODE BEGIN 0x300A 0x01 READ 0 */
    
    /* USER CODE END 0x300A 0x01 READ 0 */
    *(UNS16*)value = get_Notch_filter_width(subindex - 1);
    /* USER CODE BEGIN 0x300A 0x01 READ 1 */
    
    /* USER CODE END 0x300A 0x01 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x300B_Notch_filter_depth_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    if (*(UNS16*)value > 255)
    {
        return ABORT_CODE_VALUE_TOO_HIGH;
    }
    if(subindex == 0)
    {
        return ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    }
    if(subindex > 6)
    {
        return ABORT_CODE_SUB_INDEX_NOT_EXIST;
    }
    /* USER CODE BEGIN 0x300B 0x01 WRITE 0 */
    
    /* USER CODE END 0x300B 0x01 WRITE 0 */
    abort_code = set_Notch_filter_depth(subindex - 1, *(UNS16*)value);
    /* USER CODE BEGIN 0x300B 0x01 WRITE 1 */
    
    /* USER CODE END 0x300B 0x01 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x300B_Notch_filter_depth_Read_Callback(UNS8 subindex, void *value)
{
    if(subindex == 0)
    {
        *(UNS8*)value = 6;
        return ABORT_CODE_SUCCESSFUL;
    }
    /* USER CODE BEGIN 0x300B 0x01 READ 0 */
    
    /* USER CODE END 0x300B 0x01 READ 0 */
    *(UNS16*)value = get_Notch_filter_depth(subindex - 1);
    /* USER CODE BEGIN 0x300B 0x01 READ 1 */
    
    /* USER CODE END 0x300B 0x01 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x300C_Input_shaping_wn_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x300C 0x00 WRITE 0 */
    
    /* USER CODE END 0x300C 0x00 WRITE 0 */
    abort_code = set_Input_shaping_wn(*(UNS16*)value);
    /* USER CODE BEGIN 0x300C 0x00 WRITE 1 */
    
    /* USER CODE END 0x300C 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x300C_Input_shaping_wn_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x300C 0x00 READ 0 */
    
    /* USER CODE END 0x300C 0x00 READ 0 */
    *(UNS16*)value = get_Input_shaping_wn();
    /* USER CODE BEGIN 0x300C 0x00 READ 1 */
    
    /* USER CODE END 0x300C 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x300D_Pos_speed_ctl_aff_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if (*(UNS16*)value > 1000)
    {
        return ABORT_CODE_VALUE_TOO_HIGH;
    }
    /* USER CODE BEGIN 0x300D 0x00 WRITE 0 */
    
    /* USER CODE END 0x300D 0x00 WRITE 0 */
    abort_code = set_Pos_speed_ctl_aff(*(UNS16*)value);
    /* USER CODE BEGIN 0x300D 0x00 WRITE 1 */
    
    /* USER CODE END 0x300D 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x300D_Pos_speed_ctl_aff_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x300D 0x00 READ 0 */
    
    /* USER CODE END 0x300D 0x00 READ 0 */
    *(UNS16*)value = get_Pos_speed_ctl_aff();
    /* USER CODE BEGIN 0x300D 0x00 READ 1 */
    
    /* USER CODE END 0x300D 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x300E_Pos_speed_ctl_vff_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if (*(UNS16*)value > 1000)
    {
        return ABORT_CODE_VALUE_TOO_HIGH;
    }
    /* USER CODE BEGIN 0x300E 0x00 WRITE 0 */
    
    /* USER CODE END 0x300E 0x00 WRITE 0 */
    abort_code = set_Pos_speed_ctl_vff(*(UNS16*)value);
    /* USER CODE BEGIN 0x300E 0x00 WRITE 1 */
    
    /* USER CODE END 0x300E 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x300E_Pos_speed_ctl_vff_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x300E 0x00 READ 0 */
    
    /* USER CODE END 0x300E 0x00 READ 0 */
    *(UNS16*)value = get_Pos_speed_ctl_vff();
    /* USER CODE BEGIN 0x300E 0x00 READ 1 */
    
    /* USER CODE END 0x300E 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x300F_Pos_speed_ctl_j_kt_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x300F 0x00 WRITE 0 */
    
    /* USER CODE END 0x300F 0x00 WRITE 0 */
    abort_code = set_Pos_speed_ctl_j_kt(*(UNS32*)value);
    /* USER CODE BEGIN 0x300F 0x00 WRITE 1 */
    
    /* USER CODE END 0x300F 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x300F_Pos_speed_ctl_j_kt_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x300F 0x00 READ 0 */
    
    /* USER CODE END 0x300F 0x00 READ 0 */
    *(UNS32*)value = get_Pos_speed_ctl_j_kt();
    /* USER CODE BEGIN 0x300F 0x00 READ 1 */
    
    /* USER CODE END 0x300F 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3010_Pos_speed_ctl_ki_s_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3010 0x00 WRITE 0 */
    
    /* USER CODE END 0x3010 0x00 WRITE 0 */
    abort_code = set_Pos_speed_ctl_ki_s(*(UNS32*)value);
    /* USER CODE BEGIN 0x3010 0x00 WRITE 1 */
    
    /* USER CODE END 0x3010 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3010_Pos_speed_ctl_ki_s_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3010 0x00 READ 0 */
    
    /* USER CODE END 0x3010 0x00 READ 0 */
    *(UNS32*)value = get_Pos_speed_ctl_ki_s();
    /* USER CODE BEGIN 0x3010 0x00 READ 1 */
    
    /* USER CODE END 0x3010 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3011_Pos_speed_ctl_kp_p_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3011 0x00 WRITE 0 */
    
    /* USER CODE END 0x3011 0x00 WRITE 0 */
    abort_code = set_Pos_speed_ctl_kp_p(*(UNS16*)value);
    /* USER CODE BEGIN 0x3011 0x00 WRITE 1 */
    
    /* USER CODE END 0x3011 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3011_Pos_speed_ctl_kp_p_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3011 0x00 READ 0 */
    
    /* USER CODE END 0x3011 0x00 READ 0 */
    *(UNS16*)value = get_Pos_speed_ctl_kp_p();
    /* USER CODE BEGIN 0x3011 0x00 READ 1 */
    
    /* USER CODE END 0x3011 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3012_Pos_speed_ctl_kp_s_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3012 0x00 WRITE 0 */
    
    /* USER CODE END 0x3012 0x00 WRITE 0 */
    abort_code = set_Pos_speed_ctl_kp_s(*(UNS32*)value);
    /* USER CODE BEGIN 0x3012 0x00 WRITE 1 */
    
    /* USER CODE END 0x3012 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3012_Pos_speed_ctl_kp_s_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3012 0x00 READ 0 */
    
    /* USER CODE END 0x3012 0x00 READ 0 */
    *(UNS32*)value = get_Pos_speed_ctl_kp_s();
    /* USER CODE BEGIN 0x3012 0x00 READ 1 */
    
    /* USER CODE END 0x3012 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3013_Pos_speed_ctl_dob_wn_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3013 0x00 WRITE 0 */
    
    /* USER CODE END 0x3013 0x00 WRITE 0 */
    abort_code = set_Pos_speed_ctl_dob_wn(*(UNS16*)value);
    /* USER CODE BEGIN 0x3013 0x00 WRITE 1 */
    
    /* USER CODE END 0x3013 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3013_Pos_speed_ctl_dob_wn_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3013 0x00 READ 0 */
    
    /* USER CODE END 0x3013 0x00 READ 0 */
    *(UNS16*)value = get_Pos_speed_ctl_dob_wn();
    /* USER CODE BEGIN 0x3013 0x00 READ 1 */
    
    /* USER CODE END 0x3013 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3014_Pos_speed_ctl_dob_enable_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if (*(UNS8*)value > 1)
    {
        return ABORT_CODE_VALUE_TOO_HIGH;
    }
    /* USER CODE BEGIN 0x3014 0x00 WRITE 0 */
    
    /* USER CODE END 0x3014 0x00 WRITE 0 */
    abort_code = set_Pos_speed_ctl_dob_enable(*(UNS8*)value);
    /* USER CODE BEGIN 0x3014 0x00 WRITE 1 */
    
    /* USER CODE END 0x3014 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3014_Pos_speed_ctl_dob_enable_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3014 0x00 READ 0 */
    
    /* USER CODE END 0x3014 0x00 READ 0 */
    *(UNS8*)value = get_Pos_speed_ctl_dob_enable();
    /* USER CODE BEGIN 0x3014 0x00 READ 1 */
    
    /* USER CODE END 0x3014 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3015_Current_ctl_i_noise_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3015 0x00 WRITE 0 */
    
    /* USER CODE END 0x3015 0x00 WRITE 0 */
    abort_code = set_Current_ctl_i_noise(*(UNS16*)value);
    /* USER CODE BEGIN 0x3015 0x00 WRITE 1 */
    
    /* USER CODE END 0x3015 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3015_Current_ctl_i_noise_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3015 0x00 READ 0 */
    
    /* USER CODE END 0x3015 0x00 READ 0 */
    *(UNS16*)value = get_Current_ctl_i_noise();
    /* USER CODE BEGIN 0x3015 0x00 READ 1 */
    
    /* USER CODE END 0x3015 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3016_Current_ctl_comp_du_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3016 0x00 WRITE 0 */
    
    /* USER CODE END 0x3016 0x00 WRITE 0 */
    abort_code = set_Current_ctl_comp_du(*(UNS16*)value);
    /* USER CODE BEGIN 0x3016 0x00 WRITE 1 */
    
    /* USER CODE END 0x3016 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3016_Current_ctl_comp_du_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3016 0x00 READ 0 */
    
    /* USER CODE END 0x3016 0x00 READ 0 */
    *(UNS16*)value = get_Current_ctl_comp_du();
    /* USER CODE BEGIN 0x3016 0x00 READ 1 */
    
    /* USER CODE END 0x3016 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3017_Current_ctl_bandwidth_percentage_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3017 0x00 WRITE 0 */
    
    /* USER CODE END 0x3017 0x00 WRITE 0 */
    abort_code = set_Current_ctl_bandwidth_percentage(*(UNS16*)value);
    /* USER CODE BEGIN 0x3017 0x00 WRITE 1 */
    
    /* USER CODE END 0x3017 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3017_Current_ctl_bandwidth_percentage_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3017 0x00 READ 0 */
    
    /* USER CODE END 0x3017 0x00 READ 0 */
    *(UNS16*)value = get_Current_ctl_bandwidth_percentage();
    /* USER CODE BEGIN 0x3017 0x00 READ 1 */
    
    /* USER CODE END 0x3017 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3018_Current_ctl_kp_ld_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3018 0x00 WRITE 0 */
    
    /* USER CODE END 0x3018 0x00 WRITE 0 */
    abort_code = set_Current_ctl_kp_ld(*(UNS16*)value);
    /* USER CODE BEGIN 0x3018 0x00 WRITE 1 */
    
    /* USER CODE END 0x3018 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3018_Current_ctl_kp_ld_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3018 0x00 READ 0 */
    
    /* USER CODE END 0x3018 0x00 READ 0 */
    *(UNS16*)value = get_Current_ctl_kp_ld();
    /* USER CODE BEGIN 0x3018 0x00 READ 1 */
    
    /* USER CODE END 0x3018 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3019_Current_ctl_ki_ld_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3019 0x00 WRITE 0 */
    
    /* USER CODE END 0x3019 0x00 WRITE 0 */
    abort_code = set_Current_ctl_ki_ld(*(UNS16*)value);
    /* USER CODE BEGIN 0x3019 0x00 WRITE 1 */
    
    /* USER CODE END 0x3019 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3019_Current_ctl_ki_ld_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3019 0x00 READ 0 */
    
    /* USER CODE END 0x3019 0x00 READ 0 */
    *(UNS16*)value = get_Current_ctl_ki_ld();
    /* USER CODE BEGIN 0x3019 0x00 READ 1 */
    
    /* USER CODE END 0x3019 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3020_Current_ctl_kp_lq_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3020 0x00 WRITE 0 */
    
    /* USER CODE END 0x3020 0x00 WRITE 0 */
    abort_code = set_Current_ctl_kp_lq(*(UNS16*)value);
    /* USER CODE BEGIN 0x3020 0x00 WRITE 1 */
    
    /* USER CODE END 0x3020 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3020_Current_ctl_kp_lq_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3020 0x00 READ 0 */
    
    /* USER CODE END 0x3020 0x00 READ 0 */
    *(UNS16*)value = get_Current_ctl_kp_lq();
    /* USER CODE BEGIN 0x3020 0x00 READ 1 */
    
    /* USER CODE END 0x3020 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3021_Current_ctl_ki_lq_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3021 0x00 WRITE 0 */
    
    /* USER CODE END 0x3021 0x00 WRITE 0 */
    abort_code = set_Current_ctl_ki_lq(*(UNS16*)value);
    /* USER CODE BEGIN 0x3021 0x00 WRITE 1 */
    
    /* USER CODE END 0x3021 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3021_Current_ctl_ki_lq_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3021 0x00 READ 0 */
    
    /* USER CODE END 0x3021 0x00 READ 0 */
    *(UNS16*)value = get_Current_ctl_ki_lq();
    /* USER CODE BEGIN 0x3021 0x00 READ 1 */
    
    /* USER CODE END 0x3021 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x3022_Speed_obs_pll_wn_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x3022 0x00 WRITE 0 */
    
    /* USER CODE END 0x3022 0x00 WRITE 0 */
    abort_code = set_Speed_obs_pll_wn(*(UNS16*)value);
    /* USER CODE BEGIN 0x3022 0x00 WRITE 1 */
    
    /* USER CODE END 0x3022 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x3022_Speed_obs_pll_wn_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x3022 0x00 READ 0 */
    
    /* USER CODE END 0x3022 0x00 READ 0 */
    *(UNS16*)value = get_Speed_obs_pll_wn();
    /* USER CODE BEGIN 0x3022 0x00 READ 1 */
    
    /* USER CODE END 0x3022 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
