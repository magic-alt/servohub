#include "factory_trace_recorder.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

static FactoryTraceConfig ConfigManual(void)
{
    FactoryTraceConfig config = {0};
    config.channel_ids[0] = 0x0101U;
    config.channel_ids[1] = 0x0102U;
    config.channel_count = 2U;
    config.trigger_channel = 1U;
    config.sample_divider = 1U;
    config.pretrigger_samples = 2U;
    config.posttrigger_samples = 2U;
    config.trigger_mode = FACTORY_TRACE_TRIGGER_MANUAL;
    return config;
}

static void TestManualPrePostCapture(void)
{
    FactoryTraceRecorder recorder;
    FactoryTraceConfig config = ConfigManual();
    FactoryTraceSample sample;
    FactoryTraceStatus status;
    float values[2];

    FactoryTraceRecorderInit(&recorder, 20000U);
    assert(FactoryTraceRecorderConfigure(&recorder, &config) == FACTORY_TRACE_OK);
    assert(FactoryTraceRecorderArm(&recorder) == FACTORY_TRACE_OK);
    values[0] = 1.0F;
    values[1] = 10.0F;
    FactoryTraceRecorderPushIsr(&recorder, values, 2U);
    values[0] = 2.0F;
    values[1] = 20.0F;
    FactoryTraceRecorderPushIsr(&recorder, values, 2U);
    assert(FactoryTraceRecorderManualTrigger(&recorder) == FACTORY_TRACE_OK);
    values[0] = 3.0F;
    values[1] = 30.0F;
    FactoryTraceRecorderPushIsr(&recorder, values, 2U);
    values[0] = 4.0F;
    values[1] = 40.0F;
    FactoryTraceRecorderPushIsr(&recorder, values, 2U);
    values[0] = 5.0F;
    values[1] = 50.0F;
    FactoryTraceRecorderPushIsr(&recorder, values, 2U);

    status = FactoryTraceRecorderGetStatus(&recorder);
    assert(status.state == FACTORY_TRACE_STATE_COMPLETE);
    assert(status.sample_count == 5U);
    assert(status.trigger_sample_offset == 2U);
    assert(status.effective_sample_rate_hz == 20000U);
    assert(
        FactoryTraceRecorderReadSample(&recorder, 2U, &sample) ==
        FACTORY_TRACE_OK);
    assert(fabsf(sample.values[0] - 3.0F) < 1e-6F);
}

static void TestRisingTriggerAndDecimation(void)
{
    FactoryTraceRecorder recorder;
    FactoryTraceConfig config = {0};
    FactoryTraceSample sample;
    FactoryTraceStatus status;
    float value[1];
    unsigned int i;

    config.channel_ids[0] = 0x0104U;
    config.channel_count = 1U;
    config.trigger_channel = 0U;
    config.sample_divider = 2U;
    config.pretrigger_samples = 2U;
    config.posttrigger_samples = 1U;
    config.trigger_mode = FACTORY_TRACE_TRIGGER_RISING;
    config.trigger_threshold = 1.0F;

    FactoryTraceRecorderInit(&recorder, 20000U);
    assert(FactoryTraceRecorderConfigure(&recorder, &config) == FACTORY_TRACE_OK);
    assert(FactoryTraceRecorderArm(&recorder) == FACTORY_TRACE_OK);

    for (i = 0U; i < 8U; ++i) {
        value[0] = (i < 4U) ? 0.5F : 1.5F;
        FactoryTraceRecorderPushIsr(&recorder, value, 1U);
    }

    status = FactoryTraceRecorderGetStatus(&recorder);
    assert(status.state == FACTORY_TRACE_STATE_COMPLETE);
    assert(status.effective_sample_rate_hz == 10000U);
    assert(status.sample_count == 4U);
    assert(status.trigger_sample_offset == 2U);
    assert(
        FactoryTraceRecorderReadSample(&recorder, 2U, &sample) ==
        FACTORY_TRACE_OK);
    assert(sample.sequence == 5U);
    assert(fabsf(sample.values[0] - 1.5F) < 1e-6F);
}

int main(void)
{
    TestManualPrePostCapture();
    TestRisingTriggerAndDecimation();
    puts("factory_trace_recorder_test: PASS");
    return 0;
}
