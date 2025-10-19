MOD_NAME := uspace/libc
MOD_SRCDIR := $(ROOT_DIR)/uspace/libc
MOD_OBJDIR := $(BUILD_DIR)/uspace/libc
CFLAGS := $(GLOBL_CFLAGS)
TARGET := $(MOD_OBJDIR)/libc.a

include $(ROOT_DIR)/scripts/build.mk

.PHONY: all

all: $(TARGET)
$(TARGET): $(MOD_OBJDIR)_dirs $(OBJS)
	$(AR) rcs $@ $(OBJS)