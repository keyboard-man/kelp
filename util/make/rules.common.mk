################################################################################
## @file: 	rules.common.mk
## @author:	Ðì³Â·æ <johnx@mail.ustc.edu.cn>
## @brief	¹«ÓÃµÄrules.
## @version	1.0
###############################################################################

.PHONY: all 
all: makefile_name depend $(TARGET_FILE_FULL)


.PHONY: release
release:  
	@$(RM) $(addprefix $(OBJECTS_DIR)/, $(OBJECTS))
	@$(MAKE) -f $(MAKEFILE) release=1 all

.PHONY: debug
debug:
	@$(RM) $(addprefix $(OBJECTS_DIR)/, $(OBJECTS))
	@$(MAKE) -f $(MAKEFILE) release=0 all

.PHONY: clean 
clean: makefile_name 
	@$(ECHO) -e "\033[1;35m"clean"\033[1;31m" "$(TARGET_FILE) $(OBJECTS)""\033[0m"
	@$(RM) $(TARGET_FILE) $(TARGET_FILE_SHORT_FULL) $(TARGET_FILE_FULL) $(addprefix $(OBJECTS_DIR)/, $(OBJECTS))
	@$(ECHO)

.PHONY: moreclean 
moreclean: makefile_name 
	@$(ECHO) -e "\033[1;35m"clean"\033[1;31m" "$(filter-out $(FILES) $(FILES_H),$(wildcard $(TARGET_FILE)*)) $(OBJECTS)""\033[0m"
	@$(RM) $(filter-out $(FILES) $(FILES_H),$(wildcard $(TARGET_FILE)*)) $(addprefix $(OBJECTS_DIR)/, $(OBJECTS))
	@$(ECHO)

.PHONY: distclean
distclean: makefile_name
	@$(ECHO) -e "\033[1;35m"clean"\033[1;31m" \
	"$(filter-out $(FILES) $(FILES_H),$(wildcard $(TARGET_FILE)*)) $(OBJECTS)" \
	"tags cscope.out $(DEPS_DIR) $(OBJECTS_DIR) $(DOCS_DIR) $(ICE_H_FILES) $(ICE_CPP_FILES)""\033[0m"
	@$(RM) $(filter-out $(FILES) $(FILES_H),$(wildcard $(TARGET_FILE)*))
	@$(RM) tags cscope.out
	@$(RM) $(DEPS_DIR) $(OBJECTS_DIR) $(ICE_H_FILES) $(ICE_CPP_FILES)
	@$(RM) $(DOCS_DIR)
	@$(ECHO)

.PHONY: tags 
tags: makefile_name $(FILES) $(FILES_H)
	@$(MKDIR) $(DOCS_DIR)
	@$(CTARGS) $?
	@$(ECHO)

.PHONY: cscope
cscope: makefile_name $(FILES) $(FILES_H)
	@$(CSCOPE_CMD) $?
	@$(ECHO)

.PHONY: docs
docs: makefile_name $(DOXYFILE) $(FILES_H) $(FILES)
	@doxygen $(DOXYFILE) 
	@$(ECHO)

$(OBJECTS): %.o: %$(FILE_SUFFIX)
	$(CC) $(LOCAL_CFLAGS) $(INCLUDES) -c $< -o $(OBJECTS_DIR)/$@

$(FILES_DEPS): %.dep: %$(FILE_SUFFIX)  $(ICE_H_FILES)
	$(CC) -MM -MP $(INCLUDES) $< -MF $(DEPS_DIR)/$@


$(ICE_CPP_FILES): %.cpp: %.h

$(ICE_H_FILES): %.h: %.ice
	$(ICE_SLICE) $<

.PHONY: depend
depend: mkdirs $(FILES_DEPS)

.PHONY: mkdirs
mkdirs: $(DEPS_DIR) $(OBJECTS_DIR)

$(DEPS_DIR) $(OBJECTS_DIR):
	$(MKDIR) $@ 
ifeq ($(findstring $(MAKECMDGOALS), clean moreclean distclean tags cscope docs makefile_name),)
-include $(addprefix $(DEPS_DIR)/, $(FILES_DEPS))
#$(addprefix $(DEPS_DIR)/, $(FILES_DEPS)): $(DEPS_DIR)/%.dep: %$(FILE_SUFFIX)
#	@$(MKDIR) -p $(DEPS_DIR) $(OBJECTS_DIR) 
#	$(CC) $(INCLUDES) -MM $< -o $@
#	@$(ECHO) "	"$$\{CC\} $$\{LOCAL_CFLAGS\} $$\{INCLUDES\} -c $< -o $$\{OBJECTS_DIR\}/$$\@ >> $@
endif

include $(MAKE_RULES_DIR)/rules.mkname.mk
