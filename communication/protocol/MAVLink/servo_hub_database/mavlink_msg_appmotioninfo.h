#pragma once
// MESSAGE AppMotionInfo PACKING

#define MAVLINK_MSG_ID_AppMotionInfo 30061


typedef struct __mavlink_appmotioninfo_t {
 int64_t Position_demand_value; /*<  */
 int64_t Position_actual_value_inc; /*<  */
 int64_t Position_actual_value; /*<  */
 int64_t Following_error_actual_value; /*<  */
 int64_t Motor_position_demand_value; /*<  */
 int64_t Motor_position_actual_value; /*<  */
 int64_t Motor_following_error_actual_value; /*<  */
 float Velocity_demand_value; /*<  */
 float Velocity_actual_value; /*<  */
 float Torque_demand_value; /*<  */
 float Torque_actual_value; /*<  */
 float Current_actual_value; /*<  */
 float D_current_actual_value; /*<  */
 float U_current_actual_value; /*<  */
 float V_current_actual_value; /*<  */
 float W_current_actual_value; /*<  */
 float Motor_velocity_demand_value; /*<  */
 float Motor_velocity_actual_value; /*<  */
 float Current_loop_time; /*<  */
 float Position_loop_time; /*<  */
 float Current_loop_cycle; /*<  */
 float Position_loop_cycle; /*<  */
 uint16_t U_adc_mid_val; /*<  */
 uint16_t V_adc_mid_val; /*<  */
 uint16_t W_adc_mid_val; /*<  */
} mavlink_appmotioninfo_t;

#define MAVLINK_MSG_ID_AppMotionInfo_LEN 122
#define MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN 122
#define MAVLINK_MSG_ID_30061_LEN 122
#define MAVLINK_MSG_ID_30061_MIN_LEN 122

