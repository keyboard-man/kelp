################################################################################
## @file: 	common.cmd.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	设定各种命令.
## @version	1.0
###############################################################################

ifeq ($(AR),)
	AR		:= ar
endif

ifeq ($(AS),)
	AS		:= as
endif

ifeq ($(CC),)
	CC		:= gcc 
endif

ifeq ($(CXX),)
	CXX		:= g++
endif

ifeq ($(CPP),)
	CPP             := cpp
endif

ifeq ($(CD),)
	CD	        := cd
endif

ifeq ($(RM),)
	RM		:= rm -fr
endif

ifeq ($(RM),rm -f)
	RM		:= rm -fr
endif

ifeq ($(LN),)
	LN		:= ln -sf
endif

ifeq ($(MV),)
	MV		:= mv
endif

ifeq ($(MKDIR),)
	MKDIR		:= mkdir -p
endif

ifeq ($(ECHO),)
	ECHO		:= echo
endif

ifeq ($(SHELL),)	
	SHELL		:= /bin/sh
endif

ifeq ($(CTARGS),)
	CTARGS		:= ctags --extra=+fq \
	--c++-types=cfgmnpstu --append=yes 
endif

ifeq ($(CSCOPE_CMD),)
	CSCOPE_CMD	:= cscope -b
endif

ifeq ($(MAKE),)
	MAKE		:= make
endif

ifeq ($(SED),)
	SED		:= sed
endif

ifeq ($(LD),)
	LD		:= $(CC)
endif

ifeq ($(LD),ld)
	LD		:= $(CC)
endif

ifeq ($(STRIP),)
	STRIP		:= strip -s
endif

ifeq ($(ICE_SLICE),)
	ICE_SLICE	:= slice2cpp
endif
