#!/usr/bin/env bash
set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$PROJECT_ROOT"

ISO_ROOT="$PROJECT_ROOT/iso_root"
OUT_ISO="$PROJECT_ROOT/build/ExoOS-1.1-EcoSys.iso"

rm -rf "$ISO_ROOT"
mkdir -p "$ISO_ROOT/boot/limine"
mkdir -p "$PROJECT_ROOT/build"

cp "$PROJECT_ROOT/build/kernel.elf" "$ISO_ROOT/kernel.elf"
cp "$PROJECT_ROOT/boot/limine.cfg" "$ISO_ROOT/boot/limine/limine.cfg"

LIMINE_DIR=""

for dir in \
    /usr/share/limine \
    /usr/local/share/limine \
    "$PROJECT_ROOT/toolchain/limine" \
    "$PROJECT_ROOT/limine"
do
    if [ -d "$dir" ]; then
        LIMINE_DIR="$dir"
        break
    fi
done

if [ -z "$LIMINE_DIR" ]; then
    echo "Could not find Limine files."
    echo "Install Limine or clone it into ./toolchain/limine"
    echo
    echo "Arch example:"
    echo "  yay -S limine"
    exit 1
fi

copy_if_exists() {
    local file="$1"
    if [ -f "$LIMINE_DIR/$file" ]; then
        cp "$LIMINE_DIR/$file" "$ISO_ROOT/boot/limine/"
    fi
}

copy_if_exists limine-bios.sys
copy_if_exists limine-bios-cd.bin
copy_if_exists limine-uefi-cd.bin

mkdir -p "$ISO_ROOT/EFI/BOOT"

if [ -f "$LIMINE_DIR/BOOTX64.EFI" ]; then
    cp "$LIMINE_DIR/BOOTX64.EFI" "$ISO_ROOT/EFI/BOOT/BOOTX64.EFI"
fi

if [ -f "$LIMINE_DIR/BOOTIA32.EFI" ]; then
    cp "$LIMINE_DIR/BOOTIA32.EFI" "$ISO_ROOT/EFI/BOOT/BOOTIA32.EFI"
fi

xorriso -as mkisofs \
    -b boot/limine/limine-bios-cd.bin \
    -no-emul-boot \
    -boot-load-size 4 \
    -boot-info-table \
    --efi-boot boot/limine/limine-uefi-cd.bin \
    -efi-boot-part \
    --efi-boot-image \
    --protective-msdos-label \
    "$ISO_ROOT" \
    -o "$OUT_ISO"

if command -v limine >/dev/null 2>&1; then
    limine bios-install "$OUT_ISO" || true
elif [ -x "$LIMINE_DIR/limine" ]; then
    "$LIMINE_DIR/limine" bios-install "$OUT_ISO" || true
fi

echo "Built ISO:"
echo "  $OUT_ISO"