#define MAVLINK_MSG_ID_AppMotionInfo_CRC 164
#define MAVLINK_MSG_ID_30061_CRC 164



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppMotionInfo { \
    30061, \
    "AppMotionInfo", \
    25, \
    {  { "Position_demand_value", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_appmotioninfo_t, Position_demand_value) }, \
         { "Position_actual_value_inc", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_appmotioninfo_t, Position_actual_value_inc) }, \
         { "Position_actual_value", NULL, MAVLINK_TYPE_INT64_T, 0, 16, offsetof(mavlink_appmotioninfo_t, Position_actual_value) }, \
         { "Following_error_actual_value", NULL, MAVLINK_TYPE_INT64_T, 0, 24, offsetof(mavlink_appmotioninfo_t, Following_error_actual_value) }, \
         { "Velocity_demand_value", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_appmotioninfo_t, Velocity_demand_value) }, \
         { "Velocity_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_appmotioninfo_t, Velocity_actual_value) }, \
         { "Torque_demand_value", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_appmotioninfo_t, Torque_demand_value) }, \
         { "Torque_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_appmotioninfo_t, Torque_actual_value) }, \
         { "Current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_appmotioninfo_t, Current_actual_value) }, \
         { "D_current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_appmotioninfo_t, D_current_actual_value) }, \
         { "U_current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_appmotioninfo_t, U_current_actual_value) }, \
         { "V_current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_appmotioninfo_t, V_current_actual_value) }, \
         { "W_current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_appmotioninfo_t, W_current_actual_value) }, \
         { "Motor_position_demand_value", NULL, MAVLINK_TYPE_INT64_T, 0, 32, offsetof(mavlink_appmotioninfo_t, Motor_position_demand_value) }, \
         { "Motor_position_actual_value", NULL, MAVLINK_TYPE_INT64_T, 0, 40, offsetof(mavlink_appmotioninfo_t, Motor_position_actual_value) }, \
         { "Motor_following_error_actual_value", NULL, MAVLINK_TYPE_INT64_T, 0, 48, offsetof(mavlink_appmotioninfo_t, Motor_following_error_actual_value) }, \
         { "Motor_velocity_demand_value", NULL, MAVLINK_TYPE_FLOAT, 0, 92, offsetof(mavlink_appmotioninfo_t, Motor_velocity_demand_value) }, \
         { "Motor_velocity_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 96, offsetof(mavlink_appmotioninfo_t, Motor_velocity_actual_value) }, \
         { "U_adc_mid_val", NULL, MAVLINK_TYPE_UINT16_T, 0, 116, offsetof(mavlink_appmotioninfo_t, U_adc_mid_val) }, \
         { "V_adc_mid_val", NULL, MAVLINK_TYPE_UINT16_T, 0, 118, offsetof(mavlink_appmotioninfo_t, V_adc_mid_val) }, \
         { "W_adc_mid_val", NULL, MAVLINK_TYPE_UINT16_T, 0, 120, offsetof(mavlink_appmotioninfo_t, W_adc_mid_val) }, \
         { "Current_loop_time", NULL, MAVLINK_TYPE_FLOAT, 0, 100, offsetof(mavlink_appmotioninfo_t, Current_loop_time) }, \
         { "Position_loop_time", NULL, MAVLINK_TYPE_FLOAT, 0, 104, offsetof(mavlink_appmotioninfo_t, Position_loop_time) }, \
         { "Current_loop_cycle", NULL, MAVLINK_TYPE_FLOAT, 0, 108, offsetof(mavlink_appmotioninfo_t, Current_loop_cycle) }, \
         { "Position_loop_cycle", NULL, MAVLINK_TYPE_FLOAT, 0, 112, offsetof(mavlink_appmotioninfo_t, Position_loop_cycle) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppMotionInfo { \
    "AppMotionInfo", \
    25, \
    {  { "Position_demand_value", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_appmotioninfo_t, Position_demand_value) }, \
         { "Position_actual_value_inc", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_appmotioninfo_t, Position_actual_value_inc) }, \
         { "Position_actual_value", NULL, MAVLINK_TYPE_INT64_T, 0, 16, offsetof(mavlink_appmotioninfo_t, Position_actual_value) }, \
         { "Following_error_actual_value", NULL, MAVLINK_TYPE_INT64_T, 0, 24, offsetof(mavlink_appmotioninfo_t, Following_error_actual_value) }, \
         { "Velocity_demand_value", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_appmotioninfo_t, Velocity_demand_value) }, \
         { "Velocity_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_appmotioninfo_t, Velocity_actual_value) }, \
         { "Torque_demand_value", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_appmotioninfo_t, Torque_demand_value) }, \
         { "Torque_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_appmotioninfo_t, Torque_actual_value) }, \
         { "Current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_appmotioninfo_t, Current_actual_value) }, \
         { "D_current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_appmotioninfo_t, D_current_actual_value) }, \
         { "U_current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_appmotioninfo_t, U_current_actual_value) }, \
         { "V_current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_appmotioninfo_t, V_current_actual_value) }, \
         { "W_current_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_appmotioninfo_t, W_current_actual_value) }, \
         { "Motor_position_demand_value", NULL, MAVLINK_TYPE_INT64_T, 0, 32, offsetof(mavlink_appmotioninfo_t, Motor_position_demand_value) }, \
         { "Motor_position_actual_value", NULL, MAVLINK_TYPE_INT64_T, 0, 40, offsetof(mavlink_appmotioninfo_t, Motor_position_actual_value) }, \
         { "Motor_following_error_actual_value", NULL, MAVLINK_TYPE_INT64_T, 0, 48, offsetof(mavlink_appmotioninfo_t, Motor_following_error_actual_value) }, \
         { "Motor_velocity_demand_value", NULL, MAVLINK_TYPE_FLOAT, 0, 92, offsetof(mavlink_appmotioninfo_t, Motor_velocity_demand_value) }, \
         { "Motor_velocity_actual_value", NULL, MAVLINK_TYPE_FLOAT, 0, 96, offsetof(mavlink_appmotioninfo_t, Motor_velocity_actual_value) }, \
         { "U_adc_mid_val", NULL, MAVLINK_TYPE_UINT16_T, 0, 116, offsetof(mavlink_appmotioninfo_t, U_adc_mid_val) }, \
         { "V_adc_mid_val", NULL, MAVLINK_TYPE_UINT16_T, 0, 118, offsetof(mavlink_appmotioninfo_t, V_adc_mid_val) }, \
         { "W_adc_mid_val", NULL, MAVLINK_TYPE_UINT16_T, 0, 120, offsetof(mavlink_appmotioninfo_t, W_adc_mid_val) }, \
         { "Current_loop_time", NULL, MAVLINK_TYPE_FLOAT, 0, 100, offsetof(mavlink_appmotioninfo_t, Current_loop_time) }, \
         { "Position_loop_time", NULL, MAVLINK_TYPE_FLOAT, 0, 104, offsetof(mavlink_appmotioninfo_t, Position_loop_time) }, \
         { "Current_loop_cycle", NULL, MAVLINK_TYPE_FLOAT, 0, 108, offsetof(mavlink_appmotioninfo_t, Current_loop_cycle) }, \
         { "Position_loop_cycle", NULL, MAVLINK_TYPE_FLOAT, 0, 112, offsetof(mavlink_appmotioninfo_t, Position_loop_cycle) }, \
         } \
}
#endif

/**
 * @brief Pack a appmotioninfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Position_demand_value  
 * @param Position_actual_value_inc  
 * @param Position_actual_value  
 * @param Following_error_actual_value  
 * @param Velocity_demand_value  
 * @param Velocity_actual_value  
 * @param Torque_demand_value  
 * @param Torque_actual_value  
 * @param Current_actual_value  
 * @param D_current_actual_value  
 * @param U_current_actual_value  
 * @param V_current_actual_value  
 * @param W_current_actual_value  
 * @param Motor_position_demand_value  
 * @param Motor_position_actual_value  
 * @param Motor_following_error_actual_value  
 * @param Motor_velocity_demand_value  
 * @param Motor_velocity_actual_value  
 * @param U_adc_mid_val  
 * @param V_adc_mid_val  
 * @param W_adc_mid_val  
 * @param Current_loop_time  
 * @param Position_loop_time  
 * @param Current_loop_cycle  
 * @param Position_loop_cycle  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotioninfo_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t Position_demand_value, int64_t Position_actual_value_inc, int64_t Position_actual_value, int64_t Following_error_actual_value, float Velocity_demand_value, float Velocity_actual_value, float Torque_demand_value, float Torque_actual_value, float Current_actual_value, float D_current_actual_value, float U_current_actual_value, float V_current_actual_value, float W_current_actual_value, int64_t Motor_position_demand_value, int64_t Motor_position_actual_value, int64_t Motor_following_error_actual_value, float Motor_velocity_demand_value, float Motor_velocity_actual_value, uint16_t U_adc_mid_val, uint16_t V_adc_mid_val, uint16_t W_adc_mid_val, float Current_loop_time, float Position_loop_time, float Current_loop_cycle, float Position_loop_cycle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotionInfo_LEN];
    _mav_put_int64_t(buf, 0, Position_demand_value);
    _mav_put_int64_t(buf, 8, Position_actual_value_inc);
    _mav_put_int64_t(buf, 16, Position_actual_value);
    _mav_put_int64_t(buf, 24, Following_error_actual_value);
    _mav_put_int64_t(buf, 32, Motor_position_demand_value);
    _mav_put_int64_t(buf, 40, Motor_position_actual_value);
    _mav_put_int64_t(buf, 48, Motor_following_error_actual_value);
    _mav_put_float(buf, 56, Velocity_demand_value);
    _mav_put_float(buf, 60, Velocity_actual_value);
    _mav_put_float(buf, 64, Torque_demand_value);
    _mav_put_float(buf, 68, Torque_actual_value);
    _mav_put_float(buf, 72, Current_actual_value);
    _mav_put_float(buf, 76, D_current_actual_value);
    _mav_put_float(buf, 80, U_current_actual_value);
    _mav_put_float(buf, 84, V_current_actual_value);
    _mav_put_float(buf, 88, W_current_actual_value);
    _mav_put_float(buf, 92, Motor_velocity_demand_value);
    _mav_put_float(buf, 96, Motor_velocity_actual_value);
    _mav_put_float(buf, 100, Current_loop_time);
    _mav_put_float(buf, 104, Position_loop_time);
    _mav_put_float(buf, 108, Current_loop_cycle);
    _mav_put_float(buf, 112, Position_loop_cycle);
    _mav_put_uint16_t(buf, 116, U_adc_mid_val);
    _mav_put_uint16_t(buf, 118, V_adc_mid_val);
    _mav_put_uint16_t(buf, 120, W_adc_mid_val);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotionInfo_LEN);
#else
    mavlink_appmotioninfo_t packet;
    packet.Position_demand_value = Position_demand_value;
    packet.Position_actual_value_inc = Position_actual_value_inc;
    packet.Position_actual_value = Position_actual_value;
    packet.Following_error_actual_value = Following_error_actual_value;
    packet.Motor_position_demand_value = Motor_position_demand_value;
    packet.Motor_position_actual_value = Motor_position_actual_value;
    packet.Motor_following_error_actual_value = Motor_following_error_actual_value;
    packet.Velocity_demand_value = Velocity_demand_value;
    packet.Velocity_actual_value = Velocity_actual_value;
    packet.Torque_demand_value = Torque_demand_value;
    packet.Torque_actual_value = Torque_actual_value;
    packet.Current_actual_value = Current_actual_value;
    packet.D_current_actual_value = D_current_actual_value;
    packet.U_current_actual_value = U_current_actual_value;
    packet.V_current_actual_value = V_current_actual_value;
    packet.W_current_actual_value = W_current_actual_value;
    packet.Motor_velocity_demand_value = Motor_velocity_demand_value;
    packet.Motor_velocity_actual_value = Motor_velocity_actual_value;
    packet.Current_loop_time = Current_loop_time;
    packet.Position_loop_time = Position_loop_time;
    packet.Current_loop_cycle = Current_loop_cycle;
    packet.Position_loop_cycle = Position_loop_cycle;
    packet.U_adc_mid_val = U_adc_mid_val;
    packet.V_adc_mid_val = V_adc_mid_val;
    packet.W_adc_mid_val = W_adc_mid_val;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotionInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotionInfo;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN, MAVLINK_MSG_ID_AppMotionInfo_CRC);
}

/**
 * @brief Pack a appmotioninfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Position_demand_value  
 * @param Position_actual_value_inc  
 * @param Position_actual_value  
 * @param Following_error_actual_value  
 * @param Velocity_demand_value  
 * @param Velocity_actual_value  
 * @param Torque_demand_value  
 * @param Torque_actual_value  
 * @param Current_actual_value  
 * @param D_current_actual_value  
 * @param U_current_actual_value  
 * @param V_current_actual_value  
 * @param W_current_actual_value  
 * @param Motor_position_demand_value  
 * @param Motor_position_actual_value  
 * @param Motor_following_error_actual_value  
 * @param Motor_velocity_demand_value  
 * @param Motor_velocity_actual_value  
 * @param U_adc_mid_val  
 * @param V_adc_mid_val  
 * @param W_adc_mid_val  
 * @param Current_loop_time  
 * @param Position_loop_time  
 * @param Current_loop_cycle  
 * @param Position_loop_cycle  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotioninfo_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t Position_demand_value, int64_t Position_actual_value_inc, int64_t Position_actual_value, int64_t Following_error_actual_value, float Velocity_demand_value, float Velocity_actual_value, float Torque_demand_value, float Torque_actual_value, float Current_actual_value, float D_current_actual_value, float U_current_actual_value, float V_current_actual_value, float W_current_actual_value, int64_t Motor_position_demand_value, int64_t Motor_position_actual_value, int64_t Motor_following_error_actual_value, float Motor_velocity_demand_value, float Motor_velocity_actual_value, uint16_t U_adc_mid_val, uint16_t V_adc_mid_val, uint16_t W_adc_mid_val, float Current_loop_time, float Position_loop_time, float Current_loop_cycle, float Position_loop_cycle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotionInfo_LEN];
    _mav_put_int64_t(buf, 0, Position_demand_value);
    _mav_put_int64_t(buf, 8, Position_actual_value_inc);
    _mav_put_int64_t(buf, 16, Position_actual_value);
    _mav_put_int64_t(buf, 24, Following_error_actual_value);
    _mav_put_int64_t(buf, 32, Motor_position_demand_value);
    _mav_put_int64_t(buf, 40, Motor_position_actual_value);
    _mav_put_int64_t(buf, 48, Motor_following_error_actual_value);
    _mav_put_float(buf, 56, Velocity_demand_value);
    _mav_put_float(buf, 60, Velocity_actual_value);
    _mav_put_float(buf, 64, Torque_demand_value);
    _mav_put_float(buf, 68, Torque_actual_value);
    _mav_put_float(buf, 72, Current_actual_value);
    _mav_put_float(buf, 76, D_current_actual_value);
    _mav_put_float(buf, 80, U_current_actual_value);
    _mav_put_float(buf, 84, V_current_actual_value);
    _mav_put_float(buf, 88, W_current_actual_value);
    _mav_put_float(buf, 92, Motor_velocity_demand_value);
    _mav_put_float(buf, 96, Motor_velocity_actual_value);
    _mav_put_float(buf, 100, Current_loop_time);
    _mav_put_float(buf, 104, Position_loop_time);
    _mav_put_float(buf, 108, Current_loop_cycle);
    _mav_put_float(buf, 112, Position_loop_cycle);
    _mav_put_uint16_t(buf, 116, U_adc_mid_val);
    _mav_put_uint16_t(buf, 118, V_adc_mid_val);
    _mav_put_uint16_t(buf, 120, W_adc_mid_val);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotionInfo_LEN);
#else
    mavlink_appmotioninfo_t packet;
    packet.Position_demand_value = Position_demand_value;
    packet.Position_actual_value_inc = Position_actual_value_inc;
    packet.Position_actual_value = Position_actual_value;
    packet.Following_error_actual_value = Following_error_actual_value;
    packet.Motor_position_demand_value = Motor_position_demand_value;
    packet.Motor_position_actual_value = Motor_position_actual_value;
    packet.Motor_following_error_actual_value = Motor_following_error_actual_value;
    packet.Velocity_demand_value = Velocity_demand_value;
    packet.Velocity_actual_value = Velocity_actual_value;
    packet.Torque_demand_value = Torque_demand_value;
    packet.Torque_actual_value = Torque_actual_value;
    packet.Current_actual_value = Current_actual_value;
    packet.D_current_actual_value = D_current_actual_value;
    packet.U_current_actual_value = U_current_actual_value;
    packet.V_current_actual_value = V_current_actual_value;
    packet.W_current_actual_value = W_current_actual_value;
    packet.Motor_velocity_demand_value = Motor_velocity_demand_value;
    packet.Motor_velocity_actual_value = Motor_velocity_actual_value;
    packet.Current_loop_time = Current_loop_time;
    packet.Position_loop_time = Position_loop_time;
    packet.Current_loop_cycle = Current_loop_cycle;
    packet.Position_loop_cycle = Position_loop_cycle;
    packet.U_adc_mid_val = U_adc_mid_val;
    packet.V_adc_mid_val = V_adc_mid_val;
    packet.W_adc_mid_val = W_adc_mid_val;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotionInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotionInfo;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN, MAVLINK_MSG_ID_AppMotionInfo_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN);
#endif
}

/**
 * @brief Pack a appmotioninfo message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Position_demand_value  
 * @param Position_actual_value_inc  
 * @param Position_actual_value  
 * @param Following_error_actual_value  
 * @param Velocity_demand_value  
 * @param Velocity_actual_value  
 * @param Torque_demand_value  
 * @param Torque_actual_value  
 * @param Current_actual_value  
 * @param D_current_actual_value  
 * @param U_current_actual_value  
 * @param V_current_actual_value  
 * @param W_current_actual_value  
 * @param Motor_position_demand_value  
 * @param Motor_position_actual_value  
 * @param Motor_following_error_actual_value  
 * @param Motor_velocity_demand_value  
 * @param Motor_velocity_actual_value  
 * @param U_adc_mid_val  
 * @param V_adc_mid_val  
 * @param W_adc_mid_val  
 * @param Current_loop_time  
 * @param Position_loop_time  
 * @param Current_loop_cycle  
 * @param Position_loop_cycle  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotioninfo_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t Position_demand_value,int64_t Position_actual_value_inc,int64_t Position_actual_value,int64_t Following_error_actual_value,float Velocity_demand_value,float Velocity_actual_value,float Torque_demand_value,float Torque_actual_value,float Current_actual_value,float D_current_actual_value,float U_current_actual_value,float V_current_actual_value,float W_current_actual_value,int64_t Motor_position_demand_value,int64_t Motor_position_actual_value,int64_t Motor_following_error_actual_value,float Motor_velocity_demand_value,float Motor_velocity_actual_value,uint16_t U_adc_mid_val,uint16_t V_adc_mid_val,uint16_t W_adc_mid_val,float Current_loop_time,float Position_loop_time,float Current_loop_cycle,float Position_loop_cycle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotionInfo_LEN];
    _mav_put_int64_t(buf, 0, Position_demand_value);
    _mav_put_int64_t(buf, 8, Position_actual_value_inc);
    _mav_put_int64_t(buf, 16, Position_actual_value);
    _mav_put_int64_t(buf, 24, Following_error_actual_value);
    _mav_put_int64_t(buf, 32, Motor_position_demand_value);
    _mav_put_int64_t(buf, 40, Motor_position_actual_value);
    _mav_put_int64_t(buf, 48, Motor_following_error_actual_value);
    _mav_put_float(buf, 56, Velocity_demand_value);
    _mav_put_float(buf, 60, Velocity_actual_value);
    _mav_put_float(buf, 64, Torque_demand_value);
    _mav_put_float(buf, 68, Torque_actual_value);
    _mav_put_float(buf, 72, Current_actual_value);
    _mav_put_float(buf, 76, D_current_actual_value);
    _mav_put_float(buf, 80, U_current_actual_value);
    _mav_put_float(buf, 84, V_current_actual_value);
    _mav_put_float(buf, 88, W_current_actual_value);
    _mav_put_float(buf, 92, Motor_velocity_demand_value);
    _mav_put_float(buf, 96, Motor_velocity_actual_value);
    _mav_put_float(buf, 100, Current_loop_time);
    _mav_put_float(buf, 104, Position_loop_time);
    _mav_put_float(buf, 108, Current_loop_cycle);
    _mav_put_float(buf, 112, Position_loop_cycle);
    _mav_put_uint16_t(buf, 116, U_adc_mid_val);
    _mav_put_uint16_t(buf, 118, V_adc_mid_val);
    _mav_put_uint16_t(buf, 120, W_adc_mid_val);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotionInfo_LEN);
#else
    mavlink_appmotioninfo_t packet;
    packet.Position_demand_value = Position_demand_value;
    packet.Position_actual_value_inc = Position_actual_value_inc;
    packet.Position_actual_value = Position_actual_value;
    packet.Following_error_actual_value = Following_error_actual_value;
    packet.Motor_position_demand_value = Motor_position_demand_value;
    packet.Motor_position_actual_value = Motor_position_actual_value;
    packet.Motor_following_error_actual_value = Motor_following_error_actual_value;
    packet.Velocity_demand_value = Velocity_demand_value;
    packet.Velocity_actual_value = Velocity_actual_value;
    packet.Torque_demand_value = Torque_demand_value;
    packet.Torque_actual_value = Torque_actual_value;
    packet.Current_actual_value = Current_actual_value;
    packet.D_current_actual_value = D_current_actual_value;
    packet.U_current_actual_value = U_current_actual_value;
    packet.V_current_actual_value = V_current_actual_value;
    packet.W_current_actual_value = W_current_actual_value;
    packet.Motor_velocity_demand_value = Motor_velocity_demand_value;
    packet.Motor_velocity_actual_value = Motor_velocity_actual_value;
    packet.Current_loop_time = Current_loop_time;
    packet.Position_loop_time = Position_loop_time;
    packet.Current_loop_cycle = Current_loop_cycle;
    packet.Position_loop_cycle = Position_loop_cycle;
    packet.U_adc_mid_val = U_adc_mid_val;
    packet.V_adc_mid_val = V_adc_mid_val;
    packet.W_adc_mid_val = W_adc_mid_val;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotionInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotionInfo;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN, MAVLINK_MSG_ID_AppMotionInfo_CRC);
}

/**
 * @brief Encode a appmotioninfo struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appmotioninfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotioninfo_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appmotioninfo_t* appmotioninfo)
{
    return mavlink_msg_appmotioninfo_pack(system_id, component_id, msg, appmotioninfo->Position_demand_value, appmotioninfo->Position_actual_value_inc, appmotioninfo->Position_actual_value, appmotioninfo->Following_error_actual_value, appmotioninfo->Velocity_demand_value, appmotioninfo->Velocity_actual_value, appmotioninfo->Torque_demand_value, appmotioninfo->Torque_actual_value, appmotioninfo->Current_actual_value, appmotioninfo->D_current_actual_value, appmotioninfo->U_current_actual_value, appmotioninfo->V_current_actual_value, appmotioninfo->W_current_actual_value, appmotioninfo->Motor_position_demand_value, appmotioninfo->Motor_position_actual_value, appmotioninfo->Motor_following_error_actual_value, appmotioninfo->Motor_velocity_demand_value, appmotioninfo->Motor_velocity_actual_value, appmotioninfo->U_adc_mid_val, appmotioninfo->V_adc_mid_val, appmotioninfo->W_adc_mid_val, appmotioninfo->Current_loop_time, appmotioninfo->Position_loop_time, appmotioninfo->Current_loop_cycle, appmotioninfo->Position_loop_cycle);
}

/**
 * @brief Encode a appmotioninfo struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appmotioninfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotioninfo_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appmotioninfo_t* appmotioninfo)
{
    return mavlink_msg_appmotioninfo_pack_chan(system_id, component_id, chan, msg, appmotioninfo->Position_demand_value, appmotioninfo->Position_actual_value_inc, appmotioninfo->Position_actual_value, appmotioninfo->Following_error_actual_value, appmotioninfo->Velocity_demand_value, appmotioninfo->Velocity_actual_value, appmotioninfo->Torque_demand_value, appmotioninfo->Torque_actual_value, appmotioninfo->Current_actual_value, appmotioninfo->D_current_actual_value, appmotioninfo->U_current_actual_value, appmotioninfo->V_current_actual_value, appmotioninfo->W_current_actual_value, appmotioninfo->Motor_position_demand_value, appmotioninfo->Motor_position_actual_value, appmotioninfo->Motor_following_error_actual_value, appmotioninfo->Motor_velocity_demand_value, appmotioninfo->Motor_velocity_actual_value, appmotioninfo->U_adc_mid_val, appmotioninfo->V_adc_mid_val, appmotioninfo->W_adc_mid_val, appmotioninfo->Current_loop_time, appmotioninfo->Position_loop_time, appmotioninfo->Current_loop_cycle, appmotioninfo->Position_loop_cycle);
}

/**
 * @brief Encode a appmotioninfo struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appmotioninfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotioninfo_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appmotioninfo_t* appmotioninfo)
{
    return mavlink_msg_appmotioninfo_pack_status(system_id, component_id, _status, msg,  appmotioninfo->Position_demand_value, appmotioninfo->Position_actual_value_inc, appmotioninfo->Position_actual_value, appmotioninfo->Following_error_actual_value, appmotioninfo->Velocity_demand_value, appmotioninfo->Velocity_actual_value, appmotioninfo->Torque_demand_value, appmotioninfo->Torque_actual_value, appmotioninfo->Current_actual_value, appmotioninfo->D_current_actual_value, appmotioninfo->U_current_actual_value, appmotioninfo->V_current_actual_value, appmotioninfo->W_current_actual_value, appmotioninfo->Motor_position_demand_value, appmotioninfo->Motor_position_actual_value, appmotioninfo->Motor_following_error_actual_value, appmotioninfo->Motor_velocity_demand_value, appmotioninfo->Motor_velocity_actual_value, appmotioninfo->U_adc_mid_val, appmotioninfo->V_adc_mid_val, appmotioninfo->W_adc_mid_val, appmotioninfo->Current_loop_time, appmotioninfo->Position_loop_time, appmotioninfo->Current_loop_cycle, appmotioninfo->Position_loop_cycle);
}

/**
 * @brief Send a appmotioninfo message
 * @param chan MAVLink channel to send the message
 *
 * @param Position_demand_value  
 * @param Position_actual_value_inc  
 * @param Position_actual_value  
 * @param Following_error_actual_value  
 * @param Velocity_demand_value  
 * @param Velocity_actual_value  
 * @param Torque_demand_value  
 * @param Torque_actual_value  
 * @param Current_actual_value  
 * @param D_current_actual_value  
 * @param U_current_actual_value  
 * @param V_current_actual_value  
 * @param W_current_actual_value  
 * @param Motor_position_demand_value  
 * @param Motor_position_actual_value  
 * @param Motor_following_error_actual_value  
 * @param Motor_velocity_demand_value  
 * @param Motor_velocity_actual_value  
 * @param U_adc_mid_val  
 * @param V_adc_mid_val  
 * @param W_adc_mid_val  
 * @param Current_loop_time  
 * @param Position_loop_time  
 * @param Current_loop_cycle  
 * @param Position_loop_cycle  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appmotioninfo_send(mavlink_channel_t chan, int64_t Position_demand_value, int64_t Position_actual_value_inc, int64_t Position_actual_value, int64_t Following_error_actual_value, float Velocity_demand_value, float Velocity_actual_value, float Torque_demand_value, float Torque_actual_value, float Current_actual_value, float D_current_actual_value, float U_current_actual_value, float V_current_actual_value, float W_current_actual_value, int64_t Motor_position_demand_value, int64_t Motor_position_actual_value, int64_t Motor_following_error_actual_value, float Motor_velocity_demand_value, float Motor_velocity_actual_value, uint16_t U_adc_mid_val, uint16_t V_adc_mid_val, uint16_t W_adc_mid_val, float Current_loop_time, float Position_loop_time, float Current_loop_cycle, float Position_loop_cycle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotionInfo_LEN];
    _mav_put_int64_t(buf, 0, Position_demand_value);
    _mav_put_int64_t(buf, 8, Position_actual_value_inc);
    _mav_put_int64_t(buf, 16, Position_actual_value);
    _mav_put_int64_t(buf, 24, Following_error_actual_value);
    _mav_put_int64_t(buf, 32, Motor_position_demand_value);
    _mav_put_int64_t(buf, 40, Motor_position_actual_value);
    _mav_put_int64_t(buf, 48, Motor_following_error_actual_value);
    _mav_put_float(buf, 56, Velocity_demand_value);
    _mav_put_float(buf, 60, Velocity_actual_value);
    _mav_put_float(buf, 64, Torque_demand_value);
    _mav_put_float(buf, 68, Torque_actual_value);
    _mav_put_float(buf, 72, Current_actual_value);
    _mav_put_float(buf, 76, D_current_actual_value);
    _mav_put_float(buf, 80, U_current_actual_value);
    _mav_put_float(buf, 84, V_current_actual_value);
    _mav_put_float(buf, 88, W_current_actual_value);
    _mav_put_float(buf, 92, Motor_velocity_demand_value);
    _mav_put_float(buf, 96, Motor_velocity_actual_value);
    _mav_put_float(buf, 100, Current_loop_time);
    _mav_put_float(buf, 104, Position_loop_time);
    _mav_put_float(buf, 108, Current_loop_cycle);
    _mav_put_float(buf, 112, Position_loop_cycle);
    _mav_put_uint16_t(buf, 116, U_adc_mid_val);
    _mav_put_uint16_t(buf, 118, V_adc_mid_val);
    _mav_put_uint16_t(buf, 120, W_adc_mid_val);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionInfo, buf, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN, MAVLINK_MSG_ID_AppMotionInfo_CRC);
#else
    mavlink_appmotioninfo_t packet;
    packet.Position_demand_value = Position_demand_value;
    packet.Position_actual_value_inc = Position_actual_value_inc;
    packet.Position_actual_value = Position_actual_value;
    packet.Following_error_actual_value = Following_error_actual_value;
    packet.Motor_position_demand_value = Motor_position_demand_value;
    packet.Motor_position_actual_value = Motor_position_actual_value;
    packet.Motor_following_error_actual_value = Motor_following_error_actual_value;
    packet.Velocity_demand_value = Velocity_demand_value;
    packet.Velocity_actual_value = Velocity_actual_value;
    packet.Torque_demand_value = Torque_demand_value;
    packet.Torque_actual_value = Torque_actual_value;
    packet.Current_actual_value = Current_actual_value;
    packet.D_current_actual_value = D_current_actual_value;
    packet.U_current_actual_value = U_current_actual_value;
    packet.V_current_actual_value = V_current_actual_value;
    packet.W_current_actual_value = W_current_actual_value;
    packet.Motor_velocity_demand_value = Motor_velocity_demand_value;
    packet.Motor_velocity_actual_value = Motor_velocity_actual_value;
    packet.Current_loop_time = Current_loop_time;
    packet.Position_loop_time = Position_loop_time;
    packet.Current_loop_cycle = Current_loop_cycle;
    packet.Position_loop_cycle = Position_loop_cycle;
    packet.U_adc_mid_val = U_adc_mid_val;
    packet.V_adc_mid_val = V_adc_mid_val;
    packet.W_adc_mid_val = W_adc_mid_val;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionInfo, (const char *)&packet, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN, MAVLINK_MSG_ID_AppMotionInfo_CRC);
#endif
}

/**
 * @brief Send a appmotioninfo message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appmotioninfo_send_struct(mavlink_channel_t chan, const mavlink_appmotioninfo_t* appmotioninfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appmotioninfo_send(chan, appmotioninfo->Position_demand_value, appmotioninfo->Position_actual_value_inc, appmotioninfo->Position_actual_value, appmotioninfo->Following_error_actual_value, appmotioninfo->Velocity_demand_value, appmotioninfo->Velocity_actual_value, appmotioninfo->Torque_demand_value, appmotioninfo->Torque_actual_value, appmotioninfo->Current_actual_value, appmotioninfo->D_current_actual_value, appmotioninfo->U_current_actual_value, appmotioninfo->V_current_actual_value, appmotioninfo->W_current_actual_value, appmotioninfo->Motor_position_demand_value, appmotioninfo->Motor_position_actual_value, appmotioninfo->Motor_following_error_actual_value, appmotioninfo->Motor_velocity_demand_value, appmotioninfo->Motor_velocity_actual_value, appmotioninfo->U_adc_mid_val, appmotioninfo->V_adc_mid_val, appmotioninfo->W_adc_mid_val, appmotioninfo->Current_loop_time, appmotioninfo->Position_loop_time, appmotioninfo->Current_loop_cycle, appmotioninfo->Position_loop_cycle);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionInfo, (const char *)appmotioninfo, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN, MAVLINK_MSG_ID_AppMotionInfo_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppMotionInfo_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appmotioninfo_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t Position_demand_value, int64_t Position_actual_value_inc, int64_t Position_actual_value, int64_t Following_error_actual_value, float Velocity_demand_value, float Velocity_actual_value, float Torque_demand_value, float Torque_actual_value, float Current_actual_value, float D_current_actual_value, float U_current_actual_value, float V_current_actual_value, float W_current_actual_value, int64_t Motor_position_demand_value, int64_t Motor_position_actual_value, int64_t Motor_following_error_actual_value, float Motor_velocity_demand_value, float Motor_velocity_actual_value, uint16_t U_adc_mid_val, uint16_t V_adc_mid_val, uint16_t W_adc_mid_val, float Current_loop_time, float Position_loop_time, float Current_loop_cycle, float Position_loop_cycle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, Position_demand_value);
    _mav_put_int64_t(buf, 8, Position_actual_value_inc);
    _mav_put_int64_t(buf, 16, Position_actual_value);
    _mav_put_int64_t(buf, 24, Following_error_actual_value);
    _mav_put_int64_t(buf, 32, Motor_position_demand_value);
    _mav_put_int64_t(buf, 40, Motor_position_actual_value);
    _mav_put_int64_t(buf, 48, Motor_following_error_actual_value);
    _mav_put_float(buf, 56, Velocity_demand_value);
    _mav_put_float(buf, 60, Velocity_actual_value);
    _mav_put_float(buf, 64, Torque_demand_value);
    _mav_put_float(buf, 68, Torque_actual_value);
    _mav_put_float(buf, 72, Current_actual_value);
    _mav_put_float(buf, 76, D_current_actual_value);
    _mav_put_float(buf, 80, U_current_actual_value);
    _mav_put_float(buf, 84, V_current_actual_value);
    _mav_put_float(buf, 88, W_current_actual_value);
    _mav_put_float(buf, 92, Motor_velocity_demand_value);
    _mav_put_float(buf, 96, Motor_velocity_actual_value);
    _mav_put_float(buf, 100, Current_loop_time);
    _mav_put_float(buf, 104, Position_loop_time);
    _mav_put_float(buf, 108, Current_loop_cycle);
    _mav_put_float(buf, 112, Position_loop_cycle);
    _mav_put_uint16_t(buf, 116, U_adc_mid_val);
    _mav_put_uint16_t(buf, 118, V_adc_mid_val);
    _mav_put_uint16_t(buf, 120, W_adc_mid_val);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionInfo, buf, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN, MAVLINK_MSG_ID_AppMotionInfo_CRC);
#else
    mavlink_appmotioninfo_t *packet = (mavlink_appmotioninfo_t *)msgbuf;
    packet->Position_demand_value = Position_demand_value;
    packet->Position_actual_value_inc = Position_actual_value_inc;
    packet->Position_actual_value = Position_actual_value;
    packet->Following_error_actual_value = Following_error_actual_value;
    packet->Motor_position_demand_value = Motor_position_demand_value;
    packet->Motor_position_actual_value = Motor_position_actual_value;
    packet->Motor_following_error_actual_value = Motor_following_error_actual_value;
    packet->Velocity_demand_value = Velocity_demand_value;
    packet->Velocity_actual_value = Velocity_actual_value;
    packet->Torque_demand_value = Torque_demand_value;
    packet->Torque_actual_value = Torque_actual_value;
    packet->Current_actual_value = Current_actual_value;
    packet->D_current_actual_value = D_current_actual_value;
    packet->U_current_actual_value = U_current_actual_value;
    packet->V_current_actual_value = V_current_actual_value;
    packet->W_current_actual_value = W_current_actual_value;
    packet->Motor_velocity_demand_value = Motor_velocity_demand_value;
    packet->Motor_velocity_actual_value = Motor_velocity_actual_value;
    packet->Current_loop_time = Current_loop_time;
    packet->Position_loop_time = Position_loop_time;
    packet->Current_loop_cycle = Current_loop_cycle;
    packet->Position_loop_cycle = Position_loop_cycle;
    packet->U_adc_mid_val = U_adc_mid_val;
    packet->V_adc_mid_val = V_adc_mid_val;
    packet->W_adc_mid_val = W_adc_mid_val;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionInfo, (const char *)packet, MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN, MAVLINK_MSG_ID_AppMotionInfo_LEN, MAVLINK_MSG_ID_AppMotionInfo_CRC);
#endif
}
#endif

#endif

// MESSAGE AppMotionInfo UNPACKING


/**
 * @brief Get field Position_demand_value from appmotioninfo message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotioninfo_get_Position_demand_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field Position_actual_value_inc from appmotioninfo message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotioninfo_get_Position_actual_value_inc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Get field Position_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotioninfo_get_Position_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  16);
}

/**
 * @brief Get field Following_error_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotioninfo_get_Following_error_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  24);
}

/**
 * @brief Get field Velocity_demand_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Velocity_demand_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field Velocity_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Velocity_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field Torque_demand_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Torque_demand_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field Torque_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Torque_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field Current_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Current_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field D_current_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_D_current_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field U_current_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_U_current_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  80);
}

/**
 * @brief Get field V_current_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_V_current_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  84);
}

/**
 * @brief Get field W_current_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_W_current_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  88);
}

/**
 * @brief Get field Motor_position_demand_value from appmotioninfo message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotioninfo_get_Motor_position_demand_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  32);
}

/**
 * @brief Get field Motor_position_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotioninfo_get_Motor_position_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  40);
}

/**
 * @brief Get field Motor_following_error_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotioninfo_get_Motor_following_error_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  48);
}

/**
 * @brief Get field Motor_velocity_demand_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Motor_velocity_demand_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  92);
}

/**
 * @brief Get field Motor_velocity_actual_value from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Motor_velocity_actual_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  96);
}

/**
 * @brief Get field U_adc_mid_val from appmotioninfo message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appmotioninfo_get_U_adc_mid_val(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  116);
}

/**
 * @brief Get field V_adc_mid_val from appmotioninfo message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appmotioninfo_get_V_adc_mid_val(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  118);
}

/**
 * @brief Get field W_adc_mid_val from appmotioninfo message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appmotioninfo_get_W_adc_mid_val(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  120);
}

/**
 * @brief Get field Current_loop_time from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Current_loop_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  100);
}

/**
 * @brief Get field Position_loop_time from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Position_loop_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  104);
}

/**
 * @brief Get field Current_loop_cycle from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Current_loop_cycle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  108);
}

/**
 * @brief Get field Position_loop_cycle from appmotioninfo message
 *
 * @return  
 */
static inline float mavlink_msg_appmotioninfo_get_Position_loop_cycle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  112);
}

