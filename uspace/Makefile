LINKER := $(BUILD_DIR)/uspace/uspace.lds
LINKER_TEMPLATE := uspace.lds.in

LIBC := libc
RUNNABLE := apps servers

.PHONY: all $(LIBC) $(RUNNABLE)

all: $(LINKER) $(LIBC) $(RUNNABLE)

$(LIBC):
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all

$(RUNNABLE): $(LIBC) $(LINKER)
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