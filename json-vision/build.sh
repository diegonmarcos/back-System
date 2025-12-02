#!/bin/bash
set -e

# Ensure we are in the project directory
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_DIR"

echo "Building single-file SPA with Vite..."
# Using npx vite build which uses vite-plugin-singlefile
npx vite build

echo "Build complete. Output is in dist/index.html"