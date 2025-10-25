LINKER := $(BUILD_DIR)/uspace/uspace.lds
LINKER_TEMPLATE := uspace.lds.in


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
	@echo "  PP\t$(shell realpath --relative-to=$(BUILD_DIR) $@)"
	@$(CC) \
		-E \
		-P \
		-x c \
		$< -o $@ \
		-I $(ROOT_DIR)/include