# Makefile for building uspace apps
include $(ROOT_DIR)/common.mk

# Crucial parameters
MODULES = $(shell ls -d */)

.PHONY: all $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) \
		-C $@ \
		BUILD_DIR=../$(BUILD_DIR)/apps \
		ROOT_DIR=../$(ROOT_DIR)