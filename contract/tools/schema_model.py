from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SCHEMA_ROOT = ROOT / "contract" / "schema"
SCHEMA = SCHEMA_ROOT / "product_contract.json"
GENERATED = ROOT / "contract" / "generated"
DATA_PARAM = ROOT / "database" / "data_param.h"
EDS = ROOT / "communication" / "protocol" / "CANopen" / "SlaveOD" / "SlaveOD.eds"
MAVLINK_ROOT = ROOT / "communication" / "protocol" / "MAVLink" / "servo_hub_database"
MAVLINK_PROVENANCE = ROOT / "contract" / "protocol" / "mavlink_provenance.json"

PRODUCT_TYPES = {"bool", "int8", "uint8", "int16", "uint16", "int32", "uint32", "int64", "uint64", "float32", "float64", "string", "bytes"}
WIRE_TYPES = {"int8", "uint8", "int16", "uint16", "int32", "uint32", "int64", "uint64", "float32", "float64", "bytes"}
ACCESS = {"ro", "rw", "wo"}
PERSISTENCE = {"volatile", "nonvolatile"}
PHYSICAL_STATUS = {"verified", "inferred", "unverified"}
RANGE_STATUS = {"verified", "declared", "unspecified"}
SAFETY_STATUS = {"verified", "declared_phase1", "unverified", "not_applicable"}
CONVERSION_STATUS = {"verified", "unverified"}
CONVERSION_KIND = {"identity", "linear", "parameterized_linear", "adapter_defined"}
CONVERSION_DIRECTION = {"bidirectional", "product_to_wire", "wire_to_product"}
CONVERSION_OVERFLOW = {"reject", "firmware_cast"}
CONVERSION_ROUNDING = {"exact", "truncate_toward_zero", "adapter_defined"}
EDS_TYPE_CODE = {"int8": "0x0002", "int16": "0x0003", "int32": "0x0004", "uint8": "0x0005", "uint16": "0x0006", "uint32": "0x0007", "float32": "0x0008"}
STRUCT_FORMAT = {"int8": "<b", "uint8": "<B", "int16": "<h", "uint16": "<H", "int32": "<i", "uint32": "<I", "int64": "<q", "uint64": "<Q", "float32": "<f", "float64": "<d"}


def fail(message: str) -> None:
    raise ValueError(message)


def git_blob_sha(path: Path) -> str:
    data = path.read_bytes()
    return hashlib.sha1(f"blob {len(data)}\0".encode() + data).hexdigest()


def normalized_index(index: str) -> str:
    return "0x" + index[2:].upper()


def enum_name(name: str) -> str:
    return re.sub(r"[^A-Za-z0-9]+", "_", name).strip("_").upper()


def load_contract() -> dict:
    root = json.loads(SCHEMA.read_text(encoding="utf-8"))
    includes = root.get("includes")
    if not isinstance(includes, dict):
        fail("root schema must declare includes")
    required = {"parameters", "signals", "diagnostics", "capabilities"}
    if set(includes) != required:
        fail(f"schema includes must be exactly {sorted(required)}")
    paths: list[Path] = [SCHEMA]
    contract = dict(root)
    for key, relative in includes.items():
        if not isinstance(relative, str) or Path(relative).is_absolute() or ".." in Path(relative).parts:
            fail(f"invalid schema include {key}: {relative!r}")
        path = SCHEMA_ROOT / relative
        paths.append(path)
        payload = json.loads(path.read_text(encoding="utf-8"))
        if key == "diagnostics":
            contract["errors"] = payload["errors"]
            contract["warnings"] = payload["warnings"]
        else:
            contract[key] = payload
    contract["_schema_paths"] = paths
    return contract


def schema_manifest(contract: dict) -> tuple[list[dict[str, str]], str]:
    entries = []
    digest = hashlib.sha256()
    for path in sorted(contract["_schema_paths"], key=lambda p: str(p.relative_to(ROOT))):
        rel = str(path.relative_to(ROOT)).replace("\\", "/")
        data = path.read_bytes()
        entries.append({"path": rel, "git_blob_sha": git_blob_sha(path)})
        digest.update(rel.encode("utf-8") + b"\0" + data + b"\0")
    return entries, digest.hexdigest()


def all_items(contract: dict) -> list[dict]:
    return contract["parameters"] + contract["signals"]


