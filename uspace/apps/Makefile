.PHONY: all $(APPS)

all: $(APPS)

$(APPS):
	@echo "  MAKE\t$@"
	@mkdir -p $(BUILD_DIR)/uspace/apps
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk