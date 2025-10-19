# template for compiling user applications

APP_NAME := $(notdir $(CURDIR))
TYPE := $(shell basename $(shell dirname $(CURDIR)))

MOD_NAME := uspace/$(TYPE)/$(APP_NAME)
MOD_SRCDIR := $(CURDIR)
MOD_OBJDIR := $(BUILD_DIR)/uspace/$(TYPE)/$(APP_NAME)
CFLAGS := $(GLOBL_CFLAGS)
LDFLAGS := $(GLOBL_LDFLAGS) -T $(BUILD_DIR)/uspace/uspace.lds
TARGET := $(MOD_OBJDIR)/$(APP_NAME).elf

LIBC := $(BUILD_DIR)/uspace/libc/libc.a

# this script will be run at each user apps' root dir
include $(ROOT_DIR)/scripts/build.mk

.PHONY: all

all: $(MOD_OBJDIR)_dirs $(TARGET)

$(TARGET): $(OBJS) $(LIBC)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJDUMP) -S $@ > $(MOD_OBJDIR)/$(APP_NAME).asm