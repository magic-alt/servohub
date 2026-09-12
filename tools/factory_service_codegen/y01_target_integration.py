#!/usr/bin/env python3
"""Deterministically wire Factory Service into the Y01 CANopen Keil target."""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DRV = ROOT / "embedded_project/Y01/Board/drv_can_app.c"
PROJECT = ROOT / "embedded_project/Y01/MDK-ARM/STM32H743VGT6_Y01.uvprojx"

INCLUDE_BLOCK = '''#include "SlaveOD.h"\n#if defined(FACTORY_SERVICE_TRACE_USED)\n#include "../../../service/factory/canopen/factory_service_canopen.h"\n#endif'''
INIT_BLOCK = '''    setNodeId(&SlaveOD_Data, bsp_fdcan->id);\n#if defined(FACTORY_SERVICE_TRACE_USED)\n    FactoryServiceCanopenInit(&SlaveOD_Data, (uint32_t)CURRENT_FREQUENCY_HZ);\n#endif'''
SERVICE_FILES = '''\n              <File>\n                <FileName>factory_service.c</FileName>\n                <FileType>1</FileType>\n                <FilePath>..\\..\\..\\service\\factory\\factory_service.c</FilePath>\n              </File>\n              <File>\n                <FileName>factory_trace_recorder.c</FileName>\n                <FileType>1</FileType>\n                <FilePath>..\\..\\..\\service\\factory\\trace\\factory_trace_recorder.c</FilePath>\n              </File>'''
INCLUDE_PATHS = [
    "..\\..\\..\\service\\factory",
    "..\\..\\..\\service\\factory\\trace",
    "..\\..\\..\\service\\factory\\generated",
]


def transform_driver(text: str) -> str:
    if "factory_service_canopen.h" not in text:
        text = text.replace('#include "SlaveOD.h"', INCLUDE_BLOCK, 1)
    if "FactoryServiceCanopenInit(&SlaveOD_Data" not in text:
        anchor = "    setNodeId(&SlaveOD_Data, bsp_fdcan->id);"
        if anchor not in text:
            raise RuntimeError("Y01 CANopen initialization anchor not found")
        text = text.replace(anchor, INIT_BLOCK, 1)
    return text


def transform_project(text: str) -> str:
    if "factory_service.c</FileName>" not in text:
        marker = re.search(r"<FilePath>[^<]*motor_ctl_loop\.c</FilePath>", text)
        if marker is None:
            raise RuntimeError("motor_ctl_loop.c project entry not found")
        files_end = text.find("</Files>", marker.end())
        if files_end < 0:
            raise RuntimeError("enclosing </Files> not found")
        text = text[:files_end] + SERVICE_FILES + "\n            " + text[files_end:]

    def add_paths(match: re.Match[str]) -> str:
        value = match.group(1)
        parts = [part for part in value.split(";") if part]
        for path in INCLUDE_PATHS:
            if path not in parts:
                parts.append(path)
        return f"<IncludePath>{';'.join(parts)}</IncludePath>"

    text = re.sub(r"<IncludePath>(.*?)</IncludePath>", add_paths, text)

    def add_define(match: re.Match[str]) -> str:
        value = match.group(1)
        if "USE_CANOPEN" not in value or "FACTORY_SERVICE_TRACE_USED" in value:
            return match.group(0)
        separator = "," if "," in value else " "
        return f"<Define>{value}{separator}FACTORY_SERVICE_TRACE_USED</Define>"

    return re.sub(r"<Define>(.*?)</Define>", add_define, text)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("apply", "check"))
    args = parser.parse_args()
    expected = {
        DRV: transform_driver(DRV.read_text(encoding="utf-8")),
        PROJECT: transform_project(PROJECT.read_text(encoding="utf-8")),
    }
    if args.command == "apply":
        for path, content in expected.items():
            path.write_text(content, encoding="utf-8", newline="\n")
        return 0
    stale = [path for path, content in expected.items() if path.read_text(encoding="utf-8") != content]
    if stale:
        for path in stale:
            print(f"stale Y01 Factory Service integration: {path.relative_to(ROOT)}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
