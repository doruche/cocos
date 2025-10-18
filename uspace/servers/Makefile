# Makefile for building uspace servers
include $(ROOT_DIR)/common.mk

# Crucial parameters
MODULES = $(shell ls -d */)

.PHONY: all $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) \
		-C $@ \
		BUILD_DIR=../$(BUILD_DIR)/servers \
		ROOT_DIR=../$(ROOT_DIR)