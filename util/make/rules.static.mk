################################################################################
## @file: 	rules.static.mk
## @author:	Ðì³Â·æ <johnx@mail.ustc.edu.cn>
## @brief	Éú³É¾²Ì¬¿âµÄrules.
## @version	1.0
###############################################################################

ifeq ($(release),1)
        debug   = 0
endif

DEPS_DIR	:= .deps
OBJECTS_DIR     := .objs

include $(MAKE_RULES_DIR)/common.files.mk
include $(MAKE_RULES_DIR)/common.flags.mk
include $(MAKE_RULES_DIR)/common.cmd.mk
include $(MAKE_RULES_DIR)/common.others.mk

TARGET_FILE_SYMBOL		:= lib$(TARGET).a

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

include $(MAKE_RULES_DIR)/rules.common.mk

$(TARGET_FILE_FULL): $(OBJECTS)
	$(AR) $(ARFLAGS) $@  $(addprefix $(OBJECTS_DIR)/, $(OBJECTS)) 
ifneq ($(NVERSION),1)
ifneq ($(OUTDIR),)
		-@$(CD)	$(OUTDIR) && $(LN)  $(TARGET_FILE_SHORT) $(TARGET_FILE_SYMBOL)
ifneq ($(VERSION_TAIL),)
	@$(LN)  $(TARGET_FILE_SHORT) $(TARGET_FILE_SYMBOL_FULL)
endif
else
		-@$(LN)  $(TARGET_FILE_SHORT) $(TARGET_FILE_SYMBOL)
ifneq ($(VERSION_TAIL),)
	@$(LN)  $(TARGET_FILE_SHORT) $(TARGET_FILE_SYMBOL_FULL)
endif
endif
endif
	@$(ECHO)
