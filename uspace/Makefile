LINKER := $(BUILD_DIR)/uspace/uspace.lds
LINKER_TEMPLATE := uspace.lds.in

LIBC := libc
RUNNABLE := apps servers

.PHONY: all $(LIBC) $(RUNNABLE)

all: $(LINKER) $(LIBC) $(RUNNABLE)

$(LIBC):
	$(MAKE) -C $@ all

$(RUNNABLE): $(LIBC) $(LINKER)
	$(MAKE) -C $@ all

$(LINKER): $(LINKER_TEMPLATE)
	$(CC) \
		-E \
		-P \
		-x c \
		$< -o $@ \
		-I $(ROOT_DIR)/include