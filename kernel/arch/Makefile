# Makefile for architecture module

include ../../common.mk

# Crucial parameters
CFLAGS += -I$(INCLUDE_DIR)

C_SRC := $(wildcard *.c)
S_SRC := $(wildcard *.S)
SRCS := $(C_SRC) $(S_SRC)
OBJS := $(C_SRC:.c=.o) $(S_SRC:.S=.o)

MODULE_DIR := $(BUILD_DIR)/arch

all: $(MODULE_DIR) $(OBJS)

$(MODULE_DIR):
	mkdir -p $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(MODULE_DIR)/$@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $(MODULE_DIR)/$@