#!/usr/bin/env python3
"""Validate, generate, and freshness-check the ServoHub product contract."""
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
SCHEMA = ROOT / "contract/schema/product_contract.json"
GENERATED = ROOT / "contract/generated"
DATA_PARAM = ROOT / "database/data_param.h"
EDS = ROOT / "communication/protocol/CANopen/SlaveOD/SlaveOD.eds"
PRODUCT_TYPES = {"bool", "int8", "uint8", "int16", "uint16", "int32", "uint32",
                 "int64", "uint64", "float32", "float64", "string", "bytes"}
ACCESS = {"ro", "rw", "wo"}
WIRE_TYPES = {"int8", "uint8", "int16", "uint16", "int32", "uint32",
              "int64", "uint64", "float32", "float64", "bytes"}


def fail(message: str) -> None:
    raise ValueError(message)


def load_contract() -> dict:
    return json.loads(SCHEMA.read_text(encoding="utf-8"))


def normalized_index(index: str) -> str:
    return "0x" + index[2:].upper()


def git_blob_sha(path: Path) -> str:
    data = path.read_bytes()
    header = f"blob {len(data)}\0".encode("ascii")
    return hashlib.sha1(header + data).hexdigest()


def validate(contract: dict) -> None:
    required = ("contract_version", "schema_version", "protocol_revision",
                "generator_version", "parameters", "signals", "errors",
                "warnings", "capabilities")
    missing = [key for key in required if key not in contract]
    if missing:
        fail("missing top-level keys: " + ", ".join(missing))
    if contract.get("ownership", {}).get("canonical_repository") != "magic-alt/servohub":
        fail("canonical_repository must be magic-alt/servohub")

    ids: set[int] = set()
    names: set[str] = set()
    addresses: set[tuple[str, int]] = set()
    for kind in ("parameters", "signals"):
        for item in contract[kind]:
            item_id, name = item.get("id"), item.get("name")
            if not isinstance(item_id, int) or item_id <= 0 or item_id in ids:
                fail(f"{kind}: invalid/duplicate id for {name!r}")
            if not isinstance(name, str) or not name or name in names:
                fail(f"{kind}: invalid/duplicate name {name!r}")
            ids.add(item_id)
            names.add(name)
            if item.get("product_type") not in PRODUCT_TYPES or item.get("access") not in ACCESS:
                fail(f"{name}: invalid product type/access")
            fw = item.get("firmware", {})
            if fw.get("source") != "database/data_param.h" or not fw.get("struct") or not fw.get("field"):
                fail(f"{name}: incomplete firmware provenance")
            co = item.get("canopen")
            if co:
                index, subindex = co.get("index"), co.get("subindex")
                if (not isinstance(index, str) or not re.fullmatch(r"0x[0-9A-Fa-f]{4}", index)
                        or not isinstance(subindex, int) or not 0 <= subindex <= 255
                        or co.get("wire_type") not in WIRE_TYPES
                        or not co.get("eds_parameter_name")):
                    fail(f"{name}: invalid CANopen binding")
                address = (normalized_index(index), subindex)
                if address in addresses:
                    fail(f"duplicate CANopen address: {address[0]}:{address[1]}")
                addresses.add(address)

    for kind in ("errors", "warnings"):
        codes: set[str] = set()
        for item in contract[kind]:
            code = item.get("code")
            if not isinstance(code, str) or not code or code in codes:
                fail(f"{kind}: invalid/duplicate code {code!r}")
            codes.add(code)
            if not item.get("name") or not item.get("text_zh"):
                fail(f"{kind}: incomplete entry {code}")

    cap_ids: set[int] = set()
    cap_names: set[str] = set()
    for item in contract["capabilities"]:
        if item.get("id") in cap_ids or item.get("name") in cap_names:
            fail("duplicate capability")
        cap_ids.add(item["id"])
        cap_names.add(item["name"])


def enum_name(name: str) -> str:
    return re.sub(r"[^A-Za-z0-9]+", "_", name).strip("_").upper()


def render_ids(contract: dict) -> str:
    lines = ["#pragma once", "", "/* GENERATED FILE. DO NOT EDIT.",
             " * Source: contract/schema/product_contract.json",
             f" * Contract: {contract['contract_version']} / schema {contract['schema_version']} / protocol {contract['protocol_revision']}",
             " */", "", "#include <stdint.h>", "",
             f"#define SERVO_CONTRACT_SCHEMA_VERSION {contract['schema_version']}U",
             f"#define SERVO_CONTRACT_PROTOCOL_REVISION {contract['protocol_revision']}U",
             "", "typedef enum ServoContractId {"]
    for item in contract["parameters"] + contract["signals"]:
        lines.append(f"    SERVO_CONTRACT_{enum_name(item['name'])} = 0x{item['id']:08X}U,")
    lines += ["} ServoContractId;", "", "typedef enum ServoCapabilityId {"]
    for item in contract["capabilities"]:
        lines.append(f"    SERVO_CAPABILITY_{enum_name(item['name'])} = {item['id']}U,")
    return "\n".join(lines + ["} ServoCapabilityId;", ""])


