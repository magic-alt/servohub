#pragma once
// MESSAGE TqFcIdConfig PACKING

#define MAVLINK_MSG_ID_TqFcIdConfig 30047


typedef struct __mavlink_tqfcidconfig_t {
 uint32_t enc_line_p_n; /*<  */
} mavlink_tqfcidconfig_t;

#define MAVLINK_MSG_ID_TqFcIdConfig_LEN 4
#define MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN 4
#define MAVLINK_MSG_ID_30047_LEN 4
#define MAVLINK_MSG_ID_30047_MIN_LEN 4

#define MAVLINK_MSG_ID_TqFcIdConfig_CRC 151
#define MAVLINK_MSG_ID_30047_CRC 151



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TqFcIdConfig { \
    30047, \
    "TqFcIdConfig", \
    1, \
    {  { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_tqfcidconfig_t, enc_line_p_n) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TqFcIdConfig { \
    "TqFcIdConfig", \
    1, \
    {  { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_tqfcidconfig_t, enc_line_p_n) }, \
         } \
}
#endif

/**
 * @brief Pack a tqfcidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_line_p_n  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t enc_line_p_n)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdConfig_LEN];
    _mav_put_uint32_t(buf, 0, enc_line_p_n);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdConfig_LEN);
#else
    mavlink_tqfcidconfig_t packet;
    packet.enc_line_p_n = enc_line_p_n;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN, MAVLINK_MSG_ID_TqFcIdConfig_CRC);
}

/**
 * @brief Pack a tqfcidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_line_p_n  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t enc_line_p_n)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdConfig_LEN];
    _mav_put_uint32_t(buf, 0, enc_line_p_n);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdConfig_LEN);
#else
    mavlink_tqfcidconfig_t packet;
    packet.enc_line_p_n = enc_line_p_n;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN, MAVLINK_MSG_ID_TqFcIdConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN);
#endif
}

/**
 * @brief Pack a tqfcidconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_line_p_n  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t enc_line_p_n)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdConfig_LEN];
    _mav_put_uint32_t(buf, 0, enc_line_p_n);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdConfig_LEN);
#else
    mavlink_tqfcidconfig_t packet;
    packet.enc_line_p_n = enc_line_p_n;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN, MAVLINK_MSG_ID_TqFcIdConfig_CRC);
}

/**
 * @brief Encode a tqfcidconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tqfcidconfig_t* tqfcidconfig)
{
    return mavlink_msg_tqfcidconfig_pack(system_id, component_id, msg, tqfcidconfig->enc_line_p_n);
}

/**
 * @brief Encode a tqfcidconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tqfcidconfig_t* tqfcidconfig)
{
    return mavlink_msg_tqfcidconfig_pack_chan(system_id, component_id, chan, msg, tqfcidconfig->enc_line_p_n);
}

/**
 * @brief Encode a tqfcidconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_tqfcidconfig_t* tqfcidconfig)
{
    return mavlink_msg_tqfcidconfig_pack_status(system_id, component_id, _status, msg,  tqfcidconfig->enc_line_p_n);
}

/**
 * @brief Send a tqfcidconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_line_p_n  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tqfcidconfig_send(mavlink_channel_t chan, uint32_t enc_line_p_n)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdConfig_LEN];
    _mav_put_uint32_t(buf, 0, enc_line_p_n);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdConfig, buf, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN, MAVLINK_MSG_ID_TqFcIdConfig_CRC);
#else
    mavlink_tqfcidconfig_t packet;
    packet.enc_line_p_n = enc_line_p_n;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdConfig, (const char *)&packet, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN, MAVLINK_MSG_ID_TqFcIdConfig_CRC);
#endif
}

/**
 * @brief Send a tqfcidconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tqfcidconfig_send_struct(mavlink_channel_t chan, const mavlink_tqfcidconfig_t* tqfcidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tqfcidconfig_send(chan, tqfcidconfig->enc_line_p_n);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdConfig, (const char *)tqfcidconfig, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN, MAVLINK_MSG_ID_TqFcIdConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_TqFcIdConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tqfcidconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t enc_line_p_n)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, enc_line_p_n);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdConfig, buf, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN, MAVLINK_MSG_ID_TqFcIdConfig_CRC);
#else
    mavlink_tqfcidconfig_t *packet = (mavlink_tqfcidconfig_t *)msgbuf;
    packet->enc_line_p_n = enc_line_p_n;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdConfig, (const char *)packet, MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN, MAVLINK_MSG_ID_TqFcIdConfig_LEN, MAVLINK_MSG_ID_TqFcIdConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE TqFcIdConfig UNPACKING


/**
 * @brief Get field enc_line_p_n from tqfcidconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_tqfcidconfig_get_enc_line_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a tqfcidconfig message into a struct
 *
 * @param msg The message to decode
 * @param tqfcidconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_tqfcidconfig_decode(const mavlink_message_t* msg, mavlink_tqfcidconfig_t* tqfcidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tqfcidconfig->enc_line_p_n = mavlink_msg_tqfcidconfig_get_enc_line_p_n(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TqFcIdConfig_LEN? msg->len : MAVLINK_MSG_ID_TqFcIdConfig_LEN;
        memset(tqfcidconfig, 0, MAVLINK_MSG_ID_TqFcIdConfig_LEN);
    memcpy(tqfcidconfig, _MAV_PAYLOAD(msg), len);
#endif
}
