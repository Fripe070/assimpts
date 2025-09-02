#!/usr/bin/env node

import { execSync } from 'node:child_process';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { existsSync } from 'node:fs';

const GREEN = '\x1b[32m';
const CYAN = '\x1b[36m';
const RED = '\x1b[31m';
const RESET = '\x1b[0m';

const repoUrl = 'https://github.com/emscripten-core/emsdk.git';
const version = process.argv[2] || 'latest';

const emsdkDir = join(dirname(fileURLToPath(import.meta.url)), 'emsdk');
const emsdkExec = join(emsdkDir, process.platform === 'win32' ? 'emsdk.bat' : 'emsdk')

// Clone/pull
if (existsSync(emsdkDir)) {
    console.log(`${GREEN}Updating already installed Emscripten SDK...${RESET}`);
    try {
        execSync(`git -C "${emsdkDir}" pull`, { stdio: 'inherit', shell: true });
    } catch (error) {
        console.error(`${RED}Git pull failed:${RESET} ${error.message}`);
        process.exit(1);
    }
} else {
    console.log(`${GREEN}Cloning Emscripten SDK...${RESET}`);
    try {
        execSync(`git clone "${repoUrl}" "${emsdkDir}"`, { stdio: 'inherit', shell: true });
    } catch (error) {
        console.error(`${RED}Git clone failed:${RESET} ${error.message}`);
        process.exit(1);
    }
}

// Install
console.log(`${GREEN}Installing Emscripten SDK (version: ${CYAN}${version}${GREEN})...${RESET}`);
try {
    execSync(`${emsdkExec} install ${version}`, { stdio: 'inherit', shell: true });
} catch (error) {
    console.error(`${RED}Emscripten installation failed:${RESET} ${error.message}`);
    process.exit(1);
}

// Activate
console.log(`${GREEN}Activating Emscripten SDK (version: ${CYAN}${version}${GREEN})...${RESET}`);
try {
    execSync(`${emsdkExec} activate ${version}`, { stdio: "inherit", shell: true });
} catch (error) {
    console.error(`${RED}Emscripten activation failed:${RESET} ${error.message}`);
    process.exit(1);
}
console.log(`${GREEN}Emscripten SDK activated successfully!${RESET}`);

console.log(`${GREEN}Emscripten SDK installed and activated successfully!${RESET}`);
