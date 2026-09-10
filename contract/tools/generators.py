from __future__ import annotations

import csv
import io
import json
import struct
from pathlib import Path

from schema_model import GENERATED, EDS_TYPE_CODE, STRUCT_FORMAT, all_items, enum_name, fail, schema_manifest


def csv_text(header: list[str], rows: list[list[object]]) -> str:
    output = io.StringIO(newline="")
    writer = csv.writer(output, lineterminator="\n")
    writer.writerow(header); writer.writerows(rows)
    return output.getvalue()


def display(value: object) -> object:
    return "" if value is None else value


def render_ids(contract: dict) -> str:
    lines = ["#pragma once", "", "/* GENERATED FILE. DO NOT EDIT.", " * Source: contract/schema/*", f" * Contract: {contract['contract_version']} / schema {contract['schema_version']} / protocol {contract['protocol_revision']}", " */", "", "#include <stdint.h>", "", f"#define SERVO_CONTRACT_SCHEMA_VERSION {contract['schema_version']}U", f"#define SERVO_CONTRACT_PROTOCOL_REVISION {contract['protocol_revision']}U", "", "typedef enum ServoContractId {"]
    for item in all_items(contract):
        lines.append(f"    SERVO_CONTRACT_{enum_name(item['name'])} = 0x{item['id']:08X}U,")
    lines += ["} ServoContractId;", "", "typedef enum ServoCapabilityId {"]
    for item in contract["capabilities"]:
        lines.append(f"    SERVO_CAPABILITY_{enum_name(item['name'])} = {item['id']}U,")
    return "\n".join(lines + ["} ServoCapabilityId;", ""])


def c_string(value: str) -> str:
    return value.replace("\\", "\\\\").replace('"', '\\"')


def render_aliases(contract: dict) -> str:
    pairs = [(item["name"], alias) for item in all_items(contract) for alias in item["aliases"]]
    lines = ["#pragma once", "", "/* GENERATED FILE. DO NOT EDIT.", " * Source: contract/schema/*", " * Canonical semantic names and compatibility aliases only.", " */", "", "#include <stddef.h>", "", "typedef struct ServoContractAlias {", "    const char* canonical;", "    const char* alias;", "} ServoContractAlias;", "", "static const ServoContractAlias SERVO_CONTRACT_ALIASES[] = {"]
    for canonical, alias in pairs:
        lines.append(f'    {{"{c_string(canonical)}", "{c_string(alias)}"}},')
    lines += ["};", "", "#define SERVO_CONTRACT_ALIAS_COUNT (sizeof(SERVO_CONTRACT_ALIASES) / sizeof(SERVO_CONTRACT_ALIASES[0]))", ""]
    return "\n".join(lines)


SEMANTIC_HEADER = ["id", "name", "aliases", "product_type", "access", "persistence", "storage_commit", "safety_preconditions", "safety_status", "unit", "physical_dimension", "physical_status", "physical_scale", "physical_offset", "range_min", "range_max", "range_status", "firmware_struct", "firmware_field", "canopen_index", "canopen_subindex", "canopen_wire_type", "canopen_access", "canopen_pdo_mappable", "canopen_conversion_kind", "canopen_conversion_status", "canopen_conversion_direction", "canopen_scale", "canopen_offset", "canopen_rounding", "canopen_overflow", "eds_parameter_name"]


def semantic_rows(items: list[dict]) -> list[list[object]]:
    rows = []
    for item in items:
        fw, co, physical, value_range = item["firmware"], item["canopen"], item["physical"], item["range"]
        conversion = co["conversion"]
        rows.append([f"0x{item['id']:08X}", item["name"], "|".join(item["aliases"]), item["product_type"], item["access"], item["persistence"], item.get("storage_commit", "none"), "|".join(item["safety_preconditions"]["required"]), item["safety_preconditions"]["status"], physical["unit"], physical["dimension"], physical["status"], display(physical["scale"]), display(physical["offset"]), display(value_range["min"]), display(value_range["max"]), value_range["status"], fw["struct"], fw["field"], co["index"], co["subindex"], co["wire_type"], co["access"], int(co["pdo_mappable"]), conversion["kind"], conversion["status"], conversion["direction"], display(conversion["scale"]), display(conversion["offset"]), conversion["rounding"], conversion["overflow"], co["eds_parameter_name"]])
    return rows


def clean_contract(contract: dict) -> dict:
    return {key: value for key, value in contract.items() if not key.startswith("_") and key != "includes"}


def render_product_metadata(contract: dict) -> str:
    keep = {key: clean_contract(contract)[key] for key in ("contract_version", "schema_version", "protocol_revision", "unit_catalog", "parameters", "signals", "capabilities")}
    return json.dumps(keep, ensure_ascii=False, separators=(",", ":")) + "\n"


def render_od_csv(contract: dict) -> str:
    rows = []
    for item in all_items(contract):
        co, conversion = item["canopen"], item["canopen"]["conversion"]
        rows.append([item["name"], co["index"], co["subindex"], co["wire_type"], EDS_TYPE_CODE.get(co["wire_type"], ""), co["access"], int(co["pdo_mappable"]), co["eds_parameter_name"], conversion["kind"], conversion["status"], conversion["direction"], display(conversion["scale"]), display(conversion["offset"])])
    return csv_text(["semantic_name", "index", "subindex", "wire_type", "eds_data_type", "access", "pdo_mappable", "eds_parameter_name", "conversion_kind", "conversion_status", "conversion_direction", "scale", "offset"], rows)


