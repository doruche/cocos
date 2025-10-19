include $(ROOT_DIR)/common.mk

# Crucial parameters
CFLAGS += -I$(ROOT_DIR)/include

C_SRC := $(wildcard *.c)
S_SRC := $(wildcard *.S)
SRCS := $(C_SRC) $(S_SRC)
OBJS := $(C_SRC:.c=.o) $(S_SRC:.S=.o)

LINKER := $(ROOT_DIR)/build/uspace/uspace.lds

override MODULE_DIR := $(MODULE_DIR)/pm

TARGET_ELF := $(MODULE_DIR)/pm.elf
TARGET_ASM := $(MODULE_DIR)/pm.asm

all: $(MODULE_DIR) $(OBJS) $(TARGET_ELF) $(TARGET_ASM)

$(MODULE_DIR):
	mkdir -p $@

$(TARGET_ELF): $(MODULE_DIR) $(OBJS) $(LINKER)
	echo "$(MODULE_DIR)"
	$(LD) $(LDFLAGS) -T $(LINKER) -o $@ $(MODULE_DIR)/$(OBJS) $(LDFLAGS)

$(TARGET_ASM): $(TARGET_ELF)
	$(OBJDUMP) -d -S $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(MODULE_DIR)/$@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $(MODULE_DIR)/$@ -D__DEFONLY__