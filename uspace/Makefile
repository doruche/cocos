# Makefile for building uspace apps and servers
include $(ROOT_DIR)/common.mk

# Crucial parameters
MODULES = servers apps

LINKER := $(BUILD_DIR)/uspace/uspace.lds
LINKER_TEMPLATE := uspace.lds.in

.PHONY: all $(MODULES)

all: $(BUILD_DIR) $(MODULES) $(LINKER)

$(BUILD_DIR):
	mkdir -p $@
	mkdir -p $(BUILD_DIR)/uspace
	mkdir -p $(BUILD_DIR)/uspace/servers
	mkdir -p $(BUILD_DIR)/uspace/apps

$(MODULES): $(LINKER)
	$(MAKE) \
		-C $@ \
		BUILD_DIR=../$(BUILD_DIR)/uspace \
		ROOT_DIR=../$(ROOT_DIR)

$(LINKER): $(LINKER_TEMPLATE)
	$(CC) \
		-E \
		-P \
		-x c \
		$< -o $@ \
		-I $(ROOT_DIR)/include