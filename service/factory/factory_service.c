#include "factory_service.h"

#include <string.h>

static FactoryTraceRecorder g_factory_trace_recorder;
static FactoryDiagnosticSnapshot g_factory_diagnostics;

static uint32_t FactoryServiceCapabilities(void)
{
    return FACTORY_SERVICE_CAP_DIAGNOSTICS_READ |
           FACTORY_SERVICE_CAP_TRACE_CAPTURE |
           FACTORY_SERVICE_CAP_TRACE_PRETRIGGER |
           FACTORY_SERVICE_CAP_TRACE_MANUAL_TRIGGER |
           FACTORY_SERVICE_CAP_TRACE_THRESHOLD_TRIGGER |
           FACTORY_SERVICE_CAP_TRACE_BULK_READ;
}

static int FactoryServiceSignalSupported(uint16_t signal_id)
{
    return signal_id >= FACTORY_TRACE_SIGNAL_FOC_ID_REF &&
           signal_id <= FACTORY_TRACE_SIGNAL_POWER_DC_BUS_VOLTAGE;
}

static float FactoryServiceSignalValue(
    const FactoryFocTraceSource *source,
    uint16_t signal_id)
{
    switch (signal_id) {
    case FACTORY_TRACE_SIGNAL_FOC_ID_REF:
        return source->id_ref_a;
    case FACTORY_TRACE_SIGNAL_FOC_IQ_REF:
        return source->iq_ref_a;
    case FACTORY_TRACE_SIGNAL_FOC_ID_FB:
        return source->id_fb_a;
    case FACTORY_TRACE_SIGNAL_FOC_IQ_FB:
        return source->iq_fb_a;
    case FACTORY_TRACE_SIGNAL_PHASE_CURRENT_A:
        return source->ia_a;
    case FACTORY_TRACE_SIGNAL_PHASE_CURRENT_B:
        return source->ib_a;
    case FACTORY_TRACE_SIGNAL_PHASE_CURRENT_C:
        return source->ic_a;
    case FACTORY_TRACE_SIGNAL_POWER_DC_BUS_VOLTAGE:
        return source->dc_bus_voltage_v;
    default:
        return 0.0F;
    }
}

static uint32_t FactoryServiceDiagnosticValidBit(uint16_t diagnostic_id)
{
    switch (diagnostic_id) {
    case FACTORY_DIAG_POWER_DC_BUS_VOLTAGE:
        return FACTORY_DIAG_VALID_DC_BUS_VOLTAGE;
    case FACTORY_DIAG_TEMPERATURE_DRIVER:
        return FACTORY_DIAG_VALID_DRIVER_TEMPERATURE;
    case FACTORY_DIAG_TEMPERATURE_MCU:
        return FACTORY_DIAG_VALID_MCU_TEMPERATURE;
    case FACTORY_DIAG_TEMPERATURE_MOTOR:
        return FACTORY_DIAG_VALID_MOTOR_TEMPERATURE;
    case FACTORY_DIAG_CURRENT_OFFSET_PHASE_A:
        return FACTORY_DIAG_VALID_CURRENT_OFFSET_PHASE_A;
    case FACTORY_DIAG_CURRENT_OFFSET_PHASE_B:
        return FACTORY_DIAG_VALID_CURRENT_OFFSET_PHASE_B;
    case FACTORY_DIAG_CURRENT_OFFSET_PHASE_C:
        return FACTORY_DIAG_VALID_CURRENT_OFFSET_PHASE_C;
    case FACTORY_DIAG_ENCODER_MOTOR_RAW_COUNT:
        return FACTORY_DIAG_VALID_ENCODER_MOTOR_RAW_COUNT;
    case FACTORY_DIAG_ENCODER_LOAD_RAW_COUNT:
        return FACTORY_DIAG_VALID_ENCODER_LOAD_RAW_COUNT;
    case FACTORY_DIAG_GATE_DRIVER_FAULT_BITS:
        return FACTORY_DIAG_VALID_GATE_DRIVER_FAULT_BITS;
    case FACTORY_DIAG_TIMING_CURRENT_ISR_OVERRUN_COUNT:
        return FACTORY_DIAG_VALID_CURRENT_ISR_OVERRUN_COUNT;
    default:
        return 0U;
    }
}

void FactoryServiceInit(uint32_t base_sample_rate_hz)
{
    memset(&g_factory_diagnostics, 0, sizeof(g_factory_diagnostics));
    FactoryTraceRecorderInit(&g_factory_trace_recorder, base_sample_rate_hz);
}

FactoryServiceInfo FactoryServiceGetInfo(void)
{
    FactoryServiceInfo info;
    info.schema_version = FACTORY_SERVICE_SCHEMA_VERSION;
    info.protocol_revision = FACTORY_SERVICE_PROTOCOL_REVISION;
    info.capabilities = FactoryServiceCapabilities();
    info.trace_capacity = FACTORY_TRACE_CAPACITY;
    info.trace_max_channels = FACTORY_TRACE_MAX_CHANNELS;
    info.base_sample_rate_hz = g_factory_trace_recorder.base_sample_rate_hz;
    return info;
}

