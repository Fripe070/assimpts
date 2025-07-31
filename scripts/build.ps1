param(
    [string]$BuildType = "Debug"
)
$ErrorActionPreference = "Stop"

Write-Host "Building with Emscripten for WebAssembly..." -ForegroundColor Green
Write-Host "Build Type: " -NoNewline -ForegroundColor Green
Write-Host $BuildType -ForegroundColor Cyan

emcmake cmake -B build-wasm -G "Ninja" -DCMAKE_BUILD_TYPE="$BuildType" .
if (!$?) {
    Write-Host "CMake configuration failed. Exiting."
    exit 1
}

Write-Host "Ninja files generated, proceeding to build..." -ForegroundColor Green
emmake ninja -C build-wasm
if (!$?) {
    Write-Host "Build failed. Exiting."
    exit 1
}
Write-Host "Build completed successfully!" -ForegroundColor Green
