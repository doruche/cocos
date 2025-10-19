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

# General compiler flags
export GLOBL_CFLAGS := \
	-Wall -Werror -Wno-error=unused \
	-O2 -fno-pic -fno-builtin -ffreestanding -fno-stack-protector -mno-relax -g \
	-march=rv64gc -mabi=lp64d -std=gnu11 \
	-mcmodel=medany -fno-pie \
	-I$(ROOT_DIR)/include \
	-I.

export GLOBL_LDFLAGS := -nostdlib -static -no-pie

# Emulator and debugger. Not used by sub-makefiles.
QEMU := qemu-system-riscv64
GDB := $(CROSS)gdb
QEMU_FLAGS := \
	-machine virt -nographic -m 128M -bios default -smp 1 \
	-serial mon:stdio -nographic

# Parameters
MODULES := libs kernel uspace

KERNEL_LINKER := $(BUILD_DIR)/kernel/kernel.lds

KERNEL_ELF := $(BUILD_DIR)/kernel.elf
KERNEL_ASM := $(BUILD_DIR)/kernel.asm
KERNEL_BIN := $(BUILD_DIR)/kernel.bin
KERNEL_MAP := $(BUILD_DIR)/kernel.map

KERNEL_OBJS := $(BUILD_DIR)/kernel/*/*.o \
	$(BUILD_DIR)/libs/*.o

.PHONY: all clean $(MODULES)			run gdb-client gdb-server

all: $(MODULES)
#	$(LD) $(LDFLAGS) -T $(KERNEL_LINKER) -o $(KERNEL_ELF) $(KERNEL_OBJS) -Map=$(KERNEL_MAP)
#	$(OBJCOPY) -O binary $(KERNEL_ELF) $(KERNEL_BIN)
#	$(OBJDUMP) -d -S $(KERNEL_ELF) > $(KERNEL_ASM)

# building the kernel depends on bootelf from uspace.
# this is a bit coarse-grained and slow, but works for now.
uspace: libs
kernel: uspace

$(MODULES): prepare
	$(MAKE) all -C $@

prepare: $(patsubst %,$(BUILD_DIR)/%,$(MODULES))

$(BUILD_DIR)/%:
	mkdir -p $@

run:
	$(QEMU) $(QEMU_FLAGS) \
		-kernel $(KERNEL_BIN)

gdb-server:
	$(QEMU) $(QEMU_FLAGS) \
		-kernel $(KERNEL_BIN) \
		-s -S

gdb-client:
	$(GDB) \
		-ex "target remote :1234" \
		-ex "file $(KERNEL_ELF)" \
		-ex "set architecture riscv:rv64" \

clean:
	rm -rf $(BUILD_DIR)