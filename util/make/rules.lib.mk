################################################################################
## @file: 	rules.lib.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	生成共享库的rules.
## @version	1.0
###############################################################################

ifeq ($(release),1)
        debug   = 0
endif

ifeq ($(SOEXT),)
	SOEXT		:= .so
endif

SOEXT		:= $(strip $(SOEXT))

DEPS_DIR	:= .shdeps
OBJECTS_DIR     := .shobjs

include $(MAKE_RULES_DIR)/common.flags.mk
include $(MAKE_RULES_DIR)/common.files.mk
include $(MAKE_RULES_DIR)/common.cmd.mk
include $(MAKE_RULES_DIR)/common.others.mk

TARGET_FILE_SYMBOL		:= lib$(TARGET)$(SOEXT)

ifeq ($(OUTDIR),)
	TARGET_FILE		:= $(TARGET_FILE_SYMBOL)
else
	TARGET_FILE		:= $(OUTDIR)/$(TARGET_FILE_SYMBOL)
endif

ifneq ($(NVERSION),1)
	TARGET_FILE_SYMBOL_FULL	:= $(TARGET_FILE_SYMBOL).$(VERSION)
	TARGET_FILE_SHORT_FULL	:= $(TARGET_FILE).$(VERSION)
ifneq ($(VERSION_TAIL),) 
	TARGET_FILE_FULL	:= $(TARGET_FILE).$(VERSION).$(VERSION_TAIL)
	TARGET_FILE_SHORT	:= $(TARGET_FILE_SYMBOL).$(VERSION).$(VERSION_TAIL)
else
	TARGET_FILE_FULL	:= $(TARGET_FILE).$(VERSION)
	TARGET_FILE_SHORT	:= $(TARGET_FILE_SYMBOL).$(VERSION)
endif
else
	TARGET_FILE_SYMBOL_FULL	:= $(TARGET_FILE_SYMBOL)
	TARGET_FILE_FULL	:= $(TARGET_FILE)
	TARGET_FILE_SHORT_FULL	:= $(TARGET_FILE)
	TARGET_FILE_SHORT	:= $(TARGET_FILE_SYMBOL)
endif

LOCAL_CFLAGS  += -fPIC
LOCAL_LDFLAGS += -Wl,-Bsymbolic -Wl,-E -Wl,-h 

include $(MAKE_RULES_DIR)/rules.common.mk

$(TARGET_FILE_FULL): $(OBJECTS)
	$(LD) -shared $(LOCAL_LDFLAGS) -Wl,$(TARGET_FILE_SYMBOL_FULL) $(addprefix $(OBJECTS_DIR)/, $(OBJECTS)) $(LIBS) -o $@
ifneq ($(NVERSION),1)
ifneq ($(OUTDIR),)
	@$(CD)	$(OUTDIR) && $(LN)  $(TARGET_FILE_SHORT) $(TARGET_FILE_SYMBOL)
ifneq ($(VERSION_TAIL),)
	@$(CD)	$(OUTDIR) && $(LN)  $(TARGET_FILE_SHORT) $(TARGET_FILE_SYMBOL_FULL)
endif
else
	@$(LN)  $(TARGET_FILE_SHORT) $(TARGET_FILE_SYMBOL)
ifneq ($(VERSION_TAIL),)
	@$(LN)  $(TARGET_FILE_SHORT) $(TARGET_FILE_SYMBOL_FULL)
endif
endif
endif
ifeq ($(debug),0)
	@$(STRIP) $(TARGET_FILE_FULL)
endif
	@$(ECHO)
