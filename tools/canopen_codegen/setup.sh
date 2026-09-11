#!/usr/bin/env sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
VENV_DIR="$SCRIPT_DIR/.venv"
PYTHON_BIN="${PYTHON_BIN:-python3}"

printf '%s\n' "[ServoHub] Creating virtual environment..."
"$PYTHON_BIN" -m venv "$VENV_DIR"

printf '%s\n' "[ServoHub] Installing pinned CANopen generator..."
"$VENV_DIR/bin/python" -m pip install --upgrade pip
"$VENV_DIR/bin/python" -m pip install -r "$SCRIPT_DIR/requirements.txt"

printf '%s\n' "[ServoHub] Verifying generator..."
"$VENV_DIR/bin/python" "$SCRIPT_DIR/generate.py" doctor

printf '%s\n' \
  "" \
  "Ready. Common commands:" \
  "  $VENV_DIR/bin/python $SCRIPT_DIR/generate.py list" \
  "  $VENV_DIR/bin/python $SCRIPT_DIR/generate.py generate" \
  "  $VENV_DIR/bin/python $SCRIPT_DIR/generate.py migrate-jsonc"
