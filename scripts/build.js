#!/usr/bin/env node

import { execSync } from 'node:child_process';

const GREEN = '\x1b[32m';
const CYAN = '\x1b[36m';
const RED = '\x1b[31m';
const RESET = '\x1b[0m';

const buildType = process.argv[2] || 'Debug';
const buildDir = 'build-wasm';


console.log(`${GREEN}Building with Emscripten for WebAssembly...${RESET}`);
console.log(`${GREEN}Build Type: ${RESET}${CYAN}${buildType}${RESET}`);

try {
    execSync(`emcmake cmake -B ${buildDir} -G "Ninja" -DCMAKE_BUILD_TYPE="${buildType}" .`, { stdio: 'inherit' });
} catch (error) {
    console.error(`${RED}CMake configuration failed:${RESET} ${error.message}`);
    process.exit(1);
}

console.log(`${GREEN}Ninja files generated, proceeding to build...${RESET}`);

try {
    execSync(`emmake ninja -C ${buildDir}`, { stdio: 'inherit' });
} catch (error) {
    console.error(`${RED}Build failed:${RESET} ${error.message}`);
    process.exit(1);
}

console.log(`${GREEN}Build completed successfully!${RESET}`);
