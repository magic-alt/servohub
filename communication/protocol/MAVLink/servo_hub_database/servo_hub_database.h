/** @file
 *  @brief MAVLink comm protocol generated from servo_hub_database.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_SERVO_HUB_DATABASE_H
#define MAVLINK_SERVO_HUB_DATABASE_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_SERVO_HUB_DATABASE.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_SERVO_HUB_DATABASE_XML_HASH -3359420680733421460

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 60, 12, 21, 28, 5, 29, 4, 120, 4, 4, 16, 9, 8, 81, 40, 128, 48, 24, 32, 12, 46, 33, 2, 12, 49, 45, 32, 72, 8, 16, 4, 25, 18, 4, 8, 12, 10, 4, 21, 12, 8, 16, 13, 8, 10, 17, 4, 12, 8, 36, 17, 26, 20, 3, 41, 1, 19, 35, 81, 52, 122, 36, 52, 88, 32, 16, 4, 2, 1, 4, 13, 8, 2, 4, 2, 8, 1, 64, 16, 21, 80, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {0, 0, 0, 0, 0, 0, 0, 0, 0, 119, 118, 47, 180, 72, 99, 65, 247, 3, 4, 37, 152, 238, 107, 199, 108, 104, 78, 96, 220, 51, 109, 124, 152, 38, 121, 84, 58, 125, 30, 82, 244, 112, 25, 156, 232, 197, 103, 107, 88, 160, 88, 5, 20, 152, 246, 37, 151, 116, 34, 152, 103, 90, 154, 108, 89, 26, 15, 207, 102, 217, 164, 162, 239, 51, 17, 147, 53, 134, 169, 215, 27, 228, 245, 59, 207, 1, 45, 158, 79, 88, 135, 44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_SERVO_HUB_DATABASE

// ENUM DEFINITIONS



// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_read_param.h"
#include "./mavlink_msg_pmsmconfig.h"
#include "./mavlink_msg_elecidsininput.h"
#include "./mavlink_msg_elecidsinoutput.h"
#include "./mavlink_msg_elecidsinconfig.h"
#include "./mavlink_msg_mecidoutput.h"
#include "./mavlink_msg_mecidconfig.h"
#include "./mavlink_msg_notchfilterinput.h"
#include "./mavlink_msg_notchfilterinternal.h"
#include "./mavlink_msg_notchfilteroutput.h"
#include "./mavlink_msg_mecidinput.h"
#include "./mavlink_msg_inputshapinginput.h"
#include "./mavlink_msg_inputshapingconfig.h"
#include "./mavlink_msg_inputshapingoutput.h"
#include "./mavlink_msg_scopeconfig.h"
#include "./mavlink_msg_scopecontrol.h"
#include "./mavlink_msg_scopedata.h"
#include "./mavlink_msg_waveformdata.h"
#include "./mavlink_msg_waveformmap.h"
#include "./mavlink_msg_posspeedctlinput.h"
#include "./mavlink_msg_posspeedctloutput.h"
#include "./mavlink_msg_posspeedctlconfig.h"
#include "./mavlink_msg_motorctlsmconfig.h"
#include "./mavlink_msg_motorctlsminput.h"
#include "./mavlink_msg_motorctlsmoutput.h"
#include "./mavlink_msg_currentctlinput.h"
#include "./mavlink_msg_currentctlconfig.h"
#include "./mavlink_msg_currentctloutput.h"
#include "./mavlink_msg_notchfilterconfig.h"
#include "./mavlink_msg_speedobspllinput.h"
#include "./mavlink_msg_speedobspllconfig.h"
#include "./mavlink_msg_speedobsplloutput.h"
#include "./mavlink_msg_elecangleidconfig.h"
#include "./mavlink_msg_elecangleidoutput.h"
#include "./mavlink_msg_elecangleidinput.h"
#include "./mavlink_msg_directionidinput.h"
#include "./mavlink_msg_directionidconfig.h"
#include "./mavlink_msg_directionidoutput.h"
#include "./mavlink_msg_motorpossensorinput.h"
#include "./mavlink_msg_motorpossensorconfig.h"
#include "./mavlink_msg_motorpossensoroutput.h"
#include "./mavlink_msg_polepairsidinput.h"
#include "./mavlink_msg_polepairsidconfig.h"
#include "./mavlink_msg_polepairsidoutput.h"
#include "./mavlink_msg_nonvolatileparam.h"
#include "./mavlink_msg_systemconfig.h"
#include "./mavlink_msg_tqfcidinput.h"
#include "./mavlink_msg_tqfcidconfig.h"
#include "./mavlink_msg_tqfcidoutput.h"
#include "./mavlink_msg_objectdictionary.h"
#include "./mavlink_msg_reciprocalmotionconfig.h"
#include "./mavlink_msg_reciprocalmotionoutput.h"
#include "./mavlink_msg_referencesignalconfig.h"
#include "./mavlink_msg_referencesignaloutput.h"
#include "./mavlink_msg_appcontrolword.h"
#include "./mavlink_msg_appstatusinfo.h"
#include "./mavlink_msg_appopmode.h"
#include "./mavlink_msg_appencoderconfig.h"
#include "./mavlink_msg_appbaseconfig.h"
#include "./mavlink_msg_appmotionparam.h"
#include "./mavlink_msg_apprestrictparam.h"
#include "./mavlink_msg_appmotioninfo.h"
#include "./mavlink_msg_appwindowparam.h"
#include "./mavlink_msg_appmotorconfig.h"
#include "./mavlink_msg_appprotectconfig.h"
#include "./mavlink_msg_mitctlinput.h"
#include "./mavlink_msg_mitctlconfig.h"
#include "./mavlink_msg_mitctloutput.h"
#include "./mavlink_msg_apppermissionconfig.h"
#include "./mavlink_msg_systemcmd.h"
#include "./mavlink_msg_loadpossensorinput.h"
#include "./mavlink_msg_loadpossensorconfig.h"
#include "./mavlink_msg_loadpossensoroutput.h"
#include "./mavlink_msg_systemstatus.h"
#include "./mavlink_msg_encodercalibrationcmd.h"
#include "./mavlink_msg_encodercalibrationstatus.h"
#include "./mavlink_msg_custominfo.h"
#include "./mavlink_msg_heartbit.h"
#include "./mavlink_msg_historicalinfo.h"
#include "./mavlink_msg_simplantinput.h"
#include "./mavlink_msg_simplantoutput.h"
#include "./mavlink_msg_simplantconfig.h"
#include "./mavlink_msg_appdebugparam.h"

// base include



#if MAVLINK_SERVO_HUB_DATABASE_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {{"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_READ_PARAM, MAVLINK_MESSAGE_INFO_PmsmConfig, MAVLINK_MESSAGE_INFO_ElecIdSinInput, MAVLINK_MESSAGE_INFO_ElecIdSinOutput, MAVLINK_MESSAGE_INFO_ElecIdSinConfig, MAVLINK_MESSAGE_INFO_MecIdOutput, MAVLINK_MESSAGE_INFO_MecIdConfig, MAVLINK_MESSAGE_INFO_NotchFilterInput, MAVLINK_MESSAGE_INFO_NotchFilterInternal, MAVLINK_MESSAGE_INFO_NotchFilterOutput, MAVLINK_MESSAGE_INFO_MecIdInput, MAVLINK_MESSAGE_INFO_InputShapingInput, MAVLINK_MESSAGE_INFO_InputShapingConfig, MAVLINK_MESSAGE_INFO_InputShapingOutput, MAVLINK_MESSAGE_INFO_ScopeConfig, MAVLINK_MESSAGE_INFO_ScopeControl, MAVLINK_MESSAGE_INFO_ScopeData, MAVLINK_MESSAGE_INFO_WaveformData, MAVLINK_MESSAGE_INFO_WaveformMap, MAVLINK_MESSAGE_INFO_PosSpeedCtlInput, MAVLINK_MESSAGE_INFO_PosSpeedCtlOutput, MAVLINK_MESSAGE_INFO_PosSpeedCtlConfig, MAVLINK_MESSAGE_INFO_MotorCtlSmConfig, MAVLINK_MESSAGE_INFO_MotorCtlSmInput, MAVLINK_MESSAGE_INFO_MotorCtlSmOutput, MAVLINK_MESSAGE_INFO_CurrentCtlInput, MAVLINK_MESSAGE_INFO_CurrentCtlConfig, MAVLINK_MESSAGE_INFO_CurrentCtlOutput, MAVLINK_MESSAGE_INFO_NotchFilterConfig, MAVLINK_MESSAGE_INFO_SpeedObsPllInput, MAVLINK_MESSAGE_INFO_SpeedObsPllConfig, MAVLINK_MESSAGE_INFO_SpeedObsPllOutput, MAVLINK_MESSAGE_INFO_ElecAngleIdConfig, MAVLINK_MESSAGE_INFO_ElecAngleIdOutput, MAVLINK_MESSAGE_INFO_ElecAngleIdInput, MAVLINK_MESSAGE_INFO_DirectionIdInput, MAVLINK_MESSAGE_INFO_DirectionIdConfig, MAVLINK_MESSAGE_INFO_DirectionIdOutput, MAVLINK_MESSAGE_INFO_MotorPosSensorInput, MAVLINK_MESSAGE_INFO_MotorPosSensorConfig, MAVLINK_MESSAGE_INFO_MotorPosSensorOutput, MAVLINK_MESSAGE_INFO_PolePairsIdInput, MAVLINK_MESSAGE_INFO_PolePairsIdConfig, MAVLINK_MESSAGE_INFO_PolePairsIdOutput, MAVLINK_MESSAGE_INFO_NonVolatileParam, MAVLINK_MESSAGE_INFO_SystemConfig, MAVLINK_MESSAGE_INFO_TqFcIdInput, MAVLINK_MESSAGE_INFO_TqFcIdConfig, MAVLINK_MESSAGE_INFO_TqFcIdOutput, MAVLINK_MESSAGE_INFO_ObjectDictionary, MAVLINK_MESSAGE_INFO_ReciprocalMotionConfig, MAVLINK_MESSAGE_INFO_ReciprocalMotionOutput, MAVLINK_MESSAGE_INFO_ReferenceSignalConfig, MAVLINK_MESSAGE_INFO_ReferenceSignalOutput, MAVLINK_MESSAGE_INFO_AppControlWord, MAVLINK_MESSAGE_INFO_AppStatusInfo, MAVLINK_MESSAGE_INFO_AppOpMode, MAVLINK_MESSAGE_INFO_AppEncoderConfig, MAVLINK_MESSAGE_INFO_AppBaseConfig, MAVLINK_MESSAGE_INFO_AppMotionParam, MAVLINK_MESSAGE_INFO_AppRestrictParam, MAVLINK_MESSAGE_INFO_AppMotionInfo, MAVLINK_MESSAGE_INFO_AppWindowParam, MAVLINK_MESSAGE_INFO_AppMotorConfig, MAVLINK_MESSAGE_INFO_AppProtectConfig, MAVLINK_MESSAGE_INFO_MitCtlInput, MAVLINK_MESSAGE_INFO_MitCtlConfig, MAVLINK_MESSAGE_INFO_MitCtlOutput, MAVLINK_MESSAGE_INFO_AppPermissionConfig, MAVLINK_MESSAGE_INFO_SystemCmd, MAVLINK_MESSAGE_INFO_LoadPosSensorInput, MAVLINK_MESSAGE_INFO_LoadPosSensorConfig, MAVLINK_MESSAGE_INFO_LoadPosSensorOutput, MAVLINK_MESSAGE_INFO_SystemStatus, MAVLINK_MESSAGE_INFO_EncoderCalibrationCmd, MAVLINK_MESSAGE_INFO_EncoderCalibrationStatus, MAVLINK_MESSAGE_INFO_CustomInfo, MAVLINK_MESSAGE_INFO_HeartBit, MAVLINK_MESSAGE_INFO_HistoricalInfo, MAVLINK_MESSAGE_INFO_SimPlantInput, MAVLINK_MESSAGE_INFO_SimPlantOutput, MAVLINK_MESSAGE_INFO_SimPlantConfig, MAVLINK_MESSAGE_INFO_AppDebugParam, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}}
# define MAVLINK_MESSAGE_NAMES {{ "AppBaseConfig", 67 }, { "AppControlWord", 63 }, { "AppDebugParam", 91 }, { "AppEncoderConfig", 66 }, { "AppMotionInfo", 70 }, { "AppMotionParam", 68 }, { "AppMotorConfig", 72 }, { "AppOpMode", 65 }, { "AppPermissionConfig", 77 }, { "AppProtectConfig", 73 }, { "AppRestrictParam", 69 }, { "AppStatusInfo", 64 }, { "AppWindowParam", 71 }, { "CurrentCtlConfig", 35 }, { "CurrentCtlInput", 34 }, { "CurrentCtlOutput", 36 }, { "CustomInfo", 85 }, { "DirectionIdConfig", 45 }, { "DirectionIdInput", 44 }, { "DirectionIdOutput", 46 }, { "ElecAngleIdConfig", 41 }, { "ElecAngleIdInput", 43 }, { "ElecAngleIdOutput", 42 }, { "ElecIdSinConfig", 13 }, { "ElecIdSinInput", 11 }, { "ElecIdSinOutput", 12 }, { "EncoderCalibrationCmd", 83 }, { "EncoderCalibrationStatus", 84 }, { "HeartBit", 86 }, { "HistoricalInfo", 87 }, { "InputShapingConfig", 21 }, { "InputShapingInput", 20 }, { "InputShapingOutput", 22 }, { "LoadPosSensorConfig", 80 }, { "LoadPosSensorInput", 79 }, { "LoadPosSensorOutput", 81 }, { "MecIdConfig", 15 }, { "MecIdInput", 19 }, { "MecIdOutput", 14 }, { "MitCtlConfig", 75 }, { "MitCtlInput", 74 }, { "MitCtlOutput", 76 }, { "MotorCtlSmConfig", 31 }, { "MotorCtlSmInput", 32 }, { "MotorCtlSmOutput", 33 }, { "MotorPosSensorConfig", 48 }, { "MotorPosSensorInput", 47 }, { "MotorPosSensorOutput", 49 }, { "NonVolatileParam", 53 }, { "NotchFilterConfig", 37 }, { "NotchFilterInput", 16 }, { "NotchFilterInternal", 17 }, { "NotchFilterOutput", 18 }, { "ObjectDictionary", 58 }, { "PmsmConfig", 10 }, { "PolePairsIdConfig", 51 }, { "PolePairsIdInput", 50 }, { "PolePairsIdOutput", 52 }, { "PosSpeedCtlConfig", 30 }, { "PosSpeedCtlInput", 28 }, { "PosSpeedCtlOutput", 29 }, { "READ_PARAM", 9 }, { "ReciprocalMotionConfig", 59 }, { "ReciprocalMotionOutput", 60 }, { "ReferenceSignalConfig", 61 }, { "ReferenceSignalOutput", 62 }, { "ScopeConfig", 23 }, { "ScopeControl", 24 }, { "ScopeData", 25 }, { "SimPlantConfig", 90 }, { "SimPlantInput", 88 }, { "SimPlantOutput", 89 }, { "SpeedObsPllConfig", 39 }, { "SpeedObsPllInput", 38 }, { "SpeedObsPllOutput", 40 }, { "SystemCmd", 78 }, { "SystemConfig", 54 }, { "SystemStatus", 82 }, { "TqFcIdConfig", 56 }, { "TqFcIdInput", 55 }, { "TqFcIdOutput", 57 }, { "WaveformData", 26 }, { "WaveformMap", 27 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_SERVO_HUB_DATABASE_H
