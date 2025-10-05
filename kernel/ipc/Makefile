# Makefile for IPC module

include ../../common.mk

# Crucial parameters
CFLAGS += -I$(INCLUDE_DIR)

C_SRC := $(wildcard *.c)
S_SRC := $(wildcard *.S)
SRCS := $(C_SRC) $(S_SRC)
OBJS := $(C_SRC:.c=.o) $(S_SRC:.S=.o)

MODULE_DIR := $(BUILD_DIR)/ipc

all: $(MODULE_DIR) $(OBJS)

$(MODULE_DIR):
	mkdir -p $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(MODULE_DIR)/$@

%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $(MODULE_DIR)/$@