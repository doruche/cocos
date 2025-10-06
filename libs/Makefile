# Makefile for building common libraries
include $(ROOT_DIR)/common.mk

# Crucial parameters
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

LIB_DIR := $(BUILD_DIR)/libs

.PHONY: all $(LIBS)

all: $(LIB_DIR) $(OBJS)

$(LIB_DIR):
	mkdir -p $@

%.o: %.c
	$(CC) $(CFLAGS) -I$(ROOT_DIR)/include -c $< -o $(LIB_DIR)/$@