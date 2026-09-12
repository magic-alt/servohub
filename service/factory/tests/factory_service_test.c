#include "factory_service.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    FactoryServiceInfo info;
    FactoryTraceConfig config = {0};
    FactoryFocTraceSource source = {0};
    FactoryTraceSample sample;
    FactoryTraceStatus status;
    FactoryDiagnosticSnapshot diagnostics = {0};
    float value = 0.0F;

    FactoryServiceInit(20000U);
    info = FactoryServiceGetInfo();
    assert(info.schema_version == 1U);
    assert(info.protocol_revision == 1U);
    assert(info.base_sample_rate_hz == 20000U);
    assert((info.capabilities & FACTORY_SERVICE_CAP_TRACE_CAPTURE) != 0U);

    assert(
        FactoryServiceReadDiagnostic(
            FACTORY_DIAG_POWER_DC_BUS_VOLTAGE,
            &value) == FACTORY_TRACE_NOT_READY);
    diagnostics.valid_fields = FACTORY_DIAG_VALID_DC_BUS_VOLTAGE;
    diagnostics.dc_bus_voltage_v = 48.25F;
    FactoryServiceUpdateDiagnostics(&diagnostics);
    assert(
        FactoryServiceReadDiagnostic(
            FACTORY_DIAG_POWER_DC_BUS_VOLTAGE,
            &value) == FACTORY_TRACE_OK);
    assert(fabsf(value - 48.25F) < 1e-6F);
    assert(
        FactoryServiceReadDiagnostic(
            FACTORY_DIAG_GATE_DRIVER_FAULT_BITS,
            &value) == FACTORY_TRACE_NOT_READY);

    config.channel_ids[0] = FACTORY_TRACE_SIGNAL_FOC_IQ_REF;
    config.channel_ids[1] = FACTORY_TRACE_SIGNAL_FOC_IQ_FB;
    config.channel_count = 2U;
    config.trigger_channel = 0U;
    config.sample_divider = 1U;
    config.pretrigger_samples = 1U;
    config.posttrigger_samples = 1U;
    config.trigger_mode = FACTORY_TRACE_TRIGGER_MANUAL;
    assert(FactoryServiceTraceConfigure(&config) == FACTORY_TRACE_OK);
    assert(FactoryServiceTraceArm() == FACTORY_TRACE_OK);
    source.iq_ref_a = 1.0F;
    source.iq_fb_a = 0.8F;
    FactoryServiceTracePushFocIsr(&source);
    assert(FactoryServiceTraceManualTrigger() == FACTORY_TRACE_OK);
    source.iq_ref_a = 2.0F;
    source.iq_fb_a = 1.7F;
    FactoryServiceTracePushFocIsr(&source);
    source.iq_fb_a = 1.9F;
    FactoryServiceTracePushFocIsr(&source);

    status = FactoryServiceTraceGetStatus();
    assert(status.state == FACTORY_TRACE_STATE_COMPLETE);
    assert(status.sample_count == 3U);
    assert(status.trigger_sample_offset == 1U);
    assert(
        FactoryServiceTraceReadSample(1U, &sample) == FACTORY_TRACE_OK);
    assert(fabsf(sample.values[1] - 1.7F) < 1e-6F);

    puts("factory_service_test: PASS");
    return 0;
}
