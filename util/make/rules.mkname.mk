###############################################################################
## @file: 	rules.mkname.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	输出使用的makefile名称的rules.
## @version	1.0
###############################################################################

ifeq ($(LOCAL_TOP_DIR),)
	LOCAL_TOP_DIR	:= $(shell pwd)/
endif

.PHONY: makefile_name
makefile_name:
	@echo
	@echo Makefile: $(subst $(LOCAL_TOP_DIR),,$(shell pwd)/$(MAKEFILE))
	@echo
