#!/usr/bin/env bash
# Generate keyboard layout SVG from ZMK keymap
# Requires: python3 venv with keymap-drawer (pip install keymap-drawer)

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VENV_DIR="$SCRIPT_DIR/.venv"
CONFIG="$SCRIPT_DIR/keymap_drawer.config.yaml"
KEYMAP="$SCRIPT_DIR/config/corneish_zen.keymap"
YAML_OUT="$SCRIPT_DIR/keymap.yaml"
SVG_OUT="$SCRIPT_DIR/keymap.svg"

# Ensure venv exists with keymap-drawer
if [ ! -f "$VENV_DIR/bin/keymap" ]; then
    echo "Setting up Python venv with keymap-drawer..."
    python3 -m venv "$VENV_DIR"
    "$VENV_DIR/bin/pip" install -q keymap-drawer
fi

KEYMAP_CMD="$VENV_DIR/bin/keymap"

echo "Parsing keymap..."
"$KEYMAP_CMD" -c "$CONFIG" parse -z "$KEYMAP" -o "$YAML_OUT"

echo "Drawing SVG..."
"$KEYMAP_CMD" -c "$CONFIG" draw -z corneish_zen "$YAML_OUT" -o "$SVG_OUT"

echo "Done! Output: $SVG_OUT"
