param(
    [string]$Version = "latest"
)
$ErrorActionPreference = "Stop"

$EmsdkDir = Join-Path $PSScriptRoot "emsdk"

Write-Host "Activating Emscripten SDK..." -ForegroundColor Green
Push-Location $EmsdkDir
./emsdk activate $Version
Write-Host "Loading Emscripten environment..." -ForegroundColor Green
./emsdk_env
Pop-Location
Write-Host "Emscripten SDK activated successfully!" -ForegroundColor Green
