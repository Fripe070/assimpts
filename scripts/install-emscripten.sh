#!/bin/bash
GREEN="\033[1;32m"
RED="\033[1;31m"
RESET="\033[0m"

set -e
VERSION=${1:-"latest"}
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EMSDK_DIR="$SCRIPT_DIR/emsdk"

# Clone or update
if [ -d "$EMSDK_DIR" ]; then
    echo -e "${GREEN}Updating existing Emscripten SDK...${RESET}"
    pushd "$EMSDK_DIR" > /dev/null
    git pull
    popd > /dev/null
else
    echo -e "${GREEN}Cloning Emscripten SDK...${RESET}"
    git clone https://github.com/emscripten-core/emsdk.git "$EMSDK_DIR"
fi

# Install and activate
pushd "$EMSDK_DIR" > /dev/null
./emsdk install "$VERSION"
if [ $? -ne 0 ]; then
    echo -e "${RED}Emscripten SDK installation failed. Exiting.${RESET}"
    popd > /dev/null
    exit 1
fi
popd > /dev/null

echo -e "${GREEN}Activating Emscripten SDK...${RESET}"
bash "$SCRIPT_DIR/activate-emscripten.sh"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Emscripten SDK installed and activated successfully!${RESET}"
else
    echo -e "${RED}Emscripten SDK activation failed. Exiting.${RESET}"
    exit 1
fi
