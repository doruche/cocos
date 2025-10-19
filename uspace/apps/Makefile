APPS := $(shell ls -d */ | xargs -n 1 basename)

.PHONY: all

all: $(APPS)

$(APPS):
	$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk