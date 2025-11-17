BFS := $(ROOT_DIR)/build/uspace/bfs.img
PM := pm

APP_ELFS := $(foreach a, $(APPS), $(ROOT_DIR)/build/uspace/apps/$(a)/$(a))
SERVER_ELFS := $(foreach s, $(SERVERS), $(ROOT_DIR)/build/uspace/servers/$(s)/$(s))
BFS_ELFS := $(APP_ELFS) $(SERVER_ELFS)

MKFS := $(ROOT_DIR)/scripts/mkfs.bfs.py


.PHONY: all $(SERVERS) $(BFS) $(PM)

all: $(SERVERS) $(BFS) $(PM)

$(PM): $(BFS)
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk

$(BFS): $(SERVERS)
	@echo "  MAKE\t$@"
	@$(PYTHON) $(MKFS) -o $@ $(BFS_ELFS) -s

$(SERVERS):
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk