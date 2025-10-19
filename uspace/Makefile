# Makefile for building uspace apps and servers
include $(ROOT_DIR)/common.mk

# Crucial parameters
MODULES = servers

MODULE_DIR := $(BUILD_DIR)/uspace

LINKER := $(MODULE_DIR)/uspace.lds
LINKER_TEMPLATE := uspace.lds.in

.PHONY: all $(MODULES)

all: $(MODULES) $(LINKER)

$(MODULES): $(LINKER) $(MODULE_DIR)
	$(MAKE) \
		-C $@ \
		MODULE_DIR=../$(MODULE_DIR) \
		ROOT_DIR=../$(ROOT_DIR)

$(LINKER): $(LINKER_TEMPLATE) $(MODULE_DIR)
	$(CC) \
		-E \
		-P \
		-x c \
		$< -o $@ \
		-I $(ROOT_DIR)/include

$(MODULE_DIR):
	mkdir -p $@