#!/bin/bash
set -e

VERSION=${1:-"latest"}
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EMSDK_DIR="$SCRIPT_DIR/emsdk"

# Clone or update
if [ -d "$EMSDK_DIR" ]; then
    echo "Updating existing Emscripten SDK..."
    cd "$EMSDK_DIR"
    git pull
    cd - > /dev/null
else
    echo "Cloning Emscripten SDK..."
    git clone https://github.com/emscripten-core/emsdk.git "$EMSDK_DIR"
fi

# Install and activate
echo "Installing Emscripten SDK version: $VERSION"
cd "$EMSDK_DIR"
./emsdk install "$VERSION"
cd - > /dev/null

echo "Activating Emscripten SDK..."
source "$SCRIPT_DIR/activate-emscripten.sh" "$VERSION"

echo "Emscripten SDK installation completed!"