def validate_physical(name: str, item: dict, units: dict) -> None:
    physical = item.get("physical")
    if not isinstance(physical, dict):
        fail(f"{name}: physical metadata required")
    for key in ("unit", "dimension", "scale", "offset", "status"):
        if key not in physical:
            fail(f"{name}: physical.{key} must be explicit")
    if physical["unit"] not in units or physical["status"] not in PHYSICAL_STATUS:
        fail(f"{name}: invalid physical unit/status")
    if physical["status"] == "unverified":
        if physical["scale"] is not None or physical["offset"] is not None:
            fail(f"{name}: unverified physical scale/offset must remain null")
    elif not isinstance(physical["scale"], (int, float)) or not isinstance(physical["offset"], (int, float)):
        fail(f"{name}: verified/inferred physical scale/offset must be numeric")


def validate_range(name: str, item: dict) -> None:
    value_range = item.get("range")
    if not isinstance(value_range, dict) or set(value_range) != {"min", "max", "status"}:
        fail(f"{name}: range must explicitly contain min/max/status")
    if value_range["status"] not in RANGE_STATUS:
        fail(f"{name}: invalid range status")
    if value_range["status"] == "unspecified" and (value_range["min"] is not None or value_range["max"] is not None):
        fail(f"{name}: unspecified range must not invent limits")
    if value_range["min"] is not None and value_range["max"] is not None and value_range["min"] > value_range["max"]:
        fail(f"{name}: range min exceeds max")


def validate_conversion(name: str, item: dict, co: dict) -> None:
    conversion = co.get("conversion")
    if not isinstance(conversion, dict):
        fail(f"{name}: conversion specification required")
    required = {"kind", "status", "direction", "scale", "offset", "rounding", "overflow"}
    optional = {"dependencies", "formula_id", "golden_context", "evidence", "standard_semantics"}
    if not required <= set(conversion) or set(conversion) - required - optional:
        fail(f"{name}: invalid conversion specification keys")
    if conversion["kind"] not in CONVERSION_KIND or conversion["status"] not in CONVERSION_STATUS or conversion["direction"] not in CONVERSION_DIRECTION:
        fail(f"{name}: invalid conversion kind/status/direction")
    if conversion["overflow"] not in CONVERSION_OVERFLOW or conversion["rounding"] not in CONVERSION_ROUNDING:
        fail(f"{name}: invalid conversion overflow/rounding policy")
    if conversion["status"] == "unverified":
        if conversion["kind"] != "adapter_defined" or conversion["scale"] is not None or conversion["offset"] is not None:
            fail(f"{name}: unverified conversion must be adapter_defined with null scale/offset")
        if conversion["rounding"] != "adapter_defined":
            fail(f"{name}: unverified conversion rounding must remain adapter_defined")
        return
    if conversion["kind"] == "identity":
        if item["product_type"] != co["wire_type"] or conversion["scale"] != 1.0 or conversion["offset"] != 0.0 or conversion["rounding"] != "exact":
            fail(f"{name}: verified identity conversion must be same type, scale=1, offset=0, exact")
    elif conversion["kind"] == "linear":
        if not isinstance(conversion["scale"], (int, float)) or not isinstance(conversion["offset"], (int, float)):
            fail(f"{name}: verified linear conversion requires numeric scale/offset")
    elif conversion["kind"] == "parameterized_linear":
        deps = conversion.get("dependencies")
        context = conversion.get("golden_context")
        if conversion["scale"] is not None or not isinstance(conversion["offset"], (int, float)):
            fail(f"{name}: parameterized conversion keeps fixed scale null and explicit numeric offset")
        if not isinstance(deps, list) or not deps or any(not isinstance(x, str) or not x for x in deps):
            fail(f"{name}: parameterized conversion requires dependencies")
        if not isinstance(context, dict) or any(dep not in context for dep in deps):
            fail(f"{name}: parameterized conversion requires deterministic golden context")
        if conversion.get("formula_id") not in {"load_pps_to_rpm", "rated_current_per_mille_peak"}:
            fail(f"{name}: unsupported parameterized conversion formula")
    else:
        fail(f"{name}: adapter_defined conversion cannot be marked verified")
    evidence = conversion.get("evidence")
    if conversion["kind"] != "identity" and (not isinstance(evidence, dict) or evidence.get("status") != "firmware_verified"):
        fail(f"{name}: verified non-identity conversion requires firmware evidence")

