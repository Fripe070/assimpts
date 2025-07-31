#!/bin/bash
set -e

BuildType="${1:-Debug}"

echo "Building with Emscripten for WebAssembly..."
echo -n "Build Type: "
echo "$BuildType"

if ! emcmake cmake -B build-wasm -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$BuildType" .; then
    echo "CMake configuration failed. Exiting."
    exit 1
fi

echo "Makefile generated, proceeding to build..."

if ! emmake make -C build-wasm; then
    echo "Build failed. Exiting."
    exit 1
fi

echo "Build completed successfully!"
