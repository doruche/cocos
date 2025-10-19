MOD_NAME := kernel
MOD_SRCDIR := $(ROOT_DIR)/kernel
MOD_OBJDIR := $(BUILD_DIR)/kernel
TARGET := $(BUILD_DIR)/kernel.elf

LIBCOCO := $(BUILD_DIR)/libs/libgeneric.a
LINKER := $(MOD_OBJDIR)/kernel.lds
LINKER_TEMPLATE := $(MOD_SRCDIR)/kernel.lds.in

CFLAGS := $(GLOBL_CFLAGS) -DKERNEL

include $(ROOT_DIR)/scripts/build.mk

.PHONY: all stub

all: $(TARGET)

stub: | $(MOD_OBJDIR)_dirs
	echo "$(MOD_SRCDIR)"
	echo "$(cbuild_dir)"
	echo "$(cbuild_rel_dir)"
	echo "$(local_objs)"
	echo "$(OBJS)"

$(BUILD_DIR)/kernel.elf: $(MOD_OBJDIR)_dirs $(OBJS) $(LIBCOCO) $(LINKER)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBCOCO) -T $(LINKER) -Map=$(BUILD_DIR)/kernel.map
	$(OBJCOPY) -S -O binary $@ $(BUILD_DIR)/kernel.bin
	$(OBJDUMP) -d $@ > $(BUILD_DIR)/kernel.asm

$(LINKER): $(LINKER_TEMPLATE)
# -E: preprocess only
# -P: inhibit generation of linemarkers
# -x c: treat input as C code to make preprocessor happy
# -I: include path
	$(CC) \
		-E \
		-P \
		-x c \
		$< -o $@ \
		-I $(ROOT_DIR)/include