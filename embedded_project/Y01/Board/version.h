#ifndef VERSION_H
#define VERSION_H

#ifdef __cplusplus
extern "C"
{
#endif

// 次版本号定义
#define V_CAN_CIA402            (0x00)  // 0：CAN CiA402 协议版本
#define V_CAN_ENCOS             (0x01)  // 1：CAN ENCOS 协议版本
#define V_CANOPEN_CIA402        (0x02)  // 2：CANopen CiA402 协议版本
#define V_ECAT_CIA402           (0x03)  // 3：EtherCAT CiA402 协议版本
#define V_CANFD_CUSTOM          (0x04)  // 4：CANFD 自定义协议版本

// 版本定义
#define MAJOR_VERSION           (0x02)              // 主版本号
#define MINOR_VERSION           (V_CANOPEN_CIA402)      // 次版本号
#define REVISION_VERSION        (0x02)              // 修订号
#define BUILD_VERSION           (0x02)              // 构建号
#define VERSION_ENCODE (((MAJOR_VERSION) << 24) | ((MINOR_VERSION) << 16) | ((REVISION_VERSION) << 8) | (BUILD_VERSION))

#if MINOR_VERSION == V_CAN_CIA402
#define USE_CAN
#define USE_CIA402
#endif

#if MINOR_VERSION == V_CAN_ENCOS
#define USE_CAN
#define USE_ENCOS
#endif

#if MINOR_VERSION == V_CANOPEN_CIA402
#define USE_CAN
#define USE_CANOPEN
#define USE_CIA402
#endif

#if MINOR_VERSION == V_ECAT_CIA402
#define USE_ECAT
#define USE_CIA402
#endif

#if MINOR_VERSION == V_CANFD_CUSTOM
#define USE_CAN
#define USE_CUSTOM
#endif


#ifdef __cplusplus
}
#endif

#endif // VERSION_H