def render_eds_subset(contract: dict) -> str:
    lines = ["; GENERATED FILE. DO NOT EDIT.", "; Product Contract CANopen covered-object EDS fragment.", "; This is intentionally NOT a standalone device EDS. Runtime SlaveOD.eds", "; remains unchanged until full OD generation is migrated.", f"; Contract {contract['contract_version']} schema {contract['schema_version']}", ""]
    for item in sorted(all_items(contract), key=lambda x: (int(x["canopen"]["index"], 16), x["canopen"]["subindex"])):
        co = item["canopen"]; section = co["index"][2:].upper() + (f"sub{co['subindex']}" if co["subindex"] else "")
        dtype = EDS_TYPE_CODE.get(co["wire_type"])
        if not dtype: fail(f"{item['name']}: no EDS type code for {co['wire_type']}")
        lines += [f"; semantic={item['name']}", f"[{section}]", f"ParameterName={co['eds_parameter_name']}", "ObjectType=0x7", f"DataType={dtype}", f"AccessType={co['access']}", "DefaultValue=0", f"PDOMapping={1 if co['pdo_mappable'] else 0}", ""]
    return "\n".join(lines)


def wire_bytes(wire_type: str, value: int | float) -> str:
    if wire_type not in STRUCT_FORMAT: fail(f"golden vector unsupported wire type {wire_type}")
    return struct.pack(STRUCT_FORMAT[wire_type], value).hex().upper()


def identity_cases(value_type: str) -> list[int]:
    cases = {"int8": [-128, -1, 0, 1, 127], "uint8": [0, 1, 127, 255], "int16": [-32768, -1, 0, 1, 32767], "uint16": [0, 1, 65535], "int32": [-2147483648, -1, 0, 1, 2147483647], "uint32": [0, 1, 65535, 4294967295], "int64": [-9223372036854775808, -1, 0, 1, 9223372036854775807], "uint64": [0, 1, 4294967295, 18446744073709551615]}
    if value_type not in cases: fail(f"golden identity cases unsupported for {value_type}")
    return cases[value_type]


def render_golden_vectors(contract: dict) -> str:
    vectors = []
    for item in all_items(contract):
        co, conversion = item["canopen"], item["canopen"]["conversion"]
        if conversion["status"] != "verified": continue
        if conversion["kind"] != "identity": fail(f"{item['name']}: verified non-identity conversion needs explicit vectors")
        cases = [{"product_value": value, "wire_value": value, "wire_le_hex": wire_bytes(co["wire_type"], value), "roundtrip_product": value} for value in identity_cases(co["wire_type"])]
        vectors.append({"id": f"0x{item['id']:08X}", "name": item["name"], "product_type": item["product_type"], "wire_type": co["wire_type"], "direction": conversion["direction"], "conversion": conversion, "cases": cases})
    return json.dumps({"schema_version": contract["schema_version"], "scope": "Only verified conversions. Unverified adapter conversions are deliberately absent.", "vectors": vectors}, indent=2) + "\n"


def render_outputs(contract: dict) -> dict[Path, str]:
    generated_files = ["servo_contract_ids.h", "servo_contract_aliases.h", "product_metadata.json", "host/servo_parameters.csv", "host/servo_signals.csv", "host/error_code.csv", "host/warning_code.csv", "canopen/od_metadata.csv", "canopen/covered_objects.eds", "golden/canopen_conversion_vectors.json"]
    schema_files, bundle_sha = schema_manifest(contract)
    manifest = {"contract_version": contract["contract_version"], "schema_version": contract["schema_version"], "protocol_revision": contract["protocol_revision"], "generator_version": contract["generator_version"], "schema_git_blob_sha": next(x["git_blob_sha"] for x in schema_files if x["path"].endswith("/product_contract.json")), "schema_files": schema_files, "schema_bundle_sha256": bundle_sha, "generated_files": generated_files}
    errors = [[x["text_zh"], x["code"], x.get("cause_zh", ""), x["bit"]] for x in contract["errors"]]
    warnings = [[x["text_zh"], x["code"], x.get("cause_zh", "")] for x in contract["warnings"]]
    return {GENERATED / "servo_contract_ids.h": render_ids(contract), GENERATED / "servo_contract_aliases.h": render_aliases(contract), GENERATED / "product_metadata.json": render_product_metadata(contract), GENERATED / "host/servo_parameters.csv": csv_text(SEMANTIC_HEADER, semantic_rows(contract["parameters"])), GENERATED / "host/servo_signals.csv": csv_text(SEMANTIC_HEADER, semantic_rows(contract["signals"])), GENERATED / "host/error_code.csv": csv_text(["文本", "错误代码", "可能原因", "对应bit位（序号-1）"], errors), GENERATED / "host/warning_code.csv": csv_text(["文本", "告警代码", "可能原因"], warnings), GENERATED / "canopen/od_metadata.csv": render_od_csv(contract), GENERATED / "canopen/covered_objects.eds": render_eds_subset(contract), GENERATED / "golden/canopen_conversion_vectors.json": render_golden_vectors(contract), GENERATED / "manifest.json": json.dumps(manifest, indent=2) + "\n"}


def generate(contract: dict, check: bool) -> None:
    stale = []
    for path, content in render_outputs(contract).items():
        if check:
            if not path.exists() or path.read_text(encoding="utf-8") != content: stale.append(str(path.relative_to(path.parents[2])))
        else:
            path.parent.mkdir(parents=True, exist_ok=True); path.write_text(content, encoding="utf-8", newline="")
    if stale: fail("generated artifacts are stale:\n  " + "\n  ".join(stale))
