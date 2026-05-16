#!/usr/bin/env bash
set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
ISO="$PROJECT_ROOT/build/ExoOS-1.1-EcoSys.iso"

if [ ! -f "$ISO" ]; then
    echo "ISO not found:"
    echo "  $ISO"
    echo "Run:"
    echo "  make iso"
    exit 1
fi

qemu-system-x86_64 \
    -m 512M \
    -smp 2 \
    -cdrom "$ISO" \
    -boot d \
    -serial stdio \
    -display sdl \
    -vga std
