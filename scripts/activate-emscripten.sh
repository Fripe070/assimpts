#!/bin/bash
GREEN="\033[32m"
CYAN="\033[36m"
RESET="\033[0m"

set -e
VERSION=${1:-"latest"}
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EMSDK_DIR="$SCRIPT_DIR/emsdk"

echo -e "${GREEN}Activating Emscripten SDK...${RESET}"
pushd "$EMSDK_DIR" > /dev/null
./emsdk activate "$VERSION"
echo -e "${GREEN}Loading Emscripten environment...${RESET}"
source ./emsdk_env.sh
popd > /dev/null
echo -e "${GREEN}Emscripten SDK activated successfully!${RESET}"
