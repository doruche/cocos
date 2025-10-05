# Makefile for building kernel modules
include ../common.mk

# Crucial parameters
MODULES = $(shell ls -d */)

.PHONY: all $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) -C $@ BUILD_DIR=../$(BUILD_DIR) INCLUDE_DIR=../$(INCLUDE_DIR)