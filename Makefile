# Makefile for building the kernel

include common.mk

# Crucial parameters
ROOT_DIR := .

KERNEL_DIR := kernel
USER_DIR := uspace

BUILD_DIR := build

KERNEL_LINKER := $(BUILD_DIR)/kernel/kernel.lds

KERNEL_ELF := $(BUILD_DIR)/kernel.elf
KERNEL_ASM := $(BUILD_DIR)/kernel.asm
KERNEL_BIN := $(BUILD_DIR)/kernel.bin
KERNEL_MAP := $(BUILD_DIR)/kernel.map

MODULES := kernel uspace libs

OBJS := $(BUILD_DIR)/kernel/*/*.o \
	$(BUILD_DIR)/libs/*.o

# todo uspace
.PHONY: all clean kernel libs run gdb-client gdb-server

all: $(BUILD_DIRS) $(LINKERS) $(MODULES)
	$(LD) $(LDFLAGS) -T $(KERNEL_LINKER) -o $(KERNEL_ELF) $(OBJS) -Map=$(KERNEL_MAP)
	$(OBJCOPY) -O binary $(KERNEL_ELF) $(KERNEL_BIN)
	$(OBJDUMP) -d $(KERNEL_ELF) > $(KERNEL_ASM)

$(MODULES):
	$(MAKE)		\
		-C $@	\
		BUILD_DIR=../$(BUILD_DIR) \
		ROOT_DIR=../$(ROOT_DIR)

$(BUILD_DIR):
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