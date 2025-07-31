# Assimpts

A TypeScript library template optimized for Bun.

## Installation

```bash
bun add assimpts
```

## Usage

```typescript
import { setupCounter } from "assimpts";

const button = document.querySelector<HTMLButtonElement>("#my-button")!;
setupCounter(button);
```

## Development

This project uses [Bun](https://bun.sh/) for fast package management and script execution.

### Building the library

```bash
bun run build
```

### Running the demo

```bash
bun run demo:dev
```

### Building the demo

```bash
bun run demo:build
```

### Installing dependencies

```bash
bun install
```

## Project Structure

```
├── src/                # Library source code
│   └── index.ts       # Main library entry point
├── demo/               # Demo/example application
│   ├── src/           # Demo source files
│   ├── public/        # Demo public assets
│   └── index.html     # Demo HTML file
├── dist/               # Built library output (auto-generated)
├── bun.lock           # Bun lockfile
├── package.json        # Package configuration
├── tsconfig.json       # TypeScript configuration
├── vite.config.ts      # Vite build configuration
└── README.md           # This file
```

## Why Bun?

This template uses Bun for:

-   ⚡ **Faster installs** - Bun installs packages ~10-100x faster than npm
-   🚀 **Faster script execution** - Bun runs scripts significantly faster
-   🔧 **Built-in TypeScript** - No need for separate TypeScript compilation in development
-   📦 **Better monorepo support** - Great for managing library + demo together
