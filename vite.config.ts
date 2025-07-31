import { defineConfig } from "vite";
import dts from "vite-plugin-dts";

export default defineConfig({
    plugins: [
        dts({
            include: ["src"],
            outDir: "dist",
        }),
    ],
    build: {
        lib: {
            entry: "./src/index.ts",
            name: "Assimpts",
            fileName: "assimpts",
        },
    },
});
