# Makefile for building uspace servers
include $(ROOT_DIR)/common.mk

# Crucial parameters
override MODULE_DIR := $(MODULE_DIR)/servers
MODULES = $(shell ls -d */)

.PHONY: all $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) \
		-C $@ \
		MODULE_DIR=../$(MODULE_DIR) \
		ROOT_DIR=../$(ROOT_DIR)