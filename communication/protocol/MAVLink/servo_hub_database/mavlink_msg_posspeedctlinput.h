#pragma once
// MESSAGE PosSpeedCtlInput PACKING

#define MAVLINK_MSG_ID_PosSpeedCtlInput 30019


typedef struct __mavlink_posspeedctlinput_t {
 int64_t pos_tar_p; /*<  */
 int64_t pos_now_p; /*<  */
 float iq_max_A; /*<  */
 float speed_tar_p_s; /*<  */
 float acc_tar_p_ss; /*<  */
 float speed_now_rad_s; /*<  */
} mavlink_posspeedctlinput_t;

#define MAVLINK_MSG_ID_PosSpeedCtlInput_LEN 32
#define MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN 32
#define MAVLINK_MSG_ID_30019_LEN 32
#define MAVLINK_MSG_ID_30019_MIN_LEN 32

#define MAVLINK_MSG_ID_PosSpeedCtlInput_CRC 220
#define MAVLINK_MSG_ID_30019_CRC 220



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PosSpeedCtlInput { \
    30019, \
    "PosSpeedCtlInput", \
    6, \
    {  { "pos_tar_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_posspeedctlinput_t, pos_tar_p) }, \
         { "pos_now_p", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_posspeedctlinput_t, pos_now_p) }, \
         { "iq_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_posspeedctlinput_t, iq_max_A) }, \
         { "speed_tar_p_s", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_posspeedctlinput_t, speed_tar_p_s) }, \
         { "acc_tar_p_ss", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_posspeedctlinput_t, acc_tar_p_ss) }, \
         { "speed_now_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_posspeedctlinput_t, speed_now_rad_s) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PosSpeedCtlInput { \
    "PosSpeedCtlInput", \
    6, \
    {  { "pos_tar_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_posspeedctlinput_t, pos_tar_p) }, \
         { "pos_now_p", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_posspeedctlinput_t, pos_now_p) }, \
         { "iq_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_posspeedctlinput_t, iq_max_A) }, \
         { "speed_tar_p_s", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_posspeedctlinput_t, speed_tar_p_s) }, \
         { "acc_tar_p_ss", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_posspeedctlinput_t, acc_tar_p_ss) }, \
         { "speed_now_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_posspeedctlinput_t, speed_now_rad_s) }, \
         } \
}
#endif

