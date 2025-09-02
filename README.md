# Assimpts

TypeScript wrapper around the [Assimp](https://github.com/assimp/assimp) C/C++ library compiled as WASM through [Emscripten](https://emscripten.org/).
Heavily inspired by [assimpjs](https://github.com/kovacsv/assimpjs).

## Usage
Install the package with
```bash
npm install assimpts
```
See the [examples](./examples/) for how to use the library. 

## Build
Required build tools:
- CMake
- Ninja
- C++ Compiler of your choice

### Linux
```bash
./scripts/install-emscripten.sh # Only needed on first install
./scripts/activate-emscripten.sh # Activate environment for current session
./scripts/build.sh
```
### Windows
```powershell
./scripts/install-emscripten.ps1 # Only needed on first install
./scripts/activate-emscripten.ps1 # Activate environment for current session
./scripts/build.ps1
```

