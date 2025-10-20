SERVERS := $(shell ls -d */ | xargs -n 1 basename)

.PHONY: all $(SERVERS)

all: $(SERVERS)

$(SERVERS):
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk