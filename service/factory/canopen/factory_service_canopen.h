#ifndef SERVOHUB_FACTORY_SERVICE_CANOPEN_H
#define SERVOHUB_FACTORY_SERVICE_CANOPEN_H

#include <stdint.h>

#include "data.h"
#include "objacces.h"
#include "factory_service.h"
#include "factory_service_ids.h"

static UNS32 FactoryCanopenRead(CO_Data *d, UNS16 index, UNS8 subindex, void *value, UNS32 size)
{
    UNS8 type = 0U;
    return readLocalDict(d, index, subindex, value, &size, &type, 0U);
}

static UNS32 FactoryCanopenWrite(CO_Data *d, UNS16 index, UNS8 subindex, void *value, UNS32 size)
{
    return writeLocalDict(d, index, subindex, value, &size, 0U);
}

static void FactoryCanopenRefreshInfo(CO_Data *d)
{
    FactoryServiceInfo info = FactoryServiceGetInfo();
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_FACTORY_SERVICE_INFO_INDEX,
        FACTORY_CANOPEN_FACTORY_SERVICE_INFO_SCHEMA_VERSION_SUBINDEX, &info.schema_version, sizeof(info.schema_version));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_FACTORY_SERVICE_INFO_INDEX,
        FACTORY_CANOPEN_FACTORY_SERVICE_INFO_PROTOCOL_REVISION_SUBINDEX, &info.protocol_revision, sizeof(info.protocol_revision));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_FACTORY_SERVICE_INFO_INDEX,
        FACTORY_CANOPEN_FACTORY_SERVICE_INFO_CAPABILITIES_SUBINDEX, &info.capabilities, sizeof(info.capabilities));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_FACTORY_SERVICE_INFO_INDEX,
        FACTORY_CANOPEN_FACTORY_SERVICE_INFO_TRACE_CAPACITY_SUBINDEX, &info.trace_capacity, sizeof(info.trace_capacity));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_FACTORY_SERVICE_INFO_INDEX,
        FACTORY_CANOPEN_FACTORY_SERVICE_INFO_TRACE_MAX_CHANNELS_SUBINDEX, &info.trace_max_channels, sizeof(info.trace_max_channels));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_FACTORY_SERVICE_INFO_INDEX,
        FACTORY_CANOPEN_FACTORY_SERVICE_INFO_BASE_SAMPLE_RATE_HZ_SUBINDEX, &info.base_sample_rate_hz, sizeof(info.base_sample_rate_hz));
}

static void FactoryCanopenRefreshStatus(CO_Data *d)
{
    FactoryTraceStatus status = FactoryServiceTraceGetStatus();
    uint8_t state = (uint8_t)status.state;
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_STATUS_INDEX,
        FACTORY_CANOPEN_TRACE_STATUS_STATE_SUBINDEX, &state, sizeof(state));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_STATUS_INDEX,
        FACTORY_CANOPEN_TRACE_STATUS_CAPTURE_ID_SUBINDEX, &status.capture_id, sizeof(status.capture_id));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_STATUS_INDEX,
        FACTORY_CANOPEN_TRACE_STATUS_BASE_SAMPLE_RATE_HZ_SUBINDEX, &status.base_sample_rate_hz, sizeof(status.base_sample_rate_hz));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_STATUS_INDEX,
        FACTORY_CANOPEN_TRACE_STATUS_EFFECTIVE_SAMPLE_RATE_HZ_SUBINDEX, &status.effective_sample_rate_hz, sizeof(status.effective_sample_rate_hz));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_STATUS_INDEX,
        FACTORY_CANOPEN_TRACE_STATUS_SAMPLE_COUNT_SUBINDEX, &status.sample_count, sizeof(status.sample_count));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_STATUS_INDEX,
        FACTORY_CANOPEN_TRACE_STATUS_TRIGGER_SAMPLE_OFFSET_SUBINDEX, &status.trigger_sample_offset, sizeof(status.trigger_sample_offset));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_STATUS_INDEX,
        FACTORY_CANOPEN_TRACE_STATUS_CHANNEL_COUNT_SUBINDEX, &status.channel_count, sizeof(status.channel_count));
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_STATUS_INDEX,
        FACTORY_CANOPEN_TRACE_STATUS_SAMPLE_DIVIDER_SUBINDEX, &status.sample_divider, sizeof(status.sample_divider));
}

