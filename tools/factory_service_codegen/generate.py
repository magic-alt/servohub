#!/usr/bin/env python3
"""Generate Factory Service C identifiers and CANopen binding manifest."""
from __future__ import annotations
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SCHEMA = ROOT / "service/factory/schema/factory_service_v1.json"
HEADER = ROOT / "service/factory/generated/factory_service_ids.h"
CANOPEN = ROOT / "service/factory/generated/factory_service_canopen.json"

def macro_name(prefix: str, name: str) -> str:
    token = re.sub(r"[^A-Za-z0-9]+", "_", name).strip("_").upper()
    return f"{prefix}_{token}"

def render_header(schema: dict) -> str:
    lines = ["/* Generated from service/factory/schema/factory_service_v1.json. Do not hand edit. */", "#ifndef SERVOHUB_FACTORY_SERVICE_IDS_H", "#define SERVOHUB_FACTORY_SERVICE_IDS_H", "", "#include <stdint.h>", ""]
    for cap in schema["capabilities"]:
        lines.append(f"#define {macro_name('FACTORY_SERVICE_CAP', cap['name'])} (UINT32_C(1) << {int(cap['bit'])})")
    lines.extend(["", "/* Service-plane diagnostic identifiers. */"])
    for item in schema["diagnostics"]:
        lines.append(f"#define {macro_name('FACTORY_DIAG', item['name'])} UINT16_C({item['id']})")
    lines.extend(["", "/* Trace signal identifiers. */"])
    for item in schema["trace"]["signals"]:
        lines.append(f"#define {macro_name('FACTORY_TRACE_SIGNAL', item['name'])} UINT16_C({item['id']})")
    lines.extend(["", "/* Manufacturer-specific CANopen reservation. */"])
    for item in schema["canopen_binding"]["objects"]:
        lines.append(f"#define {macro_name('FACTORY_SERVICE_CANOPEN', item['name'])} UINT16_C({item['index']})")
    lines.extend(["", "#endif", ""])
    return "\n".join(lines)

def render_canopen(schema: dict) -> str:
    payload = {"schema": schema["service"]["name"], "schema_version": schema["service"]["schema_version"], "protocol_revision": schema["service"]["protocol_revision"], "binding": schema["canopen_binding"]}
    return json.dumps(payload, indent=2, sort_keys=True) + "\n"

def generate(check: bool) -> int:
    schema = json.loads(SCHEMA.read_text(encoding="utf-8"))
    expected = {HEADER: render_header(schema), CANOPEN: render_canopen(schema)}
    stale = []
    for path, content in expected.items():
        if check:
            if not path.exists() or path.read_text(encoding="utf-8") != content:
                stale.append(path)
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content, encoding="utf-8", newline="\n")
    if stale:
        for path in stale:
            print(f"stale generated artifact: {path.relative_to(ROOT)}", file=sys.stderr)
        return 1
    return 0

def main() -> int:
    command = sys.argv[1] if len(sys.argv) > 1 else "check"
    if command == "generate": return generate(False)
    if command == "check": return generate(True)
    raise SystemExit("usage: generate.py [generate|check]")

if __name__ == "__main__": raise SystemExit(main())
