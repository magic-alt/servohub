#ifndef SERVOHUB_FACTORY_SERVICE_H
#define SERVOHUB_FACTORY_SERVICE_H

#include <stdint.h>

#include "factory_service_ids.h"
#include "factory_trace_recorder.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FACTORY_SERVICE_SCHEMA_VERSION 1U
#define FACTORY_SERVICE_PROTOCOL_REVISION 1U

typedef enum FactoryDiagnosticValidBits {
    FACTORY_DIAG_VALID_DC_BUS_VOLTAGE = UINT32_C(1) << 0,
    FACTORY_DIAG_VALID_DRIVER_TEMPERATURE = UINT32_C(1) << 1,
    FACTORY_DIAG_VALID_MCU_TEMPERATURE = UINT32_C(1) << 2,
    FACTORY_DIAG_VALID_MOTOR_TEMPERATURE = UINT32_C(1) << 3,
    FACTORY_DIAG_VALID_CURRENT_OFFSET_PHASE_A = UINT32_C(1) << 4,
    FACTORY_DIAG_VALID_CURRENT_OFFSET_PHASE_B = UINT32_C(1) << 5,
    FACTORY_DIAG_VALID_CURRENT_OFFSET_PHASE_C = UINT32_C(1) << 6,
    FACTORY_DIAG_VALID_ENCODER_MOTOR_RAW_COUNT = UINT32_C(1) << 7,
    FACTORY_DIAG_VALID_ENCODER_LOAD_RAW_COUNT = UINT32_C(1) << 8,
    FACTORY_DIAG_VALID_GATE_DRIVER_FAULT_BITS = UINT32_C(1) << 9,
    FACTORY_DIAG_VALID_CURRENT_ISR_OVERRUN_COUNT = UINT32_C(1) << 10
} FactoryDiagnosticValidBits;

typedef struct FactoryServiceInfo {
    uint16_t schema_version;
    uint16_t protocol_revision;
    uint32_t capabilities;
    uint16_t trace_capacity;
    uint8_t trace_max_channels;
    uint32_t base_sample_rate_hz;
} FactoryServiceInfo;

typedef struct FactoryDiagnosticSnapshot {
    uint32_t valid_fields;
    float dc_bus_voltage_v;
    float driver_temperature_c;
    float mcu_temperature_c;
    float motor_temperature_c;
    float phase_current_offset_a[3];
    uint32_t encoder_motor_raw_count;
    uint32_t encoder_load_raw_count;
    uint32_t gate_driver_fault_bits;
    uint32_t current_isr_overrun_count;
} FactoryDiagnosticSnapshot;

typedef struct FactoryFocTraceSource {
    float id_ref_a;
    float iq_ref_a;
    float id_fb_a;
    float iq_fb_a;
    float ia_a;
    float ib_a;
    float ic_a;
    float dc_bus_voltage_v;
} FactoryFocTraceSource;

void FactoryServiceInit(uint32_t base_sample_rate_hz);
FactoryServiceInfo FactoryServiceGetInfo(void);
void FactoryServiceUpdateDiagnostics(const FactoryDiagnosticSnapshot *snapshot);
int32_t FactoryServiceReadDiagnostic(uint16_t diagnostic_id, float *value);
int32_t FactoryServiceTraceConfigure(const FactoryTraceConfig *config);
int32_t FactoryServiceTraceArm(void);
int32_t FactoryServiceTraceManualTrigger(void);
FactoryTraceStatus FactoryServiceTraceGetStatus(void);
int32_t FactoryServiceTraceReadSample(
    uint16_t logical_index,
    FactoryTraceSample *sample);
void FactoryServiceTracePushFocIsr(const FactoryFocTraceSource *source);

#ifdef __cplusplus
}
#endif
#endif