/**
 * @brief Pack a posspeedctlinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_tar_p  
 * @param pos_now_p  
 * @param iq_max_A  
 * @param speed_tar_p_s  
 * @param acc_tar_p_ss  
 * @param speed_now_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctlinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t pos_tar_p, int64_t pos_now_p, float iq_max_A, float speed_tar_p_s, float acc_tar_p_ss, float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlInput_LEN];
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_int64_t(buf, 8, pos_now_p);
    _mav_put_float(buf, 16, iq_max_A);
    _mav_put_float(buf, 20, speed_tar_p_s);
    _mav_put_float(buf, 24, acc_tar_p_ss);
    _mav_put_float(buf, 28, speed_now_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN);
#else
    mavlink_posspeedctlinput_t packet;
    packet.pos_tar_p = pos_tar_p;
    packet.pos_now_p = pos_now_p;
    packet.iq_max_A = iq_max_A;
    packet.speed_tar_p_s = speed_tar_p_s;
    packet.acc_tar_p_ss = acc_tar_p_ss;
    packet.speed_now_rad_s = speed_now_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_CRC);
}

/**
 * @brief Pack a posspeedctlinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_tar_p  
 * @param pos_now_p  
 * @param iq_max_A  
 * @param speed_tar_p_s  
 * @param acc_tar_p_ss  
 * @param speed_now_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctlinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t pos_tar_p, int64_t pos_now_p, float iq_max_A, float speed_tar_p_s, float acc_tar_p_ss, float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlInput_LEN];
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_int64_t(buf, 8, pos_now_p);
    _mav_put_float(buf, 16, iq_max_A);
    _mav_put_float(buf, 20, speed_tar_p_s);
    _mav_put_float(buf, 24, acc_tar_p_ss);
    _mav_put_float(buf, 28, speed_now_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN);
#else
    mavlink_posspeedctlinput_t packet;
    packet.pos_tar_p = pos_tar_p;
    packet.pos_now_p = pos_now_p;
    packet.iq_max_A = iq_max_A;
    packet.speed_tar_p_s = speed_tar_p_s;
    packet.acc_tar_p_ss = acc_tar_p_ss;
    packet.speed_now_rad_s = speed_now_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN);
#endif
}

/**
 * @brief Pack a posspeedctlinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_tar_p  
 * @param pos_now_p  
 * @param iq_max_A  
 * @param speed_tar_p_s  
 * @param acc_tar_p_ss  
 * @param speed_now_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctlinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t pos_tar_p,int64_t pos_now_p,float iq_max_A,float speed_tar_p_s,float acc_tar_p_ss,float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlInput_LEN];
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_int64_t(buf, 8, pos_now_p);
    _mav_put_float(buf, 16, iq_max_A);
    _mav_put_float(buf, 20, speed_tar_p_s);
    _mav_put_float(buf, 24, acc_tar_p_ss);
    _mav_put_float(buf, 28, speed_now_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN);
#else
    mavlink_posspeedctlinput_t packet;
    packet.pos_tar_p = pos_tar_p;
    packet.pos_now_p = pos_now_p;
    packet.iq_max_A = iq_max_A;
    packet.speed_tar_p_s = speed_tar_p_s;
    packet.acc_tar_p_ss = acc_tar_p_ss;
    packet.speed_now_rad_s = speed_now_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_CRC);
}

/**
 * @brief Encode a posspeedctlinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctlinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctlinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_posspeedctlinput_t* posspeedctlinput)
{
    return mavlink_msg_posspeedctlinput_pack(system_id, component_id, msg, posspeedctlinput->pos_tar_p, posspeedctlinput->pos_now_p, posspeedctlinput->iq_max_A, posspeedctlinput->speed_tar_p_s, posspeedctlinput->acc_tar_p_ss, posspeedctlinput->speed_now_rad_s);
}

/**
 * @brief Encode a posspeedctlinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctlinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctlinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_posspeedctlinput_t* posspeedctlinput)
{
    return mavlink_msg_posspeedctlinput_pack_chan(system_id, component_id, chan, msg, posspeedctlinput->pos_tar_p, posspeedctlinput->pos_now_p, posspeedctlinput->iq_max_A, posspeedctlinput->speed_tar_p_s, posspeedctlinput->acc_tar_p_ss, posspeedctlinput->speed_now_rad_s);
}

/**
 * @brief Encode a posspeedctlinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctlinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctlinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_posspeedctlinput_t* posspeedctlinput)
{
    return mavlink_msg_posspeedctlinput_pack_status(system_id, component_id, _status, msg,  posspeedctlinput->pos_tar_p, posspeedctlinput->pos_now_p, posspeedctlinput->iq_max_A, posspeedctlinput->speed_tar_p_s, posspeedctlinput->acc_tar_p_ss, posspeedctlinput->speed_now_rad_s);
}

/**
 * @brief Send a posspeedctlinput message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_tar_p  
 * @param pos_now_p  
 * @param iq_max_A  
 * @param speed_tar_p_s  
 * @param acc_tar_p_ss  
 * @param speed_now_rad_s  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_posspeedctlinput_send(mavlink_channel_t chan, int64_t pos_tar_p, int64_t pos_now_p, float iq_max_A, float speed_tar_p_s, float acc_tar_p_ss, float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlInput_LEN];
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_int64_t(buf, 8, pos_now_p);
    _mav_put_float(buf, 16, iq_max_A);
    _mav_put_float(buf, 20, speed_tar_p_s);
    _mav_put_float(buf, 24, acc_tar_p_ss);
    _mav_put_float(buf, 28, speed_now_rad_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlInput, buf, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_CRC);
#else
    mavlink_posspeedctlinput_t packet;
    packet.pos_tar_p = pos_tar_p;
    packet.pos_now_p = pos_now_p;
    packet.iq_max_A = iq_max_A;
    packet.speed_tar_p_s = speed_tar_p_s;
    packet.acc_tar_p_ss = acc_tar_p_ss;
    packet.speed_now_rad_s = speed_now_rad_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlInput, (const char *)&packet, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_CRC);
#endif
}

/**
 * @brief Send a posspeedctlinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_posspeedctlinput_send_struct(mavlink_channel_t chan, const mavlink_posspeedctlinput_t* posspeedctlinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_posspeedctlinput_send(chan, posspeedctlinput->pos_tar_p, posspeedctlinput->pos_now_p, posspeedctlinput->iq_max_A, posspeedctlinput->speed_tar_p_s, posspeedctlinput->acc_tar_p_ss, posspeedctlinput->speed_now_rad_s);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlInput, (const char *)posspeedctlinput, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_PosSpeedCtlInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_posspeedctlinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t pos_tar_p, int64_t pos_now_p, float iq_max_A, float speed_tar_p_s, float acc_tar_p_ss, float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_int64_t(buf, 8, pos_now_p);
    _mav_put_float(buf, 16, iq_max_A);
    _mav_put_float(buf, 20, speed_tar_p_s);
    _mav_put_float(buf, 24, acc_tar_p_ss);
    _mav_put_float(buf, 28, speed_now_rad_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlInput, buf, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_CRC);
#else
    mavlink_posspeedctlinput_t *packet = (mavlink_posspeedctlinput_t *)msgbuf;
    packet->pos_tar_p = pos_tar_p;
    packet->pos_now_p = pos_now_p;
    packet->iq_max_A = iq_max_A;
    packet->speed_tar_p_s = speed_tar_p_s;
    packet->acc_tar_p_ss = acc_tar_p_ss;
    packet->speed_now_rad_s = speed_now_rad_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlInput, (const char *)packet, MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN, MAVLINK_MSG_ID_PosSpeedCtlInput_CRC);
#endif
}
#endif

#endif

// MESSAGE PosSpeedCtlInput UNPACKING


/**
 * @brief Get field pos_tar_p from posspeedctlinput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_posspeedctlinput_get_pos_tar_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field pos_now_p from posspeedctlinput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_posspeedctlinput_get_pos_now_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Get field iq_max_A from posspeedctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlinput_get_iq_max_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field speed_tar_p_s from posspeedctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlinput_get_speed_tar_p_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field acc_tar_p_ss from posspeedctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlinput_get_acc_tar_p_ss(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field speed_now_rad_s from posspeedctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlinput_get_speed_now_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Decode a posspeedctlinput message into a struct
 *
 * @param msg The message to decode
 * @param posspeedctlinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_posspeedctlinput_decode(const mavlink_message_t* msg, mavlink_posspeedctlinput_t* posspeedctlinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    posspeedctlinput->pos_tar_p = mavlink_msg_posspeedctlinput_get_pos_tar_p(msg);
    posspeedctlinput->pos_now_p = mavlink_msg_posspeedctlinput_get_pos_now_p(msg);
    posspeedctlinput->iq_max_A = mavlink_msg_posspeedctlinput_get_iq_max_A(msg);
    posspeedctlinput->speed_tar_p_s = mavlink_msg_posspeedctlinput_get_speed_tar_p_s(msg);
    posspeedctlinput->acc_tar_p_ss = mavlink_msg_posspeedctlinput_get_acc_tar_p_ss(msg);
    posspeedctlinput->speed_now_rad_s = mavlink_msg_posspeedctlinput_get_speed_now_rad_s(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PosSpeedCtlInput_LEN? msg->len : MAVLINK_MSG_ID_PosSpeedCtlInput_LEN;
        memset(posspeedctlinput, 0, MAVLINK_MSG_ID_PosSpeedCtlInput_LEN);
    memcpy(posspeedctlinput, _MAV_PAYLOAD(msg), len);
#endif
}
