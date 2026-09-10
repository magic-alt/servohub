#!/usr/bin/env python3
"""Validate, generate and check the ServoHub product contract (stdlib only)."""
from __future__ import annotations

import argparse
import json
import struct
import sys

from checks import check_golden_vectors, check_mavlink_provenance, check_sources
from generators import generate
from schema_model import load_contract, validate


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("command", choices=("validate", "generate", "check", "sources", "golden", "mavlink", "all"))
    args = parser.parse_args()
    try:
        contract = load_contract(); validate(contract)
        if args.command == "generate": generate(contract, check=False)
        elif args.command == "check": generate(contract, check=True)
        elif args.command == "sources": check_sources(contract)
        elif args.command == "golden": generate(contract, check=True); check_golden_vectors(contract)
        elif args.command == "mavlink": check_mavlink_provenance()
        elif args.command == "all": generate(contract, check=True); check_sources(contract); check_golden_vectors(contract); check_mavlink_provenance()
    except (OSError, ValueError, json.JSONDecodeError, struct.error) as exc:
        print(f"product-contract: FAIL: {exc}", file=sys.stderr); return 1
    print(f"product-contract: PASS ({args.command})"); return 0


if __name__ == "__main__":
    raise SystemExit(main())
