MOD_NAME := lib
MOD_SRCDIR := $(ROOT_DIR)/libs
MOD_OBJDIR := $(BUILD_DIR)/libs
CFLAGS := $(GLOBL_CFLAGS)
TARGET := $(MOD_OBJDIR)/libcocos.a

include $(ROOT_DIR)/scripts/build.mk

.PHONY: all

all: $(TARGET)

$(TARGET): $(MOD_OBJDIR)_dirs $(OBJS)
	@echo "  AR\t$(shell realpath --relative-to=$(BUILD_DIR) $@)"
	@$(AR) rcs $@ $(OBJS)
