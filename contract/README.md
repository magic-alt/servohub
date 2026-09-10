# Servo Product Contract

`contract/schema/product_contract.json` is the canonical, versioned product-contract source for the fields covered by this directory. It exists to stop firmware, CANopen/EDS, host metadata, diagnostics, future EtherCAT bindings, and language SDKs from evolving as independent hand-maintained interfaces.

## Ownership rule

The canonical schema lives in `magic-alt/servohub` because firmware owns the product data model. Consumers such as `servo_host`, ROS 2, Python, C++, test tools, and factory software must pin an immutable ServoHub contract commit and consume generated artifacts or generated metadata. They must not maintain a second editable copy of the schema.

For a covered field, change order is:

1. update `contract/schema/product_contract.json`;
2. run the validator and source-drift check;
3. regenerate checked-in artifacts;
4. update protocol/runtime bindings when the change requires them;
5. update consumer lock files to the new ServoHub contract commit.

## Phase 1 coverage

The initial contract deliberately covers a high-confidence slice rather than claiming that all legacy metadata has already been migrated:

- 15 product parameters across operation, motion, limits, and motor configuration;
- 8 status/feedback signals;
- stable product IDs and capability IDs;
- 21 legacy error entries and 7 warning entries migrated from the current `servo_host` catalogs;
- declared CANopen EDS address/name and wire type for the covered parameters/signals.

The checker proves that each covered firmware field still exists in `database/data_param.h` and that each declared CANopen object/subobject still exists in `SlaveOD.eds` with the expected name.

### Important type boundary

`product_type` and `canopen.wire_type` are intentionally separate. The firmware/product model often uses a wider or physical type while CiA402 transports an integer representation. Examples include `motion.target_position` (`int64` product field vs `int32` at `0x607A`) and `motion.target_torque` (`float32` product field vs `int16` at `0x6071`). Conversion/scaling therefore remains a protocol-adapter responsibility until an explicit conversion contract is added.

## Diagnostics migration status

The error/warning entries are a **migration seed**, not yet firmware-verified symbolic definitions. Their schema entries set `firmware_verified=false`. This prevents the new SSOT from falsely claiming evidence that is not present in the current firmware source tree. The next diagnostics step is to locate or introduce firmware symbolic fault definitions and then promote each migrated entry to firmware-verified status.

## Deferred bindings

Phase 1 does not claim that the following are already generated from the schema:

- `database/data_param.c/.h` runtime implementation;
- `SlaveOD.c/.h` or the complete EDS;
- MAVLink XML/generated headers (the authoritative dialect source must first be identified);
- EtherCAT object dictionary / ESI;
- protocol scaling/conversion functions.

These stay existing runtime sources during the seed phase. The schema is the change-control source for covered semantics, and the drift gate prevents silent divergence while generation is introduced incrementally.

## Commands

Requires Python 3.9+ and no third-party packages.

```bash
python contract/tools/contract_tool.py validate
python contract/tools/contract_tool.py generate
python contract/tools/contract_tool.py check
python contract/tools/contract_tool.py all
```

`generate` rewrites checked-in derivatives. `check` fails when generated files are stale. `all` additionally validates firmware-field and EDS-name/address presence.

## Generated artifacts

- `generated/servo_contract_ids.h`: stable C IDs for firmware/SDK integration;
- `generated/host/servo_parameters.csv`: protocol-neutral product metadata plus CANopen wire binding;
- `generated/host/error_code.csv`: error catalog generated from the schema;
- `generated/host/warning_code.csv`: warning catalog generated from the schema;
- `generated/manifest.json`: contract/schema/protocol/generator versions and the exact Git blob ID of the canonical schema.

Generated files are committed intentionally so downstream repositories can pin exact artifacts without requiring the ServoHub generator at runtime.

## Compatibility rules

Within a schema major version, these are breaking unless explicitly version-gated: reusing/removing a stable product ID, changing a semantic name's meaning, changing a product type, changing units/scaling semantics once specified, reusing a diagnostic code, or changing a CANopen address/wire representation without a protocol-revision change. Additive optional parameters/capabilities may be compatible when older consumers can ignore them.
