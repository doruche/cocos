# Makefile for building kernel modules
include $(ROOT_DIR)/common.mk

# Crucial parameters
MODULES = $(shell ls -d */)
MODULE_DIR := $(BUILD_DIR)/kernel

LINKER := $(MODULE_DIR)/kernel.lds
LINKER_TEMPLATE := kernel.lds.in

.PHONY: all $(MODULES)

all: $(MODULES) $(LINKER)

$(MODULES): $(MODULE_DIR)
	$(MAKE) \
		-C $@ \
		MODULE_DIR=../$(MODULE_DIR) \
		ROOT_DIR=../$(ROOT_DIR)

$(MODULE_DIR):
	mkdir -p $@

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