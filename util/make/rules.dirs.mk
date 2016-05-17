################################################################################
## @file: 	rules.dirs.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	编译多个子目录的rules.
## @version	1.0
###############################################################################

ifeq ($(MAKEFILE),)
        MAKEFILE        := Makefile
endif

ifeq ($(release),1)
        debug   = 0
endif

include $(MAKE_RULES_DIR)/common.flags.mk

LOCAL_TARGETS	= all release debug clean moreclean cscope distclean docs tags

.PHONY: $(LOCAL_TARGETS)
$(LOCAL_TARGETS): makefile_name
	@$(MAKE) -S -f $(MAKEFILE) CFLAGS_PASS="$(CFLAGS)" LDFLAGS_PASS="$(LDFLAGS)" \
	DCFLAGS_PASS="$(DCFLAGS)" DLDFLAGS_PASS="$(DLDFLAGS)" \
	DEFAULT_FLAGS_PASS=$(DEFAULT_FLAGS) release=$(release) \
	LOCAL_TOP_DIR=$(LOCAL_TOP_DIR) LOCAL_TARGET=$@ $(DIRS)

.PHONY: $(DIRS)
$(DIRS): 
	@$(MAKE) -f $(basename $(MAKEFILE)) -C $@ CFLAGS_PASS="$(CFLAGS)" \
	DCFLAGS_PASS="$(DCFLAGS)" DLDFLAGS_PASS="$(DLDFLAGS)" \
	DEFAULT_FLAGS=$(DEFAULT_FLAGS) release=$(release) \
	LOCAL_TOP_DIR=$(LOCAL_TOP_DIR) LDFLAGS_PASS="$(LDFLAGS)" \
	$(LOCAL_TARGET)

include $(MAKE_RULES_DIR)/rules.mkname.mk
