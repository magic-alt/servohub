#!/usr/bin/env python3
"""Synchronize Factory Service CANopen objects from the canonical schema into SlaveOD.eds."""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[2]
SCHEMA = ROOT / "service/factory/schema/factory_service_v1.json"
EDS = ROOT / "communication/protocol/CANopen/SlaveOD/SlaveOD.eds"
TYPE_CODE = {"int32": "0x0004", "uint8": "0x0005", "uint16": "0x0006", "uint32": "0x0007", "float32": "0x0008"}
SECTION_RE = re.compile(r"^\[([0-9A-Fa-f]{4})(?:sub\d+)?\]$")


def _render_entry(name: str, type_name: str, access: str, default: Any) -> list[str]:
    return [
        f"ParameterName={name}",
        "ObjectType=0x7",
        f"DataType={TYPE_CODE[type_name]}",
        f"AccessType={access}",
        f"DefaultValue={default}",
        "PDOMapping=0",
    ]


def _render_object(obj: dict[str, Any]) -> list[str]:
    index = int(obj["index"], 0)
    key = f"{index:04X}"
    if obj["object_type"] == "variable":
        return [f"[{key}]", *_render_entry(obj["name"], obj["type"], obj["access"], obj["default"]), ""]

    subs = obj["subindices"]
    lines = [f"[{key}]", f"ParameterName={obj['name']}", "ObjectType=0x9", f"SubNumber={len(subs)}", ""]
    for sub in subs:
        lines.extend(
            [
                f"[{key}sub{int(sub['subindex'])}]",
                *_render_entry(sub["name"], sub["type"], sub["access"], sub["default"]),
                "",
            ]
        )
    return lines


def _strip_owned_sections(lines: list[str], owned: set[int]) -> list[str]:
    out: list[str] = []
    skipping = False
    for line in lines:
        match = SECTION_RE.match(line.strip())
        if match:
            skipping = int(match.group(1), 16) in owned
        if not skipping:
            out.append(line)
    return out


def _rewrite_optional_objects(lines: list[str], owned_indices: list[int]) -> list[str]:
    start = lines.index("[OptionalObjects]")
    end = start + 1
    while end < len(lines) and not (lines[end].startswith("[") and lines[end].endswith("]")):
        end += 1
    existing: list[int] = []
    for line in lines[start + 1 : end]:
        match = re.match(r"^\d+=0x([0-9A-Fa-f]+)$", line.strip())
        if match:
            value = int(match.group(1), 16)
            if value not in owned_indices:
                existing.append(value)
    values = existing + sorted(owned_indices)
    replacement = ["[OptionalObjects]", f"SupportedObjects={len(values)}"]
    replacement.extend(f"{number}=0x{value:04X}" for number, value in enumerate(values, start=1))
    replacement.append("")
    return lines[:start] + replacement + lines[end:]


def render(current: str, schema: dict[str, Any]) -> str:
    objects = schema["canopen_binding"]["objects"]
    owned = [int(obj["index"], 0) for obj in objects]
    lines = current.replace("\r\n", "\n").splitlines()
    lines = _strip_owned_sections(lines, set(owned))
    lines = _rewrite_optional_objects(lines, owned)
    while lines and not lines[-1].strip():
        lines.pop()
    lines.extend([""])
    for obj in objects:
        lines.extend(_render_object(obj))
    return "\n".join(lines).rstrip() + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("apply", "check"))
    args = parser.parse_args()
    schema = json.loads(SCHEMA.read_text(encoding="utf-8"))
    current = EDS.read_text(encoding="utf-8")
    expected = render(current, schema)
    if args.command == "apply":
        EDS.write_text(expected, encoding="utf-8", newline="\n")
        return 0
    if current.replace("\r\n", "\n") != expected:
        print("SlaveOD.eds is stale relative to Factory Service schema", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
