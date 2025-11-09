# SERVERS := $(shell ls -d */ | xargs -n 1 basename)

SERVERS := echo
BFS := bfs
PM := pm

BFS_PATH := $(ROOT_DIR)/build/uspace/bfs.img
BFS_ELFS := \
	$(ROOT_DIR)/build/uspace/apps/hello/hello \
	$(ROOT_DIR)/build/uspace/servers/echo/echo

MKFS := $(ROOT_DIR)/scripts/mkfs.bfs.py


.PHONY: all $(SERVERS) $(BFS) $(PM)

all: $(SERVERS) $(BFS) $(PM)

$(PM): $(BFS)
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk

$(BFS): $(SERVERS)
	@echo "  MAKE\t$@"
	@$(PYTHON) $(MKFS) -o $(BFS_PATH) $(BFS_ELFS) -s

$(SERVERS):
	@echo "  MAKE\t$@"
	@$(MAKE) -C $@ all -f$(ROOT_DIR)/scripts/userapp.mk