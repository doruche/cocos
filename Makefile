# Makefile for building the kernel

include common.mk

# Crucial parameters
INCLUDE_DIR := include
KERNEL_DIR := kernel
USER_DIR := uspace

BUILD_DIR := build

KERNEL_LINKER_TEMPLATE := $(KERNEL_DIR)/kernel.lds.in
KERNEL_LINKER := $(BUILD_DIR)/kernel.lds

KERNEL_ELF := $(BUILD_DIR)/kernel.elf
KERNEL_BIN := $(BUILD_DIR)/kernel.bin
KERNEL_MAP := $(BUILD_DIR)/kernel.map

LINKERS := $(KERNEL_LINKER)

MODULES := kernel uspace

OBJS := $(BUILD_DIR)/**/*.o

# todo uspace
.PHONY: all clean kernel run gdb-client gdb-server

all: $(BUILD_DIR) $(LINKERS) $(MODULES)
	$(LD) $(LDFLAGS) -T $(KERNEL_LINKER) -o $(KERNEL_ELF) $(OBJS) -Map=$(KERNEL_MAP)
	$(OBJCOPY) -O binary $(KERNEL_ELF) $(KERNEL_BIN)
	$(OBJDUMP) -d $(KERNEL_ELF) > $(BUILD_DIR)/kernel.asm

$(KERNEL_LINKER): $(KERNEL_LINKER_TEMPLATE)
# -E: preprocess only
# -P: inhibit generation of linemarkers
# -x c: treat input as C code to make preprocessor happy
# -I: include path
	$(CC) \
		-E \
		-P \
		-x c \
		$< -o $@ \
		-I $(INCLUDE_DIR) # Include path

$(MODULES):
	$(MAKE) -C $@ BUILD_DIR=../$(BUILD_DIR) INCLUDE_DIR=../$(INCLUDE_DIR)

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