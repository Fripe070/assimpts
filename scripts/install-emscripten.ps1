param(
    [string]$Version = "latest"
)
$ErrorActionPreference = "Stop"

$EmsdkDir = Join-Path $PSScriptRoot "emsdk"

# Clone or update
if (Test-Path $EmsdkDir) {
    Write-Host "Updating existing Emscripten SDK..." -ForegroundColor Yellow
    Push-Location $EmsdkDir
    git pull
    Pop-Location
} else {
    Write-Host "Cloning Emscripten SDK..." -ForegroundColor Yellow
    git clone https://github.com/emscripten-core/emsdk.git $EmsdkDir
}

# Install and activate
Push-Location $EmsdkDir
./emsdk install $Version
Pop-Location
Write-Host "Activating Emscripten SDK..." -ForegroundColor Green
& $PSScriptRoot/activate-emscripten.ps1 $Version
Write-Host "Emscripten SDK installed and activated successfully!" -ForegroundColor Green
