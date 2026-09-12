#include "factory_trace_recorder.h"

#include <string.h>

static bool FactoryTraceConfigIsValid(const FactoryTraceConfig *config)
{
    uint32_t total;

    if (config == NULL || config->channel_count == 0U ||
        config->channel_count > FACTORY_TRACE_MAX_CHANNELS ||
        config->sample_divider == 0U ||
        config->trigger_channel >= config->channel_count) {
        return false;
    }

    total = (uint32_t)config->pretrigger_samples + 1U +
            (uint32_t)config->posttrigger_samples;
    if (total > FACTORY_TRACE_CAPACITY) {
        return false;
    }

    return config->trigger_mode >= FACTORY_TRACE_TRIGGER_IMMEDIATE &&
           config->trigger_mode <= FACTORY_TRACE_TRIGGER_FALLING;
}

static void FactoryTraceAppend(FactoryTraceRecorder *recorder,
                               const float *values,
                               uint8_t value_count)
{
    FactoryTraceSample *sample = &recorder->samples[recorder->write_index];
    uint8_t i;

    sample->sequence = recorder->source_sequence;
    for (i = 0U; i < value_count; ++i) {
        sample->values[i] = values[i];
    }
    for (; i < FACTORY_TRACE_MAX_CHANNELS; ++i) {
        sample->values[i] = 0.0F;
    }

    recorder->write_index =
        (uint16_t)((recorder->write_index + 1U) % FACTORY_TRACE_CAPACITY);
    if (recorder->valid_count < FACTORY_TRACE_CAPACITY) {
        recorder->valid_count++;
    } else {
        recorder->start_index =
            (uint16_t)((recorder->start_index + 1U) % FACTORY_TRACE_CAPACITY);
    }
}

static void FactoryTraceTrimPretrigger(FactoryTraceRecorder *recorder)
{
    while (recorder->valid_count > recorder->config.pretrigger_samples) {
        recorder->start_index =
            (uint16_t)((recorder->start_index + 1U) % FACTORY_TRACE_CAPACITY);
        recorder->valid_count--;
    }
}

static bool FactoryTraceThresholdTriggered(FactoryTraceRecorder *recorder,
                                           float value)
{
    bool triggered = false;

    if (!recorder->trigger_value_valid) {
        recorder->last_trigger_value = value;
        recorder->trigger_value_valid = true;
        return false;
    }

    if (recorder->config.trigger_mode == FACTORY_TRACE_TRIGGER_RISING) {
        triggered = recorder->last_trigger_value < recorder->config.trigger_threshold &&
                    value >= recorder->config.trigger_threshold;
    } else if (recorder->config.trigger_mode == FACTORY_TRACE_TRIGGER_FALLING) {
        triggered = recorder->last_trigger_value > recorder->config.trigger_threshold &&
                    value <= recorder->config.trigger_threshold;
    }

    recorder->last_trigger_value = value;
    return triggered;
}

void FactoryTraceRecorderInit(FactoryTraceRecorder *recorder,
                              uint32_t base_sample_rate_hz)
{
    if (recorder == NULL) {
        return;
    }

    memset(recorder, 0, sizeof(*recorder));
    recorder->base_sample_rate_hz = base_sample_rate_hz;
    recorder->state = FACTORY_TRACE_STATE_IDLE;
}

FactoryTraceStatusCode FactoryTraceRecorderConfigure(
    FactoryTraceRecorder *recorder, const FactoryTraceConfig *config)
{
    if (recorder == NULL || !FactoryTraceConfigIsValid(config)) {
        return FACTORY_TRACE_INVALID_ARGUMENT;
    }
    if (recorder->state == FACTORY_TRACE_STATE_ARMED ||
        recorder->state == FACTORY_TRACE_STATE_TRIGGERED) {
        return FACTORY_TRACE_BUSY;
    }

    recorder->config = *config;
    return FACTORY_TRACE_OK;
}

FactoryTraceStatusCode FactoryTraceRecorderArm(FactoryTraceRecorder *recorder)
{
    if (recorder == NULL || !FactoryTraceConfigIsValid(&recorder->config)) {
        return FACTORY_TRACE_INVALID_ARGUMENT;
    }
    if (recorder->base_sample_rate_hz == 0U) {
        return FACTORY_TRACE_NOT_READY;
    }

    recorder->capture_id++;
    recorder->state = FACTORY_TRACE_STATE_ARMED;
    recorder->source_sequence = 0U;
    recorder->decimation_counter = 0U;
    recorder->start_index = 0U;
    recorder->write_index = 0U;
    recorder->valid_count = 0U;
    recorder->trigger_sample_offset = 0U;
    recorder->post_remaining = 0U;
    recorder->trigger_value_valid = false;
    recorder->manual_trigger_pending = false;
    return FACTORY_TRACE_OK;
}

