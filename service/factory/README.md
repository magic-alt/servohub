# ServoHub Factory Service v1

This directory defines the **Factory/R&D Service Plane**. It is intentionally separate from the Product Contract in `contract/schema/product_contract.json`.

## Ownership and compatibility

- `schema/factory_service_v1.json` is the editable source of truth.
- `generated/` contains deterministic outputs produced by `tools/factory_service_codegen/generate.py`.
- `schema_version` and `protocol_revision` are negotiated before any factory command is accepted by a host.
- Unknown schema/protocol revisions fail closed.
- Service IDs are not Product Contract IDs and must never be exposed as ordinary product semantics.

## Trace recorder

`trace/factory_trace_recorder.[ch]` is a bounded, heap-free recorder intended to be called once from the current-control ISR. Default capacity is 1024 samples and may be overridden with `FACTORY_TRACE_CAPACITY`. It supports up to eight channels, sample-divider decimation, rolling pre-trigger history, immediate/manual/rising/falling triggers, bounded post-trigger capture and logical-order reads after the capture freezes.

The recorder never streams every ISR sample over CAN. Capture happens in MCU memory first; bulk transfer occurs only after the buffer is frozen.

## v1 FOC signal set

The v1 schema only names quantities currently available at the `CurrentLoopCtrl()` boundary: Id/Iq reference, Id/Iq feedback, phase current A/B/C and DC-link voltage. Vd/Vq and PWM-duty signals are deliberately not advertised until the generated control model exposes them as stable outputs.

## Current-loop integration

`FactoryServiceTracePushFocIsr()` is the firmware-side ISR entry point. The intended hook is immediately after `CurrentCtlLoopTask()` in `CurrentLoopCtrl()`, using `kAxis.current_ctl_input` and `kAxis.current_ctl_output`. A factory-enabled firmware build must call `FactoryServiceInit(CURRENT_FREQUENCY_HZ)` once during motor-control initialization and `FactoryServiceTracePushFocIsr()` once per current-loop invocation.

The core is compile-time optional (`SERVOHUB_ENABLE_FACTORY_SERVICE_TRACE=OFF` by default). This slice deliberately keeps the production motor-control call site unchanged until target build, SRAM footprint and ISR-overhead evidence are collected. Wiring the hook is the next firmware integration step, not an implicit claim of this core PR.

## Diagnostics validity

`FactoryDiagnosticSnapshot.valid_fields` marks which BSP/control values are actually wired. Reading a known but unwired diagnostic returns `FACTORY_TRACE_NOT_READY`; it never returns a default zero as if that were measured evidence. Current-offset, gate-driver and ISR-timing diagnostics therefore remain not-ready until their authoritative firmware sources are connected.

## CANopen binding

The schema reserves manufacturer-specific objects `0x2200..0x2206`. The generated manifest is a binding contract, **not yet a claim that CanFestival `SlaveOD.c/.h/.eds` contains those objects**. `SlaveOD.*` remains generator-owned; transport integration must extend the CANopen code generator and regenerate the object dictionary instead of hand-editing generated files.

## Evidence rule

Host-rate feedback is not equivalent to this trace. Only a completed capture with negotiated service schema/protocol, base sample rate, divider, channel list, capture id and sample count may be used as internal FOC trace evidence.
