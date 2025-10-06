# Toolchain
CROSS := riscv64-unknown-elf-

CC := $(CROSS)gcc
AS := $(CROSS)as
LD := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
OBJDUMP := $(CROSS)objdump

QEMU := qemu-system-riscv64
GDB := $(CROSS)gdb

# General flags
CFLAGS := -Wall -Werror -O2 -fno-pic -fno-builtin -ffreestanding -fno-stack-protector -mno-relax
CFLAGS += -march=rv64gc -mabi=lp64d -std=gnu11
# Critical for kernel to support large address space
CFLAGS += -mcmodel=medany

LDFLAGS := -nostdlib -static

QEMU_FLAGS := -machine virt -nographic -m 128M -bios default -smp 1
QEMU_FLAGS += -serial mon:stdio -nographic

# Functions