static FactoryTraceStatusCode FactoryCanopenLoadConfig(CO_Data *d)
{
    FactoryTraceConfig config = {0};
    uint8_t trigger_mode = 0U;
    if (FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_INDEX,
            FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_CHANNEL_COUNT_SUBINDEX,
            &config.channel_count, sizeof(config.channel_count)) != OD_SUCCESSFUL) {
        return FACTORY_TRACE_INVALID_ARGUMENT;
    }
    for (uint8_t channel = 0U; channel < FACTORY_TRACE_MAX_CHANNELS; ++channel) {
        if (FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_INDEX,
                (UNS8)(FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_CHANNEL_1_SUBINDEX + channel),
                &config.channel_ids[channel], sizeof(config.channel_ids[channel])) != OD_SUCCESSFUL) {
            return FACTORY_TRACE_INVALID_ARGUMENT;
        }
    }
    (void)FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_INDEX,
        FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_SAMPLE_DIVIDER_SUBINDEX, &config.sample_divider, sizeof(config.sample_divider));
    (void)FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_INDEX,
        FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_PRETRIGGER_SAMPLES_SUBINDEX, &config.pretrigger_samples, sizeof(config.pretrigger_samples));
    (void)FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_INDEX,
        FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_POSTTRIGGER_SAMPLES_SUBINDEX, &config.posttrigger_samples, sizeof(config.posttrigger_samples));
    (void)FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_INDEX,
        FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_TRIGGER_MODE_SUBINDEX, &trigger_mode, sizeof(trigger_mode));
    config.trigger_mode = (FactoryTraceTriggerMode)trigger_mode;
    (void)FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_INDEX,
        FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_TRIGGER_CHANNEL_SUBINDEX, &config.trigger_channel, sizeof(config.trigger_channel));
    (void)FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_INDEX,
        FACTORY_CANOPEN_TRACE_CONFIGURATION_WINDOW_TRIGGER_THRESHOLD_SUBINDEX, &config.trigger_threshold, sizeof(config.trigger_threshold));
    return FactoryServiceTraceConfigure(&config);
}

static UNS32 FactoryCanopenCommandCallback(CO_Data *d, const indextable *table, UNS8 subindex)
{
    (void)table;
    (void)subindex;
    uint8_t command = 0U;
    int32_t result = FACTORY_TRACE_INVALID_ARGUMENT;
    if (FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_COMMAND_INDEX,
            FACTORY_CANOPEN_TRACE_COMMAND_COMMAND_SUBINDEX, &command, sizeof(command)) == OD_SUCCESSFUL) {
        if (command == FACTORY_SERVICE_COMMAND_APPLY_CONFIG) {
            result = (int32_t)FactoryCanopenLoadConfig(d);
        } else if (command == FACTORY_SERVICE_COMMAND_ARM) {
            result = (int32_t)FactoryServiceTraceArm();
        } else if (command == FACTORY_SERVICE_COMMAND_MANUAL_TRIGGER) {
            result = (int32_t)FactoryServiceTraceManualTrigger();
        } else if (command == FACTORY_SERVICE_COMMAND_REFRESH_STATUS) {
            result = FACTORY_TRACE_OK;
        }
    }
    FactoryCanopenRefreshStatus(d);
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_COMMAND_INDEX,
        FACTORY_CANOPEN_TRACE_COMMAND_LAST_RESULT_SUBINDEX, &result, sizeof(result));
    return OD_SUCCESSFUL;
}

