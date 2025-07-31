#!/bin/bash
set -e

VERSION=${1:-"latest"}
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EMSDK_DIR="$SCRIPT_DIR/emsdk"

if [ ! -d "$EMSDK_DIR" ]; then
    echo "Error: Emscripten SDK not found at $EMSDK_DIR"
    echo "Please run install-emscripten.sh first"
    exit 1
fi

echo "Activating Emscripten SDK version: $VERSION"
cd "$EMSDK_DIR"
./emsdk activate "$VERSION"

echo "Loading Emscripten environment..."
source ./emsdk_env.sh

cd - > /dev/null
echo "Emscripten SDK activated successfully!"
echo "Environment variables have been set for the current shell session."
echo ""
echo "To use Emscripten in other shell sessions, run:"
echo "source $EMSDK_DIR/emsdk_env.sh"
