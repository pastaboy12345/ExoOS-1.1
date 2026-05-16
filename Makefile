CC ?= x86_64-elf-gcc
LD ?= x86_64-elf-ld

CFLAGS := \
	-std=gnu11 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-lto \
	-fno-pie \
	-fno-pic \
	-m64 \
	-march=x86-64 \
	-mabi=sysv \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-mcmodel=kernel \
	-Wall \
	-Wextra \
	-O2 \
	-pipe

LDFLAGS := \
	-nostdlib \
	-static \
	-m elf_x86_64 \
	-z max-page-size=0x1000 \
	-T linker.ld

KERNEL_OBJS := \
	build/kernel.o

.PHONY: all clean kernel iso run

all: kernel

build:
	mkdir -p build

build/kernel.o: kernel/core/kernel.c | build
	$(CC) $(CFLAGS) -c $< -o $@

kernel: $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) $(KERNEL_OBJS) -o build/kernel.elf

iso: kernel
	./scripts/build.sh

run: iso
	./scripts/run-qemu.sh

clean:
	rm -rf build iso_root
