LINKER := $(BUILD_DIR)/uspace/libc/arch/uspace.lds
LINKER_TEMPLATE := libc/arch/uspace.lds.in

export APPS := \
	idle \
	hello \
	echoc 

export SERVERS := \
	echo \
	uart16550

.PHONY: all libc apps servers

all: $(LINKER) libc apps servers

libc:
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all

# build apps first
servers: libc $(LINKER) apps
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all

apps: libc $(LINKER)
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all

$(LINKER): $(LINKER_TEMPLATE)
	@echo "  PP\t$(shell realpath -m --relative-to=$(BUILD_DIR) $@)"
	@$(CC) \
		-E \
		-P \
		-x c \
		$< -o $@ \
		-I $(ROOT_DIR)/include