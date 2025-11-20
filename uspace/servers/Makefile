BFS := $(ROOT_DIR)/build/uspace/bfs.img

APP_ELFS := $(foreach a, $(APPS), $(ROOT_DIR)/build/uspace/apps/$(a)/$(a))
SERVER_ELFS := $(foreach s, $(SERVERS), $(ROOT_DIR)/build/uspace/servers/$(s)/$(s))
BFS_ELFS := $(APP_ELFS) $(SERVER_ELFS)

MKFS := $(ROOT_DIR)/scripts/mkfs.bfs.py


.PHONY: all pm $(SERVERS)

all: pm

# force rebuild of PM every time

pm: $(BFS)
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ clean -f$(ROOT_DIR)/scripts/userapp.mk
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk

$(BFS): $(SERVER_ELFS) $(APP_ELFS)
	@echo "  MKFS\t$@"
	@$(PYTHON) $(MKFS) -o $@ $(BFS_ELFS) -s

$(SERVER_ELFS): $(SERVERS)

$(SERVERS):
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk
