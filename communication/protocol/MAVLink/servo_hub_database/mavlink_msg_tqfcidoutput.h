#pragma once
// MESSAGE TqFcIdOutput PACKING

#define MAVLINK_MSG_ID_TqFcIdOutput 30048


typedef struct __mavlink_tqfcidoutput_t {
 int64_t pos_cmd_p; /*<  */
 uint8_t iq_com_enable; /*<  */
 uint8_t tq_com_enable; /*<  */
 uint8_t fc_com_enable; /*<  */
 int8_t state_now; /*<  */
} mavlink_tqfcidoutput_t;

#define MAVLINK_MSG_ID_TqFcIdOutput_LEN 12
#define MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN 12
#define MAVLINK_MSG_ID_30048_LEN 12
#define MAVLINK_MSG_ID_30048_MIN_LEN 12

#define MAVLINK_MSG_ID_TqFcIdOutput_CRC 116
#define MAVLINK_MSG_ID_30048_CRC 116



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TqFcIdOutput { \
    30048, \
    "TqFcIdOutput", \
    5, \
    {  { "pos_cmd_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_tqfcidoutput_t, pos_cmd_p) }, \
         { "iq_com_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_tqfcidoutput_t, iq_com_enable) }, \
         { "tq_com_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_tqfcidoutput_t, tq_com_enable) }, \
         { "fc_com_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_tqfcidoutput_t, fc_com_enable) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 11, offsetof(mavlink_tqfcidoutput_t, state_now) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TqFcIdOutput { \
    "TqFcIdOutput", \
    5, \
    {  { "pos_cmd_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_tqfcidoutput_t, pos_cmd_p) }, \
         { "iq_com_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_tqfcidoutput_t, iq_com_enable) }, \
         { "tq_com_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_tqfcidoutput_t, tq_com_enable) }, \
         { "fc_com_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_tqfcidoutput_t, fc_com_enable) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 11, offsetof(mavlink_tqfcidoutput_t, state_now) }, \
         } \
}
#endif

/**
 * @brief Pack a tqfcidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_cmd_p  
 * @param iq_com_enable  
 * @param tq_com_enable  
 * @param fc_com_enable  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t pos_cmd_p, uint8_t iq_com_enable, uint8_t tq_com_enable, uint8_t fc_com_enable, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_uint8_t(buf, 8, iq_com_enable);
    _mav_put_uint8_t(buf, 9, tq_com_enable);
    _mav_put_uint8_t(buf, 10, fc_com_enable);
    _mav_put_int8_t(buf, 11, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdOutput_LEN);
#else
    mavlink_tqfcidoutput_t packet;
    packet.pos_cmd_p = pos_cmd_p;
    packet.iq_com_enable = iq_com_enable;
    packet.tq_com_enable = tq_com_enable;
    packet.fc_com_enable = fc_com_enable;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN, MAVLINK_MSG_ID_TqFcIdOutput_CRC);
}

/**
 * @brief Pack a tqfcidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_cmd_p  
 * @param iq_com_enable  
 * @param tq_com_enable  
 * @param fc_com_enable  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t pos_cmd_p, uint8_t iq_com_enable, uint8_t tq_com_enable, uint8_t fc_com_enable, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_uint8_t(buf, 8, iq_com_enable);
    _mav_put_uint8_t(buf, 9, tq_com_enable);
    _mav_put_uint8_t(buf, 10, fc_com_enable);
    _mav_put_int8_t(buf, 11, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdOutput_LEN);
#else
    mavlink_tqfcidoutput_t packet;
    packet.pos_cmd_p = pos_cmd_p;
    packet.iq_com_enable = iq_com_enable;
    packet.tq_com_enable = tq_com_enable;
    packet.fc_com_enable = fc_com_enable;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN, MAVLINK_MSG_ID_TqFcIdOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN);
#endif
}

/**
 * @brief Pack a tqfcidoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_cmd_p  
 * @param iq_com_enable  
 * @param tq_com_enable  
 * @param fc_com_enable  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t pos_cmd_p,uint8_t iq_com_enable,uint8_t tq_com_enable,uint8_t fc_com_enable,int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_uint8_t(buf, 8, iq_com_enable);
    _mav_put_uint8_t(buf, 9, tq_com_enable);
    _mav_put_uint8_t(buf, 10, fc_com_enable);
    _mav_put_int8_t(buf, 11, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdOutput_LEN);
#else
    mavlink_tqfcidoutput_t packet;
    packet.pos_cmd_p = pos_cmd_p;
    packet.iq_com_enable = iq_com_enable;
    packet.tq_com_enable = tq_com_enable;
    packet.fc_com_enable = fc_com_enable;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN, MAVLINK_MSG_ID_TqFcIdOutput_CRC);
}

/**
 * @brief Encode a tqfcidoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tqfcidoutput_t* tqfcidoutput)
{
    return mavlink_msg_tqfcidoutput_pack(system_id, component_id, msg, tqfcidoutput->pos_cmd_p, tqfcidoutput->iq_com_enable, tqfcidoutput->tq_com_enable, tqfcidoutput->fc_com_enable, tqfcidoutput->state_now);
}

/**
 * @brief Encode a tqfcidoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tqfcidoutput_t* tqfcidoutput)
{
    return mavlink_msg_tqfcidoutput_pack_chan(system_id, component_id, chan, msg, tqfcidoutput->pos_cmd_p, tqfcidoutput->iq_com_enable, tqfcidoutput->tq_com_enable, tqfcidoutput->fc_com_enable, tqfcidoutput->state_now);
}

/**
 * @brief Encode a tqfcidoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_tqfcidoutput_t* tqfcidoutput)
{
    return mavlink_msg_tqfcidoutput_pack_status(system_id, component_id, _status, msg,  tqfcidoutput->pos_cmd_p, tqfcidoutput->iq_com_enable, tqfcidoutput->tq_com_enable, tqfcidoutput->fc_com_enable, tqfcidoutput->state_now);
}

/**
 * @brief Send a tqfcidoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_cmd_p  
 * @param iq_com_enable  
 * @param tq_com_enable  
 * @param fc_com_enable  
 * @param state_now  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tqfcidoutput_send(mavlink_channel_t chan, int64_t pos_cmd_p, uint8_t iq_com_enable, uint8_t tq_com_enable, uint8_t fc_com_enable, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_uint8_t(buf, 8, iq_com_enable);
    _mav_put_uint8_t(buf, 9, tq_com_enable);
    _mav_put_uint8_t(buf, 10, fc_com_enable);
    _mav_put_int8_t(buf, 11, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdOutput, buf, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN, MAVLINK_MSG_ID_TqFcIdOutput_CRC);
#else
    mavlink_tqfcidoutput_t packet;
    packet.pos_cmd_p = pos_cmd_p;
    packet.iq_com_enable = iq_com_enable;
    packet.tq_com_enable = tq_com_enable;
    packet.fc_com_enable = fc_com_enable;
    packet.state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdOutput, (const char *)&packet, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN, MAVLINK_MSG_ID_TqFcIdOutput_CRC);
#endif
}

/**
 * @brief Send a tqfcidoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tqfcidoutput_send_struct(mavlink_channel_t chan, const mavlink_tqfcidoutput_t* tqfcidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tqfcidoutput_send(chan, tqfcidoutput->pos_cmd_p, tqfcidoutput->iq_com_enable, tqfcidoutput->tq_com_enable, tqfcidoutput->fc_com_enable, tqfcidoutput->state_now);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdOutput, (const char *)tqfcidoutput, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN, MAVLINK_MSG_ID_TqFcIdOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_TqFcIdOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tqfcidoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t pos_cmd_p, uint8_t iq_com_enable, uint8_t tq_com_enable, uint8_t fc_com_enable, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_uint8_t(buf, 8, iq_com_enable);
    _mav_put_uint8_t(buf, 9, tq_com_enable);
    _mav_put_uint8_t(buf, 10, fc_com_enable);
    _mav_put_int8_t(buf, 11, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdOutput, buf, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN, MAVLINK_MSG_ID_TqFcIdOutput_CRC);
#else
    mavlink_tqfcidoutput_t *packet = (mavlink_tqfcidoutput_t *)msgbuf;
    packet->pos_cmd_p = pos_cmd_p;
    packet->iq_com_enable = iq_com_enable;
    packet->tq_com_enable = tq_com_enable;
    packet->fc_com_enable = fc_com_enable;
    packet->state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdOutput, (const char *)packet, MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdOutput_LEN, MAVLINK_MSG_ID_TqFcIdOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE TqFcIdOutput UNPACKING


/**
 * @brief Get field pos_cmd_p from tqfcidoutput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_tqfcidoutput_get_pos_cmd_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field iq_com_enable from tqfcidoutput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_tqfcidoutput_get_iq_com_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field tq_com_enable from tqfcidoutput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_tqfcidoutput_get_tq_com_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field fc_com_enable from tqfcidoutput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_tqfcidoutput_get_fc_com_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field state_now from tqfcidoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_tqfcidoutput_get_state_now(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  11);
}

/**
 * @brief Decode a tqfcidoutput message into a struct
 *
 * @param msg The message to decode
 * @param tqfcidoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_tqfcidoutput_decode(const mavlink_message_t* msg, mavlink_tqfcidoutput_t* tqfcidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tqfcidoutput->pos_cmd_p = mavlink_msg_tqfcidoutput_get_pos_cmd_p(msg);
    tqfcidoutput->iq_com_enable = mavlink_msg_tqfcidoutput_get_iq_com_enable(msg);
    tqfcidoutput->tq_com_enable = mavlink_msg_tqfcidoutput_get_tq_com_enable(msg);
    tqfcidoutput->fc_com_enable = mavlink_msg_tqfcidoutput_get_fc_com_enable(msg);
    tqfcidoutput->state_now = mavlink_msg_tqfcidoutput_get_state_now(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TqFcIdOutput_LEN? msg->len : MAVLINK_MSG_ID_TqFcIdOutput_LEN;
        memset(tqfcidoutput, 0, MAVLINK_MSG_ID_TqFcIdOutput_LEN);
    memcpy(tqfcidoutput, _MAV_PAYLOAD(msg), len);
#endif
}
