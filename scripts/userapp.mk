# template for compiling user applications

APP_NAME := $(notdir $(CURDIR))
TYPE := $(shell basename $(shell dirname $(CURDIR)))

MOD_NAME := uspace/$(TYPE)/$(APP_NAME)
MOD_SRCDIR := $(CURDIR)
MOD_OBJDIR := $(BUILD_DIR)/uspace/$(TYPE)/$(APP_NAME)
CFLAGS := $(GLOBL_CFLAGS) -DLOG=$(ULOG) -DNAME=\"$(TYPE)/$(APP_NAME)/\"
LDFLAGS := $(GLOBL_LDFLAGS) -T $(BUILD_DIR)/uspace/libc/arch/uspace.lds
TARGET := $(MOD_OBJDIR)/$(APP_NAME)

# NOTE libc depends on libgeneric! ORDER MATTERS!!!
LIBS := $(BUILD_DIR)/libs/libgeneric.a $(BUILD_DIR)/uspace/libc/libc.a

# this script will be run at each user apps' root dir
include $(ROOT_DIR)/scripts/build.mk

.PHONY: all clean

all: $(MOD_OBJDIR)_dirs $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	@echo "  LD\t$(shell realpath --relative-to=$(BUILD_DIR) $@)"
	@$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS) $(LIBS) -Map=$(MOD_OBJDIR)/$(APP_NAME).map
	@echo "  DUMP\t$(basename $(shell realpath --relative-to=$(BUILD_DIR) $@)).asm"
	@$(OBJDUMP) -S $@ > $(MOD_OBJDIR)/$(APP_NAME).asm

clean:
	@rm -rf $(MOD_OBJDIR)