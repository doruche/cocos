# Makefile for building kernel modules
include $(ROOT_DIR)/common.mk

# Crucial parameters
MODULES = $(shell ls -d */)

LINKER := $(BUILD_DIR)/kernel/kernel.lds
LINKER_TEMPLATE := kernel.lds.in

.PHONY: all $(MODULES)

all: $(BUILD_DIR) $(MODULES) $(LINKER)

$(BUILD_DIR):
	mkdir -p $@

$(MODULES):
	$(MAKE) \
		-C $@ \
		BUILD_DIR=../$(BUILD_DIR)/kernel \
		ROOT_DIR=../$(ROOT_DIR)

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