# ServoHub CANopen / CiA 402 code generator

This directory makes the repository's existing CanFestival object dictionary
reproducible. It intentionally wraps the maintained Python 3 `objdictgen`
(`odg`) tool instead of carrying a second fork of `gen_cfile.py`.

## What is generated

The current canonical CANopen source is:

`communication/protocol/CANopen/SlaveOD/SlaveOD.eds`

A generation run produces/refreshes:

- `communication/protocol/CANopen/SlaveOD/SlaveOD.c`
- `communication/protocol/CANopen/SlaveOD/SlaveOD.h`
- `communication/protocol/CiA402/generated/cia402_od_generated.h`
- `communication/protocol/CiA402/generated/OBJECT_DICTIONARY.md`

The first two are CanFestival runtime artifacts. The latter two are a stable
ServoHub application-facing CiA 402 contract generated from
`cia402_profile.json`.

## Windows setup

From PowerShell:

```powershell
.\tools\canopen_codegen\setup.ps1
```

The script creates `tools/canopen_codegen/.venv` with Python 3.12 and installs
the pinned generator. It does not require activating the virtual environment.

Useful commands:

```powershell
.\tools\canopen_codegen\.venv\Scripts\python.exe .\tools\canopen_codegen\generate.py doctor
.\tools\canopen_codegen\.venv\Scripts\python.exe .\tools\canopen_codegen\generate.py list
.\tools\canopen_codegen\.venv\Scripts\python.exe .\tools\canopen_codegen\generate.py generate
```

For the optional wxPython editor:

```powershell
.\tools\canopen_codegen\.venv\Scripts\python.exe -m pip install -r .\tools\canopen_codegen\requirements-ui.txt
.\tools\canopen_codegen\.venv\Scripts\odg.exe edit .\communication\protocol\CANopen\SlaveOD\SlaveOD.eds
```

## Linux/macOS setup

```sh
./tools/canopen_codegen/setup.sh
./tools/canopen_codegen/.venv/bin/python tools/canopen_codegen/generate.py generate
```

## JSONC migration

Do not hand-convert the existing EDS. Use the generator:

```powershell
.\tools\canopen_codegen\.venv\Scripts\python.exe .\tools\canopen_codegen\generate.py migrate-jsonc
```

This creates:

`communication/protocol/CANopen/SlaveOD/SlaveOD.jsonc`

Review the generated JSONC and generated C/H against the existing EDS path.
After the migration is accepted, change only
`object_dictionary.source` in `codegen.json` to the JSONC path. From then on,
JSONC becomes the protocol source of truth and `SlaveOD.c/.h` remain generated
artifacts.

## CMake integration

Normal SIL builds are unchanged. Code generation is opt-in:

```powershell
cmake --preset servo_hil_demo_codegen
cmake --build out/build/servo_hil_demo_codegen --target canopen_codegen
```

Other targets:

```text
canopen_codegen
canopen_codegen_check
canopen_codegen_list
canopen_codegen_migrate_jsonc
```

`canopen_codegen_check` parses the configured OD with `odg` and checks the
checked-in CiA 402 generated contract for staleness.

## CiA 402 contract policy

`cia402_profile.json` is intentionally much smaller than the full CANopen
dictionary. It lists the objects that form the stable application/drive
contract, including Controlword, Statusword, modes of operation, position,
velocity, torque, profile limits, and quick-stop deceleration.

Rules:

1. EDS/JSONC owns the actual CANopen dictionary.
2. `cia402_profile.json` owns application-facing index/sub-index/type metadata.
3. A changed index, sub-index, signedness, access direction, or PDO direction is
   treated as an interface change and should be reviewed as such.
4. `SlaveOD.c/.h` and files under `CiA402/generated/` are generated and should
   not be edited manually.

## Why upstream `gen_cfile.py` is not modified yet

Phase 1 keeps the upstream generator intact. ServoHub-specific behavior is
implemented after OD generation, which keeps upgrades to `objdictgen` cheap and
makes generated code reproducible.

Only fork/patch `gen_cfile.py` if a requirement cannot be expressed by the OD or
post-generation contract layer. Typical future patch points would be:

- custom symbol naming for generated variables;
- section/alignment attributes for MCU memory placement;
- extra compile-time metadata for PDO objects;
- generated accessor functions tied to ServoHub's database/conversion layer.

If that becomes necessary, vendor the exact `objdictgen` revision under a
separate third-party/tooling path and keep the patch small and reviewable.
