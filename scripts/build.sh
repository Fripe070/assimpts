#!/bin/bash
GREEN="\033[32m"
CYAN="\033[36m"
RESET="\033[0m"

set -e
BuildType="${1:-Debug}"

echo -e "${GREEN}Building with Emscripten for WebAssembly...${RESET}"
echo -en "${GREEN}Build Type: ${RESET}"
echo -e "${CYAN}${BuildType}${RESET}"

if ! emcmake cmake -B build-wasm -G "Ninja" -DCMAKE_BUILD_TYPE="${BuildType}" .; then
    echo "CMake configuration failed. Exiting."
    exit 1
fi

echo -e "${GREEN}Ninja files generated, proceeding to build...${RESET}"

if ! emmake ninja -C build-wasm; then
    echo "Build failed. Exiting."
    exit 1
fi

echo -e "${GREEN}Build completed successfully!${RESET}"
