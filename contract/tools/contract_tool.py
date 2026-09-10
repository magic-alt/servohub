#!/usr/bin/env python3
"""Validate, generate and check the ServoHub product contract.

The tool intentionally uses only the Python standard library so the contract
freshness gate can run independently of firmware toolchains.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import io
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SCHEMA = ROOT / "contract" / "schema" / "product_contract.json"
GENERATED = ROOT / "contract" / "generated"
DATA_PARAM = ROOT / "database" / "data_param.h"
EDS = ROOT / "communication" / "protocol" / "CANopen" / "SlaveOD" / "SlaveOD.eds"

PRODUCT_TYPES = {"bool", "int8", "uint8", "int16", "uint16", "int32", "uint32",
                 "int64", "uint64", "float32", "float64", "string", "bytes"}
ACCESS = {"ro", "rw", "wo"}
WIRE_TYPES = {"int8", "uint8", "int16", "uint16", "int32", "uint32",
              "int64", "uint64", "float32", "float64", "bytes"}


def load_contract() -> dict:
    with SCHEMA.open("r", encoding="utf-8") as handle:
        return json.load(handle)


def fail(message: str) -> None:
    raise ValueError(message)


def normalized_index(index: str) -> str:
    return "0x" + index[2:].upper()


def validate(contract: dict) -> None:
    for key in ("contract_version", "schema_version", "protocol_revision",
                "generator_version", "parameters", "signals", "errors",
                "warnings", "capabilities"):
        if key not in contract:
            fail(f"missing top-level key: {key}")
    if contract.get("ownership", {}).get("canonical_repository") != "magic-alt/servohub":
        fail("canonical_repository must be magic-alt/servohub")

    seen_ids: set[int] = set()
    seen_names: set[str] = set()
    seen_canopen: set[tuple[str, int]] = set()
    for kind in ("parameters", "signals"):
        for item in contract[kind]:
            item_id = item.get("id")
            name = item.get("name")
            if not isinstance(item_id, int) or item_id <= 0:
                fail(f"{kind}: invalid id for {name!r}")
            if item_id in seen_ids:
                fail(f"duplicate product id: {item_id}")
            seen_ids.add(item_id)
            if not isinstance(name, str) or not name or name in seen_names:
                fail(f"duplicate/invalid semantic name: {name!r}")
            seen_names.add(name)
            if item.get("product_type") not in PRODUCT_TYPES:
                fail(f"{name}: unsupported product_type")
            if item.get("access") not in ACCESS:
                fail(f"{name}: unsupported access")
            fw = item.get("firmware", {})
            if fw.get("source") != "database/data_param.h" or not fw.get("struct") or not fw.get("field"):
                fail(f"{name}: incomplete firmware provenance")
            co = item.get("canopen")
            if co:
                if co.get("wire_type") not in WIRE_TYPES:
                    fail(f"{name}: unsupported CANopen wire_type")
                index = co.get("index")
                subindex = co.get("subindex")
                if not isinstance(index, str) or not re.fullmatch(r"0x[0-9A-Fa-f]{4}", index):
                    fail(f"{name}: invalid CANopen index")
                if not isinstance(subindex, int) or not 0 <= subindex <= 255:
                    fail(f"{name}: invalid CANopen subindex")
                address = (normalized_index(index), subindex)
                if address in seen_canopen:
                    fail(f"duplicate CANopen address: {address[0]}:{address[1]}")
                seen_canopen.add(address)
                if not co.get("eds_parameter_name"):
                    fail(f"{name}: missing EDS parameter name")

    for kind in ("errors", "warnings"):
        seen_codes: set[str] = set()
        for item in contract[kind]:
            code = item.get("code")
            if not isinstance(code, str) or not code:
                fail(f"{kind}: invalid diagnostic code")
            if code in seen_codes:
                fail(f"{kind}: duplicate diagnostic code {code}")
            seen_codes.add(code)
            if not item.get("name") or not item.get("text_zh"):
                fail(f"{kind}: incomplete diagnostic entry {code}")

    capability_ids: set[int] = set()
    capability_names: set[str] = set()
    for item in contract["capabilities"]:
        if item.get("id") in capability_ids or item.get("name") in capability_names:
            fail("duplicate capability")
        capability_ids.add(item["id"])
        capability_names.add(item["name"])


def enum_name(name: str) -> str:
    return re.sub(r"[^A-Za-z0-9]+", "_", name).strip("_").upper()


def render_ids_header(contract: dict) -> str:
    lines = [
        "#pragma once", "",
        "/* GENERATED FILE. DO NOT EDIT.",
        " * Source: contract/schema/product_contract.json",
        f" * Contract: {contract['contract_version']} / schema {contract['schema_version']} / protocol {contract['protocol_revision']}",
        " */", "", "#include <stdint.h>", "",
        f"#define SERVO_CONTRACT_SCHEMA_VERSION {contract['schema_version']}U",
        f"#define SERVO_CONTRACT_PROTOCOL_REVISION {contract['protocol_revision']}U",
        "", "typedef enum ServoContractId {",
    ]
    for item in contract["parameters"] + contract["signals"]:
        lines.append(f"    SERVO_CONTRACT_{enum_name(item['name'])} = 0x{item['id']:08X}U,")
    lines += ["} ServoContractId;", "", "typedef enum ServoCapabilityId {"]
    for item in contract["capabilities"]:
        lines.append(f"    SERVO_CAPABILITY_{enum_name(item['name'])} = {item['id']}U,")
    lines += ["} ServoCapabilityId;", ""]
    return "\n".join(lines)


def render_parameters_csv(contract: dict) -> str:
    out = io.StringIO(newline="")
    writer = csv.writer(out, lineterminator="\n")
    writer.writerow(["id", "name", "product_type", "access", "persistent",
                     "requires_disabled", "firmware_struct", "firmware_field",
                     "canopen_index", "canopen_subindex", "canopen_wire_type",
                     "canopen_conversion", "eds_parameter_name"])
    for item in contract["parameters"]:
        co = item["canopen"]
        fw = item["firmware"]
        writer.writerow([f"0x{item['id']:08X}", item["name"], item["product_type"],
                         item["access"], int(item["persistent"]),
                         int(item["requires_disabled"]), fw["struct"], fw["field"],
                         co["index"], co["subindex"], co["wire_type"],
                         co["conversion"], co["eds_parameter_name"]])
    return out.getvalue()


def render_error_csv(contract: dict) -> str:
    out = io.StringIO(newline="")
    writer = csv.writer(out, lineterminator="\n")
    writer.writerow(["文本", "错误代码", "可能原因", "对应bit位（序号-1）"])
    for item in contract["errors"]:
        writer.writerow([item["text_zh"], item["code"], item.get("cause_zh", ""), item["bit"]])
    return out.getvalue()


def render_warning_csv(contract: dict) -> str:
    out = io.StringIO(newline="")
    writer = csv.writer(out, lineterminator="\n")
    writer.writerow(["文本", "告警代码", "可能原因"])
    for item in contract["warnings"]:
        writer.writerow([item["text_zh"], item["code"], item.get("cause_zh", "")])
    return out.getvalue()


def render_outputs(contract: dict) -> dict[Path, str]:
    schema_sha = hashlib.sha256(SCHEMA.read_bytes()).hexdigest()
    manifest = {
        "contract_version": contract["contract_version"],
        "schema_version": contract["schema_version"],
        "protocol_revision": contract["protocol_revision"],
        "generator_version": contract["generator_version"],
        "schema_sha256": schema_sha,
        "generated_files": [
            "servo_contract_ids.h",
            "host/servo_parameters.csv",
            "host/error_code.csv",
            "host/warning_code.csv"
        ]
    }
    return {
        GENERATED / "servo_contract_ids.h": render_ids_header(contract),
        GENERATED / "host" / "servo_parameters.csv": render_parameters_csv(contract),
        GENERATED / "host" / "error_code.csv": render_error_csv(contract),
        GENERATED / "host" / "warning_code.csv": render_warning_csv(contract),
        GENERATED / "manifest.json": json.dumps(manifest, indent=2) + "\n"
    }


def generate(contract: dict, check: bool) -> None:
    stale: list[str] = []
    for path, content in render_outputs(contract).items():
        if check:
            if not path.exists() or path.read_text(encoding="utf-8") != content:
                stale.append(str(path.relative_to(ROOT)))
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content, encoding="utf-8", newline="")
    if stale:
        fail("generated contract artifacts are stale:\n  " + "\n  ".join(stale))


def parse_eds(text: str) -> dict[tuple[str, int], dict[str, str]]:
    current: tuple[str, int] | None = None
    result: dict[tuple[str, int], dict[str, str]] = {}
    for raw in text.splitlines():
        line = raw.strip()
        match = re.fullmatch(r"\[([0-9A-Fa-f]{4})(?:sub([0-9]+))?\]", line)
        if match:
            current = ("0x" + match.group(1).upper(), int(match.group(2) or 0))
            result[current] = {}
            continue
        if current and "=" in line:
            key, value = line.split("=", 1)
            result[current][key.strip()] = value.strip()
    return result


def check_firmware_sources(contract: dict) -> None:
    data_text = DATA_PARAM.read_text(encoding="utf-8")
    eds = parse_eds(EDS.read_text(encoding="utf-8"))
    problems: list[str] = []
    for kind in ("parameters", "signals"):
        for item in contract[kind]:
            name = item["name"]
            field = item["firmware"]["field"]
            if not re.search(rf"\b{re.escape(field)}\b", data_text):
                problems.append(f"{name}: firmware field {field} not found")
            co = item.get("canopen")
            if not co:
                continue
            key = (normalized_index(co["index"]), co["subindex"])
            section = eds.get(key)
            if not section:
                problems.append(f"{name}: EDS section {key[0]}:{key[1]} not found")
            elif section.get("ParameterName") != co["eds_parameter_name"]:
                problems.append(
                    f"{name}: EDS name drift at {key[0]}:{key[1]}: "
                    f"{section.get('ParameterName')!r} != {co['eds_parameter_name']!r}")
    if problems:
        fail("firmware/EDS drift detected:\n  " + "\n  ".join(problems))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("command", choices=("validate", "generate", "check", "all"))
    args = parser.parse_args()
    try:
        contract = load_contract()
        validate(contract)
        if args.command == "generate":
            generate(contract, check=False)
        elif args.command == "check":
            generate(contract, check=True)
        elif args.command == "all":
            generate(contract, check=True)
            check_firmware_sources(contract)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"product-contract: FAIL: {exc}", file=sys.stderr)
        return 1
    print(f"product-contract: PASS ({args.command})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
