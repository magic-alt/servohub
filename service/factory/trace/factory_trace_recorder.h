#ifndef SERVOHUB_FACTORY_TRACE_RECORDER_H
#define SERVOHUB_FACTORY_TRACE_RECORDER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FACTORY_TRACE_MAX_CHANNELS 8U
#ifndef FACTORY_TRACE_CAPACITY
#define FACTORY_TRACE_CAPACITY 1024U
#endif

typedef enum FactoryTraceState {
    FACTORY_TRACE_STATE_IDLE = 0,
    FACTORY_TRACE_STATE_ARMED = 1,
    FACTORY_TRACE_STATE_TRIGGERED = 2,
    FACTORY_TRACE_STATE_COMPLETE = 3,
    FACTORY_TRACE_STATE_ERROR = 4
} FactoryTraceState;

typedef enum FactoryTraceTriggerMode {
    FACTORY_TRACE_TRIGGER_IMMEDIATE = 0,
    FACTORY_TRACE_TRIGGER_MANUAL = 1,
    FACTORY_TRACE_TRIGGER_RISING = 2,
    FACTORY_TRACE_TRIGGER_FALLING = 3
} FactoryTraceTriggerMode;

typedef enum FactoryTraceStatusCode {
    FACTORY_TRACE_OK = 0,
    FACTORY_TRACE_INVALID_ARGUMENT = -1,
    FACTORY_TRACE_BUSY = -2,
    FACTORY_TRACE_NOT_READY = -3,
    FACTORY_TRACE_OUT_OF_RANGE = -4
} FactoryTraceStatusCode;

typedef struct FactoryTraceConfig {
    uint16_t channel_ids[FACTORY_TRACE_MAX_CHANNELS];
    uint8_t channel_count;
    uint8_t trigger_channel;
    uint16_t sample_divider;
    uint16_t pretrigger_samples;
    uint16_t posttrigger_samples;
    FactoryTraceTriggerMode trigger_mode;
    float trigger_threshold;
} FactoryTraceConfig;

typedef struct FactoryTraceSample {
    uint32_t sequence;
    float values[FACTORY_TRACE_MAX_CHANNELS];
} FactoryTraceSample;

typedef struct FactoryTraceStatus {
    FactoryTraceState state;
    uint32_t capture_id;
    uint32_t base_sample_rate_hz;
    uint32_t effective_sample_rate_hz;
    uint16_t sample_count;
    uint16_t trigger_sample_offset;
    uint8_t channel_count;
    uint16_t sample_divider;
} FactoryTraceStatus;

typedef struct FactoryTraceRecorder {
    FactoryTraceConfig config;
    FactoryTraceSample samples[FACTORY_TRACE_CAPACITY];
    FactoryTraceState state;
    uint32_t capture_id;
    uint32_t base_sample_rate_hz;
    uint32_t source_sequence;
    uint32_t decimation_counter;
    uint16_t start_index;
    uint16_t write_index;
    uint16_t valid_count;
    uint16_t trigger_sample_offset;
    uint16_t post_remaining;
    float last_trigger_value;
    bool trigger_value_valid;
    bool manual_trigger_pending;
} FactoryTraceRecorder;

void FactoryTraceRecorderInit(FactoryTraceRecorder *recorder, uint32_t base_sample_rate_hz);
FactoryTraceStatusCode FactoryTraceRecorderConfigure(FactoryTraceRecorder *recorder,
                                                     const FactoryTraceConfig *config);
FactoryTraceStatusCode FactoryTraceRecorderArm(FactoryTraceRecorder *recorder);
FactoryTraceStatusCode FactoryTraceRecorderManualTrigger(FactoryTraceRecorder *recorder);
void FactoryTraceRecorderPushIsr(FactoryTraceRecorder *recorder,
                                 const float *selected_values,
                                 uint8_t value_count);
FactoryTraceStatus FactoryTraceRecorderGetStatus(const FactoryTraceRecorder *recorder);
FactoryTraceStatusCode FactoryTraceRecorderReadSample(const FactoryTraceRecorder *recorder,
                                                      uint16_t logical_index,
                                                      FactoryTraceSample *sample);

#ifdef __cplusplus
}
#endif
#endif
