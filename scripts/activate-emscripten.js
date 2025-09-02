#!/usr/bin/env node

import { execSync } from 'node:child_process';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const GREEN = '\x1b[32m';
const CYAN = '\x1b[36m';
const RED = '\x1b[31m';
const RESET = '\x1b[0m';

const version = process.argv[2] || 'latest';

const emsdkDir = join(dirname(fileURLToPath(import.meta.url)), 'emsdk');
const emsdkExec = join(emsdkDir, process.platform === 'win32' ? 'emsdk.bat' : 'emsdk')

// Activate
console.log(`${GREEN}Activating Emscripten SDK (version: ${CYAN}${version}${GREEN})...${RESET}`);
try {
    execSync(`${emsdkExec} activate ${version}`, { stdio: "inherit", shell: true });
} catch (error) {
    console.error(`${RED}Emscripten activation failed:${RESET} ${error.message}`);
    process.exit(1);
}
console.log(`${GREEN}Emscripten SDK activated successfully!${RESET}`);