void FactoryServiceUpdateDiagnostics(const FactoryDiagnosticSnapshot *snapshot)
{
    if (snapshot != NULL) {
        g_factory_diagnostics = *snapshot;
    }
}

int32_t FactoryServiceReadDiagnostic(uint16_t diagnostic_id, float *value)
{
    uint32_t valid_bit;

    if (value == NULL) {
        return FACTORY_TRACE_INVALID_ARGUMENT;
    }
    valid_bit = FactoryServiceDiagnosticValidBit(diagnostic_id);
    if (valid_bit == 0U) {
        return FACTORY_TRACE_OUT_OF_RANGE;
    }
    if ((g_factory_diagnostics.valid_fields & valid_bit) == 0U) {
        return FACTORY_TRACE_NOT_READY;
    }

    switch (diagnostic_id) {
    case FACTORY_DIAG_POWER_DC_BUS_VOLTAGE:
        *value = g_factory_diagnostics.dc_bus_voltage_v;
        break;
    case FACTORY_DIAG_TEMPERATURE_DRIVER:
        *value = g_factory_diagnostics.driver_temperature_c;
        break;
    case FACTORY_DIAG_TEMPERATURE_MCU:
        *value = g_factory_diagnostics.mcu_temperature_c;
        break;
    case FACTORY_DIAG_TEMPERATURE_MOTOR:
        *value = g_factory_diagnostics.motor_temperature_c;
        break;
    case FACTORY_DIAG_CURRENT_OFFSET_PHASE_A:
        *value = g_factory_diagnostics.phase_current_offset_a[0];
        break;
    case FACTORY_DIAG_CURRENT_OFFSET_PHASE_B:
        *value = g_factory_diagnostics.phase_current_offset_a[1];
        break;
    case FACTORY_DIAG_CURRENT_OFFSET_PHASE_C:
        *value = g_factory_diagnostics.phase_current_offset_a[2];
        break;
    case FACTORY_DIAG_ENCODER_MOTOR_RAW_COUNT:
        *value = (float)g_factory_diagnostics.encoder_motor_raw_count;
        break;
    case FACTORY_DIAG_ENCODER_LOAD_RAW_COUNT:
        *value = (float)g_factory_diagnostics.encoder_load_raw_count;
        break;
    case FACTORY_DIAG_GATE_DRIVER_FAULT_BITS:
        *value = (float)g_factory_diagnostics.gate_driver_fault_bits;
        break;
    case FACTORY_DIAG_TIMING_CURRENT_ISR_OVERRUN_COUNT:
        *value = (float)g_factory_diagnostics.current_isr_overrun_count;
        break;
    default:
        return FACTORY_TRACE_OUT_OF_RANGE;
    }
    return FACTORY_TRACE_OK;
}

int32_t FactoryServiceTraceConfigure(const FactoryTraceConfig *config)
{
    uint8_t i;

    if (config == NULL) {
        return FACTORY_TRACE_INVALID_ARGUMENT;
    }
    for (i = 0U; i < config->channel_count; ++i) {
        if (!FactoryServiceSignalSupported(config->channel_ids[i])) {
            return FACTORY_TRACE_OUT_OF_RANGE;
        }
    }
    return FactoryTraceRecorderConfigure(&g_factory_trace_recorder, config);
}

int32_t FactoryServiceTraceArm(void)
{
    return FactoryTraceRecorderArm(&g_factory_trace_recorder);
}

int32_t FactoryServiceTraceManualTrigger(void)
{
    return FactoryTraceRecorderManualTrigger(&g_factory_trace_recorder);
}

FactoryTraceStatus FactoryServiceTraceGetStatus(void)
{
    return FactoryTraceRecorderGetStatus(&g_factory_trace_recorder);
}

int32_t FactoryServiceTraceReadSample(
    uint16_t logical_index,
    FactoryTraceSample *sample)
{
    return FactoryTraceRecorderReadSample(
        &g_factory_trace_recorder,
        logical_index,
        sample);
}

void FactoryServiceTracePushFocIsr(const FactoryFocTraceSource *source)
{
    float selected[FACTORY_TRACE_MAX_CHANNELS];
    uint8_t i;
    const FactoryTraceConfig *config;

    if (source == NULL) {
        return;
    }
    config = &g_factory_trace_recorder.config;
    if (config->channel_count == 0U ||
        (g_factory_trace_recorder.state != FACTORY_TRACE_STATE_ARMED &&
         g_factory_trace_recorder.state != FACTORY_TRACE_STATE_TRIGGERED)) {
        return;
    }
    for (i = 0U; i < config->channel_count; ++i) {
        selected[i] = FactoryServiceSignalValue(source, config->channel_ids[i]);
    }
    FactoryTraceRecorderPushIsr(
        &g_factory_trace_recorder,
        selected,
        config->channel_count);
}
