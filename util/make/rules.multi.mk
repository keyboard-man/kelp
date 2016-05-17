################################################################################
## @file: 	rules.muti.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	生成多个目标的rules.
## @version	1.0
###############################################################################

ifeq ($(MAKEFILE),)
        MAKEFILE        := Makefile
endif

ifeq ($(release),1)
        debug   = 0
endif

include $(MAKE_RULES_DIR)/common.flags.mk

LOCAL_TARGETS	:= all release debug clean moreclean cscope distclean docs tags

.PHONY: $(LOCAL_TARGETS)
$(LOCAL_TARGETS): makefile_name
	@$(MAKE) -S -f $(MAKEFILE) LOCAL_TARGET=$@ CFLAGS_PASS="$(CFLAGS)" \
	LDFLAGS_PASS="$(LDFLAGS)" DCFLAGS_PASS="$(DCFLAGS)" DLDFLAGS_PASS="$(DLDFLAGS)" \
	DEFAULT_FLAGS=$(DEFAULT_FLAGS) \
	release=$(release) $(PROJS)

.PHONY: $(PROJS)
$(PROJS):
	@$(MAKE) -f $(addprefix $(MAKEFILE)., $@) CFLAGS_PASS="$(CFLAGS)" \
	DCFLAGS_PASS="$(DCFLAGS)" DLDFLAGS_PASS="$(DLDFLAGS)" \
	DEFAULT_FLAGS=$(DEFAULT_FLAGS) \
	LDFLAGS_PASS="$(LDFLAGS)" release=$(release) $(LOCAL_TARGET)

include $(MAKE_RULES_DIR)/rules.mkname.mk