/**
 * @brief Decode a appmotioninfo message into a struct
 *
 * @param msg The message to decode
 * @param appmotioninfo C-struct to decode the message contents into
 */
static inline void mavlink_msg_appmotioninfo_decode(const mavlink_message_t* msg, mavlink_appmotioninfo_t* appmotioninfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appmotioninfo->Position_demand_value = mavlink_msg_appmotioninfo_get_Position_demand_value(msg);
    appmotioninfo->Position_actual_value_inc = mavlink_msg_appmotioninfo_get_Position_actual_value_inc(msg);
    appmotioninfo->Position_actual_value = mavlink_msg_appmotioninfo_get_Position_actual_value(msg);
    appmotioninfo->Following_error_actual_value = mavlink_msg_appmotioninfo_get_Following_error_actual_value(msg);
    appmotioninfo->Motor_position_demand_value = mavlink_msg_appmotioninfo_get_Motor_position_demand_value(msg);
    appmotioninfo->Motor_position_actual_value = mavlink_msg_appmotioninfo_get_Motor_position_actual_value(msg);
    appmotioninfo->Motor_following_error_actual_value = mavlink_msg_appmotioninfo_get_Motor_following_error_actual_value(msg);
    appmotioninfo->Velocity_demand_value = mavlink_msg_appmotioninfo_get_Velocity_demand_value(msg);
    appmotioninfo->Velocity_actual_value = mavlink_msg_appmotioninfo_get_Velocity_actual_value(msg);
    appmotioninfo->Torque_demand_value = mavlink_msg_appmotioninfo_get_Torque_demand_value(msg);
    appmotioninfo->Torque_actual_value = mavlink_msg_appmotioninfo_get_Torque_actual_value(msg);
    appmotioninfo->Current_actual_value = mavlink_msg_appmotioninfo_get_Current_actual_value(msg);
    appmotioninfo->D_current_actual_value = mavlink_msg_appmotioninfo_get_D_current_actual_value(msg);
    appmotioninfo->U_current_actual_value = mavlink_msg_appmotioninfo_get_U_current_actual_value(msg);
    appmotioninfo->V_current_actual_value = mavlink_msg_appmotioninfo_get_V_current_actual_value(msg);
    appmotioninfo->W_current_actual_value = mavlink_msg_appmotioninfo_get_W_current_actual_value(msg);
    appmotioninfo->Motor_velocity_demand_value = mavlink_msg_appmotioninfo_get_Motor_velocity_demand_value(msg);
    appmotioninfo->Motor_velocity_actual_value = mavlink_msg_appmotioninfo_get_Motor_velocity_actual_value(msg);
    appmotioninfo->Current_loop_time = mavlink_msg_appmotioninfo_get_Current_loop_time(msg);
    appmotioninfo->Position_loop_time = mavlink_msg_appmotioninfo_get_Position_loop_time(msg);
    appmotioninfo->Current_loop_cycle = mavlink_msg_appmotioninfo_get_Current_loop_cycle(msg);
    appmotioninfo->Position_loop_cycle = mavlink_msg_appmotioninfo_get_Position_loop_cycle(msg);
    appmotioninfo->U_adc_mid_val = mavlink_msg_appmotioninfo_get_U_adc_mid_val(msg);
    appmotioninfo->V_adc_mid_val = mavlink_msg_appmotioninfo_get_V_adc_mid_val(msg);
    appmotioninfo->W_adc_mid_val = mavlink_msg_appmotioninfo_get_W_adc_mid_val(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppMotionInfo_LEN? msg->len : MAVLINK_MSG_ID_AppMotionInfo_LEN;
        memset(appmotioninfo, 0, MAVLINK_MSG_ID_AppMotionInfo_LEN);
    memcpy(appmotioninfo, _MAV_PAYLOAD(msg), len);
#endif
}
