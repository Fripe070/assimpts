param(
    [string]$BuildType = "Debug"
)
$ErrorActionPreference = "Stop"

Write-Host "Building with Emscripten for WebAssembly..." -ForegroundColor Green
Write-Host "Build Type: " -NoNewline -ForegroundColor Green
Write-Host $BuildType -ForegroundColor Cyan
emcmake cmake -B build-wasm -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$BuildType .
if (!$?) {
    Write-Host "CMake configuration failed. Exiting."
    exit 1
}
Write-Host "Makefile generated, proceeding to build..." -ForegroundColor Green
emmake make -C build-wasm
if (!$?) {
    Write-Host "Build failed. Exiting."
    exit 1
}
Write-Host "Build completed successfully!" -ForegroundColor Green