static UNS32 FactoryCanopenSampleCallback(CO_Data *d, const indextable *table, UNS8 subindex)
{
    (void)table;
    (void)subindex;
    uint16_t logical_index = 0U;
    FactoryTraceSample sample = {0};
    FactoryTraceStatus status = FactoryServiceTraceGetStatus();
    int32_t result = FACTORY_TRACE_INVALID_ARGUMENT;
    if (FactoryCanopenRead(d, FACTORY_CANOPEN_TRACE_DATA_WINDOW_INDEX,
            FACTORY_CANOPEN_TRACE_DATA_WINDOW_LOGICAL_INDEX_SUBINDEX,
            &logical_index, sizeof(logical_index)) == OD_SUCCESSFUL) {
        result = (int32_t)FactoryServiceTraceReadSample(logical_index, &sample);
    }
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_DATA_WINDOW_INDEX,
        FACTORY_CANOPEN_TRACE_DATA_WINDOW_READ_RESULT_SUBINDEX, &result, sizeof(result));
    if (result == FACTORY_TRACE_OK) {
        (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_DATA_WINDOW_INDEX,
            FACTORY_CANOPEN_TRACE_DATA_WINDOW_SEQUENCE_SUBINDEX, &sample.sequence, sizeof(sample.sequence));
        (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_DATA_WINDOW_INDEX,
            FACTORY_CANOPEN_TRACE_DATA_WINDOW_VALUE_COUNT_SUBINDEX, &status.channel_count, sizeof(status.channel_count));
        for (uint8_t channel = 0U; channel < status.channel_count; ++channel) {
            (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_TRACE_DATA_WINDOW_INDEX,
                (UNS8)(FACTORY_CANOPEN_TRACE_DATA_WINDOW_VALUE_1_SUBINDEX + channel),
                &sample.values[channel], sizeof(sample.values[channel]));
        }
    }
    return OD_SUCCESSFUL;
}

static UNS32 FactoryCanopenDiagnosticCallback(CO_Data *d, const indextable *table, UNS8 subindex)
{
    (void)table;
    (void)subindex;
    uint16_t diagnostic_id = 0U;
    float value = 0.0f;
    int32_t result = FACTORY_TRACE_INVALID_ARGUMENT;
    if (FactoryCanopenRead(d, FACTORY_CANOPEN_DIAGNOSTIC_SELECTOR_INDEX,
            FACTORY_CANOPEN_DIAGNOSTIC_SELECTOR_SUBINDEX, &diagnostic_id, sizeof(diagnostic_id)) == OD_SUCCESSFUL) {
        result = (int32_t)FactoryServiceReadDiagnostic(diagnostic_id, &value);
    }
    (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_DIAGNOSTIC_VALUE_INDEX,
        FACTORY_CANOPEN_DIAGNOSTIC_VALUE_READ_RESULT_SUBINDEX, &result, sizeof(result));
    if (result == FACTORY_TRACE_OK) {
        (void)FactoryCanopenWrite(d, FACTORY_CANOPEN_DIAGNOSTIC_VALUE_INDEX,
            FACTORY_CANOPEN_DIAGNOSTIC_VALUE_VALUE_SUBINDEX, &value, sizeof(value));
    }
    return OD_SUCCESSFUL;
}

static inline void FactoryServiceCanopenInit(CO_Data *d, uint32_t base_sample_rate_hz)
{
    if (d == NULL) {
        return;
    }
    FactoryServiceInit(base_sample_rate_hz);
    FactoryCanopenRefreshInfo(d);
    FactoryCanopenRefreshStatus(d);
    (void)RegisterSetODentryCallBack(d, FACTORY_CANOPEN_TRACE_COMMAND_INDEX,
        FACTORY_CANOPEN_TRACE_COMMAND_COMMAND_SUBINDEX, FactoryCanopenCommandCallback);
    (void)RegisterSetODentryCallBack(d, FACTORY_CANOPEN_TRACE_DATA_WINDOW_INDEX,
        FACTORY_CANOPEN_TRACE_DATA_WINDOW_LOGICAL_INDEX_SUBINDEX, FactoryCanopenSampleCallback);
    (void)RegisterSetODentryCallBack(d, FACTORY_CANOPEN_DIAGNOSTIC_SELECTOR_INDEX,
        FACTORY_CANOPEN_DIAGNOSTIC_SELECTOR_SUBINDEX, FactoryCanopenDiagnosticCallback);
}

#endif /* SERVOHUB_FACTORY_SERVICE_CANOPEN_H */