def validate(contract: dict) -> None:
    required_top = {"contract_version", "schema_version", "protocol_revision", "generator_version", "status", "ownership", "coverage", "unit_catalog", "parameters", "signals", "errors", "warnings", "capabilities"}
    missing = required_top - set(contract)
    if missing:
        fail(f"missing top-level keys: {sorted(missing)}")
    if contract["ownership"].get("canonical_repository") != "magic-alt/servohub":
        fail("canonical repository must remain magic-alt/servohub")
    if contract["schema_version"] != 3 or contract["generator_version"] != 3:
        fail("Phase 1c expects schema_version=3 and generator_version=3")
    if not isinstance(contract["unit_catalog"], dict) or not contract["unit_catalog"]:
        fail("unit_catalog must be non-empty")

    ids: set[int] = set(); names: set[str] = set(); addresses: set[tuple[str, int]] = set(); units = contract["unit_catalog"]
    for kind in ("parameters", "signals"):
        for item in contract[kind]:
            item_id, name = item.get("id"), item.get("name")
            if not isinstance(item_id, int) or item_id <= 0 or item_id in ids:
                fail(f"{kind}: invalid/duplicate id for {name!r}")
            if not isinstance(name, str) or not name or name in names:
                fail(f"{kind}: invalid/duplicate name {name!r}")
            ids.add(item_id); names.add(name)
            aliases = item.get("aliases")
            if not isinstance(aliases, list) or any(not isinstance(x, str) or not x for x in aliases):
                fail(f"{name}: aliases must be a list of non-empty strings")
            for alias in aliases:
                if alias in names:
                    fail(f"{name}: duplicate canonical name/alias {alias}")
                names.add(alias)
            if item.get("product_type") not in PRODUCT_TYPES or item.get("access") not in ACCESS:
                fail(f"{name}: invalid product type/access")
            if item.get("persistence") not in PERSISTENCE:
                fail(f"{name}: persistence must be explicit")
            safety = item.get("safety_preconditions")
            if not isinstance(safety, dict) or not isinstance(safety.get("required"), list) or safety.get("status") not in SAFETY_STATUS:
                fail(f"{name}: invalid safety_preconditions")
            if kind == "parameters":
                expected = "nonvolatile" if item.get("persistent") else "volatile"
                if item["persistence"] != expected:
                    fail(f"{name}: legacy persistent flag disagrees with persistence")
                disabled = item.get("requires_disabled")
                if not isinstance(disabled, bool) or disabled != ("drive.disabled" in safety["required"]):
                    fail(f"{name}: requires_disabled disagrees with safety_preconditions")
                if item.get("storage_commit") != ("explicit_store" if item["persistent"] else "none"):
                    fail(f"{name}: invalid storage_commit")
            elif item["persistence"] != "volatile":
                fail(f"{name}: signal persistence must be volatile")
            validate_physical(name, item, units); validate_range(name, item)
            fw = item.get("firmware", {})
            if fw.get("source") != "database/data_param.h" or not fw.get("struct") or not fw.get("field"):
                fail(f"{name}: incomplete firmware provenance")
            co = item.get("canopen", {}); index, subindex = co.get("index"), co.get("subindex")
            if not isinstance(index, str) or not re.fullmatch(r"0x[0-9A-Fa-f]{4}", index) or not isinstance(subindex, int) or not 0 <= subindex <= 255 or co.get("wire_type") not in WIRE_TYPES or co.get("access") not in ACCESS or not isinstance(co.get("pdo_mappable"), bool) or not co.get("eds_parameter_name"):
                fail(f"{name}: invalid CANopen binding")
            address = (normalized_index(index), subindex)
            if address in addresses:
                fail(f"duplicate CANopen address: {address[0]}:{address[1]}")
            addresses.add(address); validate_conversion(name, item, co)

    for kind in ("errors", "warnings"):
        codes: set[str] = set()
        for item in contract[kind]:
            code = item.get("code")
            if not isinstance(code, str) or not code or code in codes or not item.get("name") or not item.get("text_zh"):
                fail(f"{kind}: invalid/incomplete diagnostic entry {code!r}")
            codes.add(code)
    cap_ids: set[int] = set(); cap_names: set[str] = set()
    for item in contract["capabilities"]:
        if item.get("id") in cap_ids or item.get("name") in cap_names:
            fail("duplicate capability")
        cap_ids.add(item["id"]); cap_names.add(item["name"])