def csv_text(header: list[str], rows: list[list[object]]) -> str:
    output = io.StringIO(newline="")
    writer = csv.writer(output, lineterminator="\n")
    writer.writerow(header)
    writer.writerows(rows)
    return output.getvalue()


def render_outputs(contract: dict) -> dict[Path, str]:
    parameter_rows = []
    for item in contract["parameters"]:
        fw, co = item["firmware"], item["canopen"]
        parameter_rows.append([
            f"0x{item['id']:08X}", item["name"], item["product_type"], item["access"],
            int(item["persistent"]), int(item["requires_disabled"]), fw["struct"], fw["field"],
            co["index"], co["subindex"], co["wire_type"], co["conversion"], co["eds_parameter_name"]])
    error_rows = [[x["text_zh"], x["code"], x.get("cause_zh", ""), x["bit"]]
                  for x in contract["errors"]]
    warning_rows = [[x["text_zh"], x["code"], x.get("cause_zh", "")]
                    for x in contract["warnings"]]
    manifest = {
        "contract_version": contract["contract_version"],
        "schema_version": contract["schema_version"],
        "protocol_revision": contract["protocol_revision"],
        "generator_version": contract["generator_version"],
        "schema_git_blob_sha": git_blob_sha(SCHEMA),
        "generated_files": ["servo_contract_ids.h", "host/servo_parameters.csv",
                            "host/error_code.csv", "host/warning_code.csv"]
    }
    return {
        GENERATED / "servo_contract_ids.h": render_ids(contract),
        GENERATED / "host/servo_parameters.csv": csv_text(
            ["id", "name", "product_type", "access", "persistent", "requires_disabled",
             "firmware_struct", "firmware_field", "canopen_index", "canopen_subindex",
             "canopen_wire_type", "canopen_conversion", "eds_parameter_name"], parameter_rows),
        GENERATED / "host/error_code.csv": csv_text(
            ["文本", "错误代码", "可能原因", "对应bit位（序号-1）"], error_rows),
        GENERATED / "host/warning_code.csv": csv_text(["文本", "告警代码", "可能原因"], warning_rows),
        GENERATED / "manifest.json": json.dumps(manifest, indent=2) + "\n"
    }


def generate(contract: dict, check: bool) -> None:
    stale = []
    for path, content in render_outputs(contract).items():
        if check:
            if not path.exists() or path.read_text(encoding="utf-8") != content:
                stale.append(str(path.relative_to(ROOT)))
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content, encoding="utf-8", newline="")
    if stale:
        fail("generated artifacts are stale:\n  " + "\n  ".join(stale))


def parse_eds(text: str) -> dict[tuple[str, int], dict[str, str]]:
    current = None
    result = {}
    for raw in text.splitlines():
        line = raw.strip()
        match = re.fullmatch(r"\[([0-9A-Fa-f]{4})(?:sub([0-9]+))?\]", line)
        if match:
            current = ("0x" + match.group(1).upper(), int(match.group(2) or 0))
            result[current] = {}
        elif current and "=" in line:
            key, value = line.split("=", 1)
            result[current][key.strip()] = value.strip()
    return result


def check_sources(contract: dict) -> None:
    data_text = DATA_PARAM.read_text(encoding="utf-8")
    eds = parse_eds(EDS.read_text(encoding="utf-8"))
    problems = []
    for item in contract["parameters"] + contract["signals"]:
        name, field, co = item["name"], item["firmware"]["field"], item.get("canopen")
        if not re.search(rf"\b{re.escape(field)}\b", data_text):
            problems.append(f"{name}: firmware field {field} not found")
        if co:
            key = (normalized_index(co["index"]), co["subindex"])
            section = eds.get(key)
            if not section:
                problems.append(f"{name}: EDS section {key[0]}:{key[1]} not found")
            elif section.get("ParameterName") != co["eds_parameter_name"]:
                problems.append(f"{name}: EDS name drift at {key[0]}:{key[1]}")
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
            check_sources(contract)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"product-contract: FAIL: {exc}", file=sys.stderr)
        return 1
    print(f"product-contract: PASS ({args.command})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
