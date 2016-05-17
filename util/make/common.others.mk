################################################################################
## @file: 	common.others.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	设定其他使用到的变量.
## @version	1.0
###############################################################################

#SVN_VERSION	:= $(subst :, ,$(subst S,,$(subst M,,$(shell [ -f .svn/entries ] && svnversion .))))
#SVN_VERSION	:= $(word $(words $(SVN_VERSION)),$(SVN_VERSION))

TARGET		:= $(strip $(TARGET))
OUTDIR		:= $(strip $(OUTDIR))
VERSION		:= $(strip $(VERSION))
SVN_VERSION 	:= $(strip $(SVN_VERSION))
SVN_VERSION_MAJOR := $(strip $(SVN_VERSION_MAJOR))
DATE		:= $(shell date +%Y%m%d)
VPATH   	:= $(OBJECTS_DIR):$(DEPS_DIR):.

VERSION_TAIL	:=


ifeq ($(DOCS_DIR),)
	DOCS_DIR 	:= docs 
endif

ifeq ($(VERSION),)
ifeq ($(debug),1)
	VERSION		:= $(DATE)
else  #ifeq ($(debug),1)
	VERSION		:= r$(DATE)
endif #ifeq ($(debug),1)
else #ifeq ($(VERSION),)
ifeq ($(VERSION),svn)
ifneq ($(SVN_VERSION),)
ifeq ($(SVN_VERSION_MAJOR),)
	VERSION		:= $(SVN_VERSION)
	VERSION_TAIL	:=
else #ifeq ($(SVN_VERSION_MAJOR),)
	VERSION		:= $(SVN_VERSION_MAJOR)
        VERSION_TAIL	:= $(SVN_VERSION)
endif #ifeq ($(SVN_VERSION_MAJOR),)
endif #ifneq ($(SVN_VERSION),)
endif #ifeq ($(VERSION),svn)
ifeq ($(debug),1)
ifeq ($(NVERSION_DATE),)
	VERSION_TAIL 	:= $(strip $(VERSION_TAIL))
ifneq ($(VERSION_TAIL),)
	VERSION_TAIL	:= $(VERSION_TAIL).$(DATE)
else #ifeq ($(VERSION_TAIL),)
	VERSION_TAIL	:= $(DATE)
endif #ifeq ($(VERSION_TAIL),)
endif #ifeq ($(NVERSION_DATE),)
endif #ifeq ($(debug),1)
endif #ifeq ($(VERSION),)

ifeq ($(NVERSION),)
	NVERSION	:= 0
endif

ifeq ($(NVERSION_DATE),)
	NVERSION_DATE 	:= 0
endif

VERSION_TAIL 	:= $(strip $(VERSION_TAIL))