FactoryTraceStatusCode FactoryTraceRecorderManualTrigger(
    FactoryTraceRecorder *recorder)
{
    if (recorder == NULL) {
        return FACTORY_TRACE_INVALID_ARGUMENT;
    }
    if (recorder->state != FACTORY_TRACE_STATE_ARMED ||
        recorder->config.trigger_mode != FACTORY_TRACE_TRIGGER_MANUAL) {
        return FACTORY_TRACE_NOT_READY;
    }

    recorder->manual_trigger_pending = true;
    return FACTORY_TRACE_OK;
}

void FactoryTraceRecorderPushIsr(FactoryTraceRecorder *recorder,
                                 const float *selected_values,
                                 uint8_t value_count)
{
    bool trigger_now = false;
    float trigger_value;

    if (recorder == NULL || selected_values == NULL ||
        value_count != recorder->config.channel_count ||
        (recorder->state != FACTORY_TRACE_STATE_ARMED &&
         recorder->state != FACTORY_TRACE_STATE_TRIGGERED)) {
        return;
    }

    recorder->source_sequence++;

    if (recorder->decimation_counter != 0U) {
        recorder->decimation_counter--;
        return;
    }
    recorder->decimation_counter = (uint32_t)recorder->config.sample_divider - 1U;

    if (recorder->state == FACTORY_TRACE_STATE_TRIGGERED) {
        FactoryTraceAppend(recorder, selected_values, value_count);
        if (recorder->post_remaining > 0U) {
            recorder->post_remaining--;
        }
        if (recorder->post_remaining == 0U) {
            recorder->state = FACTORY_TRACE_STATE_COMPLETE;
        }
        return;
    }

    trigger_value = selected_values[recorder->config.trigger_channel];
    switch (recorder->config.trigger_mode) {
    case FACTORY_TRACE_TRIGGER_IMMEDIATE:
        trigger_now = true;
        break;
    case FACTORY_TRACE_TRIGGER_MANUAL:
        trigger_now = recorder->manual_trigger_pending;
        break;
    case FACTORY_TRACE_TRIGGER_RISING:
    case FACTORY_TRACE_TRIGGER_FALLING:
        trigger_now = FactoryTraceThresholdTriggered(recorder, trigger_value);
        break;
    default:
        recorder->state = FACTORY_TRACE_STATE_ERROR;
        return;
    }

    if (!trigger_now) {
        FactoryTraceAppend(recorder, selected_values, value_count);
        FactoryTraceTrimPretrigger(recorder);
        return;
    }

    recorder->manual_trigger_pending = false;
    recorder->trigger_sample_offset = recorder->valid_count;
    FactoryTraceAppend(recorder, selected_values, value_count);
    recorder->post_remaining = recorder->config.posttrigger_samples;
    if (recorder->post_remaining == 0U) {
        recorder->state = FACTORY_TRACE_STATE_COMPLETE;
    } else {
        recorder->state = FACTORY_TRACE_STATE_TRIGGERED;
    }
}

FactoryTraceStatus FactoryTraceRecorderGetStatus(
    const FactoryTraceRecorder *recorder)
{
    FactoryTraceStatus status = {0};

    if (recorder == NULL) {
        status.state = FACTORY_TRACE_STATE_ERROR;
        return status;
    }

    status.state = recorder->state;
    status.capture_id = recorder->capture_id;
    status.base_sample_rate_hz = recorder->base_sample_rate_hz;
    status.effective_sample_rate_hz =
        recorder->config.sample_divider == 0U
            ? 0U
            : recorder->base_sample_rate_hz / recorder->config.sample_divider;
    status.sample_count = recorder->valid_count;
    status.trigger_sample_offset = recorder->trigger_sample_offset;
    status.channel_count = recorder->config.channel_count;
    status.sample_divider = recorder->config.sample_divider;
    return status;
}

FactoryTraceStatusCode FactoryTraceRecorderReadSample(
    const FactoryTraceRecorder *recorder, uint16_t logical_index,
    FactoryTraceSample *sample)
{
    uint16_t physical_index;

    if (recorder == NULL || sample == NULL) {
        return FACTORY_TRACE_INVALID_ARGUMENT;
    }
    if (recorder->state != FACTORY_TRACE_STATE_COMPLETE) {
        return FACTORY_TRACE_NOT_READY;
    }
    if (logical_index >= recorder->valid_count) {
        return FACTORY_TRACE_OUT_OF_RANGE;
    }

    physical_index =
        (uint16_t)((recorder->start_index + logical_index) % FACTORY_TRACE_CAPACITY);
    *sample = recorder->samples[physical_index];
    return FACTORY_TRACE_OK;
}
