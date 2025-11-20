MOD_NAME := kernel
MOD_SRCDIR := $(ROOT_DIR)/kernel
MOD_OBJDIR := $(BUILD_DIR)/kernel
TARGET := $(BUILD_DIR)/kernel.elf

LIBGENERIC := $(BUILD_DIR)/libs/libgeneric.a
LINKER := $(MOD_OBJDIR)/arch/kernel.lds
LINKER_TEMPLATE := $(MOD_SRCDIR)/arch/kernel.lds.in

CFLAGS := $(GLOBL_CFLAGS) -DKERNEL -DLOG=$(KLOG) -DNAME=\"kernel/\"
LDFLAGS := $(GLOBL_LDFLAGS) -T $(LINKER) -Map=$(BUILD_DIR)/kernel.map

include $(ROOT_DIR)/scripts/build.mk

.PHONY: all stub bootimage

all: $(TARGET)

$(BUILD_DIR)/kernel.elf: $(MOD_OBJDIR)_dirs $(OBJS) $(LIBGENERIC) $(LINKER) $(BOOTIMG)
	@echo "  LD\t$(shell realpath --relative-to=$(BUILD_DIR) $@)"
	@$(LD) $(LDFLAGS) -o $@ $(OBJS) $(BOOTIMG) $(LIBGENERIC)
	@echo "  COPY\tkernel.bin"
	@$(OBJCOPY) -S -O binary $@ $(BUILD_DIR)/kernel.bin
	@echo "  DUMP\tkernel.asm"
	@$(OBJDUMP) -S -d $@ > $(BUILD_DIR)/kernel.asm

BOOTIMG := $(BUILD_DIR)/kernel/bootimage.o
bootimage:
	@rm -f $(BOOTIMG)
	@$(CC) -c -o $(BOOTIMG) $(MOD_SRCDIR)/bootimage.S

$(LINKER): $(LINKER_TEMPLATE) bootimage
# -E: preprocess only
# -P: inhibit generation of linemarkers
# -x c: treat input as C code to make preprocessor happy
# -I: include path
	@echo "  PP\t$(shell realpath --relative-to=$(BUILD_DIR) $@)"
	@$(CC) \
		-E \
		-P \
		-x c \
		$< -o $@ \
		-I $(ROOT_DIR)/include