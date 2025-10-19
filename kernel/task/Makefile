# Makefile for task management module

include $(ROOT_DIR)/common.mk

# Crucial parameters
CFLAGS += -I$(ROOT_DIR)/include

C_SRC := $(wildcard *.c)
S_SRC := $(wildcard *.S)
SRCS := $(C_SRC) $(S_SRC)
OBJS := $(C_SRC:.c=.o) $(S_SRC:.S=.o)

override MODULE_DIR := $(MODULE_DIR)/task

all: $(MODULE_DIR) $(OBJS)

$(MODULE_DIR):
	mkdir -p $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(MODULE_DIR)/$@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $(MODULE_DIR)/$@ -D__DEFONLY__