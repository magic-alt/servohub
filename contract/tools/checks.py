from __future__ import annotations

import json
import re

from generators import wire_bytes
from schema_model import DATA_PARAM, EDS, EDS_TYPE_CODE, GENERATED, MAVLINK_PROVENANCE, MAVLINK_ROOT, ROOT, all_items, fail, git_blob_sha, normalized_index


def parse_eds(text: str) -> dict[tuple[str, int], dict[str, str]]:
    current = None; result: dict[tuple[str, int], dict[str, str]] = {}
    for raw in text.splitlines():
        line = raw.strip(); match = re.fullmatch(r"\[([0-9A-Fa-f]{4})(?:sub([0-9]+))?\]", line)
        if match:
            current = ("0x" + match.group(1).upper(), int(match.group(2) or 0)); result[current] = {}
        elif current and "=" in line:
            key, value = line.split("=", 1); result[current][key.strip()] = value.strip()
    return result


def check_sources(contract: dict) -> None:
    data_text = DATA_PARAM.read_text(encoding="utf-8"); eds = parse_eds(EDS.read_text(encoding="utf-8")); problems = []
    for item in all_items(contract):
        name, field, co = item["name"], item["firmware"]["field"], item["canopen"]
        if not re.search(rf"\b{re.escape(field)}\b", data_text): problems.append(f"{name}: firmware field {field} not found")
        key = (normalized_index(co["index"]), co["subindex"]); section = eds.get(key)
        if not section:
            problems.append(f"{name}: EDS section {key[0]}:{key[1]} not found"); continue
        expected = {"ParameterName": co["eds_parameter_name"], "DataType": EDS_TYPE_CODE.get(co["wire_type"]), "PDOMapping": "1" if co["pdo_mappable"] else "0", "AccessType": co["access"]}
        for field_name, value in expected.items():
            actual = section.get(field_name)
            if field_name == "DataType" and actual and value and actual.lower() == value.lower(): continue
            if actual != value: problems.append(f"{name}: EDS {field_name} drift at {key[0]}:{key[1]} ({actual!r} != {value!r})")
    if problems: fail("firmware/EDS drift detected:\n  " + "\n  ".join(problems))


def parse_mavlink_header(text: str, message: str) -> tuple[int, dict[str, str]]:
    id_match = re.search(rf"#define\s+MAVLINK_MSG_ID_{re.escape(message)}\s+(\d+)", text)
    if not id_match: fail(f"MAVLink {message}: message ID macro not found")
    struct_match = re.search(r"typedef struct __mavlink_[a-z0-9_]+_t \{(.*?)\}\s*mavlink_[a-z0-9_]+_t;", text, flags=re.S)
    if not struct_match: fail(f"MAVLink {message}: payload struct not found")
    fields = {field_name: field_type for field_type, field_name in re.findall(r"^\s*([A-Za-z0-9_]+)\s+([A-Za-z0-9_]+)(?:\[[0-9]+\])?;", struct_match.group(1), flags=re.M)}
    return int(id_match.group(1)), fields


def check_mavlink_provenance() -> None:
    provenance = json.loads(MAVLINK_PROVENANCE.read_text(encoding="utf-8"))
    if provenance.get("status") != "generated_headers_without_source_xml" or provenance.get("source_dialect") is not None: fail("MAVLink provenance must remain explicit until source XML is recovered")
    if list(MAVLINK_ROOT.glob("*.xml")): fail("MAVLink XML appeared in generated-header root; update provenance intentionally")
    for item in provenance.get("representative_headers", []):
        path = ROOT / item["path"]
        if not path.exists() or git_blob_sha(path) != item["git_blob_sha"]: fail(f"MAVLink generated-header blob drift: {item['path']}")
        message_id, fields = parse_mavlink_header(path.read_text(encoding="utf-8"), item["message"])
        if message_id != item["message_id"]: fail(f"MAVLink message ID drift for {item['message']}")
        for field_name, field_type in item.get("fields", {}).items():
            if fields.get(field_name) != field_type: fail(f"MAVLink field drift for {item['message']}.{field_name}: {fields.get(field_name)!r} != {field_type!r}")


def check_golden_vectors(contract: dict) -> None:
    payload = json.loads((GENERATED / "golden/canopen_conversion_vectors.json").read_text(encoding="utf-8"))
    names = {x["name"] for x in payload["vectors"]}; expected = {item["name"] for item in all_items(contract) if item["canopen"]["conversion"]["status"] == "verified"}
    if names != expected: fail(f"golden vector coverage drift: {sorted(names)} != {sorted(expected)}")
    for vector in payload["vectors"]:
        for case in vector["cases"]:
            if case["product_value"] != case["wire_value"] or case["roundtrip_product"] != case["product_value"]: fail(f"{vector['name']}: identity roundtrip mismatch")
            if wire_bytes(vector["wire_type"], case["wire_value"]) != case["wire_le_hex"]: fail(f"{vector['name']}: golden wire bytes mismatch")
