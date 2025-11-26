# Linux-like kbuild core
# Will be included by kernel, uspace, libs Makefiles
# a module means a top-level component that can be compiled to an independent unit
# (e.g. kernel, servers, apps and libraries)
# modules which include this file should define:
#	MOD_NAME		name of the module. e.g. "kernel", "uspace/app1"
#	MOD_SRCDIR		source directory of the module. e.g. $(ROOT_DIR)/kernel
#	MOD_OBJDIR		object directory of the module. e.g. $(BUILD_DIR)/kernel
#	CFLAGS			possible additional CFLAGS for this module

# like linux, we define our building makefiles as "CBuild". just for fun!
SUB_MKS := $(shell find $(MOD_SRCDIR) -name "CBuild")

OBJS := 
# traverse all sub-makefiles to collect object files.
# $(1) - path of the module's Cbuild file
define collect_objs
	# clear previous obj-y
	$(eval obj-y := )
	# include each sub-makefile to populate obj-y
	$(eval include $(1))

	$(eval cbuild_dir := $(dir $(1)))
	$(eval cbuild_rel_dir := $(patsubst $(MOD_SRCDIR)/%,%,$(cbuild_dir)))

	$(eval local_objs := $(patsubst %,$(cbuild_rel_dir)%,$(obj-y)))
	$(eval OBJS += $(patsubst %,$(MOD_OBJDIR)/%,$(local_objs)))
endef

$(foreach sub_mk,$(SUB_MKS),$(eval $(call collect_objs,$(sub_mk))))

# General compiling rules

$(MOD_OBJDIR)/%.o: $(MOD_SRCDIR)/%.c
	@echo "  CC\t$(shell realpath $@ -m --relative-to=$(BUILD_DIR))"
	@$(CC) $(CFLAGS) -c $(shell realpath $< --relative-to=$(MOD_SRCDIR)) -o $@

$(MOD_OBJDIR)/%.o: $(MOD_SRCDIR)/%.S
	@echo "  AS\t$(shell realpath $@ -m --relative-to=$(BUILD_DIR))"
	@$(CC) $(CFLAGS) -c $(shell realpath $< --relative-to=$(MOD_SRCDIR)) -o $@

MODULE_SUBDIRS := $(sort $(dir $(OBJS)))

.PHONY: $(MOD_OBJDIR)_dirs

$(MOD_OBJDIR)_dirs:
	@mkdir -p . $(MODULE_SUBDIRS)