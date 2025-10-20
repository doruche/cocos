APPS := $(shell ls -d */ | xargs -n 1 basename)

.PHONY: all $(APPS)

all: $(APPS)

$(APPS):
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk