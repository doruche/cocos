APPS := \
	hello

.PHONY: all $(APPS)

all: $(APPS)

$(APPS):
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk