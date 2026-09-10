#pragma once

/* GENERATED FILE. DO NOT EDIT.
 * Source: contract/schema bundle
 * Canonical semantic names and compatibility aliases only.
 */

#include <stddef.h>

typedef struct ServoContractAlias {
    const char* canonical;
    const char* alias;
} ServoContractAlias;

static const ServoContractAlias SERVO_CONTRACT_ALIASES[] = {
    {"operation.mode", "drive.operation_mode"},
    {"limits.software_position_min", "position.limit_min"},
    {"limits.software_position_max", "position.limit_max"},
    {"status.statusword", "drive.status_word"},
    {"feedback.position", "feedback.actual_position"},
    {"feedback.velocity", "feedback.actual_velocity"},
    {"feedback.current", "feedback.actual_current"},
    {"feedback.dc_link_voltage", "feedback.bus_voltage"},
};

#define SERVO_CONTRACT_ALIAS_COUNT (sizeof(SERVO_CONTRACT_ALIASES) / sizeof(SERVO_CONTRACT_ALIASES[0]))
