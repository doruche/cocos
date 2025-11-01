# Top-level build script, both for kernel and uspace.

# Toolchain
CROSS := riscv64-unknown-elf-

export CC := $(CROSS)gcc
export AS := $(CROSS)as
export LD := $(CROSS)ld
export OBJCOPY := $(CROSS)objcopy
export OBJDUMP := $(CROSS)objdump

# Directories
export ROOT_DIR := $(CURDIR)
export BUILD_DIR := $(abspath $(ROOT_DIR)/build)

# General building flags
export MAKEFLAGS += --no-print-directory

export GLOBL_CFLAGS := \
	-Wall -Wno-error=unused \
	-O2 -fno-pic -fno-builtin -ffreestanding -fno-stack-protector -mno-relax -g \
	-march=rv64gc -mabi=lp64d -std=gnu11 \
	-mcmodel=medany -fno-pie \
	-I$(ROOT_DIR)/include \
	-I.

export GLOBL_LDFLAGS := -nostdlib -static -no-pie

export KLOG ?= TRACE
export ULOG ?= TRACE

# Emulator and debugger. Not used by sub-makefiles.
KERNEL_BIN := $(BUILD_DIR)/kernel.bin
KERNEL_ELF := $(BUILD_DIR)/kernel.elf

QEMU := qemu-system-riscv64
GDB := $(CROSS)gdb
OUT_SERIAL := -serial mon:stdio
OUT_LOG := -serial file:$(BUILD_DIR)/qemu.log
QEMU_FLAGS := \
	-machine virt -nographic -m 128M -bios default -smp 1 \
	-nographic 

# Parameters
MODULES := libs kernel uspace

.PHONY: all clean $(MODULES) \
		run gdb-client gdb-server

all: $(MODULES)

# building the kernel depends on bootimage from uspace.
# this is a bit coarse-grained and slow, but works for now.
uspace: libs
kernel: uspace

$(MODULES): prepare
	@echo "  MAKE\t$@"
	@$(MAKE) all -C $@

prepare: $(patsubst %,$(BUILD_DIR)/%,$(MODULES))

$(BUILD_DIR)/%:
	@mkdir -p $@

run:
	$(QEMU) $(QEMU_FLAGS) \
		$(OUT_SERIAL) \
		-kernel $(KERNEL_BIN)

run-log:
	$(QEMU) $(QEMU_FLAGS) \
		$(OUT_LOG) \
		-kernel $(KERNEL_BIN)

gdb-server:
	$(QEMU) $(QEMU_FLAGS) \
		$(OUT_SERIAL) \
		-kernel $(KERNEL_BIN) \
		-s -S

gdb-client:
	$(GDB) \
		-ex "target remote :1234" \
		-ex "file $(KERNEL_ELF)" \
		-ex "set architecture riscv:rv64" \

clean:
	rm -rf $(BUILD_DIR)