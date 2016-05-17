################################################################################
## @file: 	common.flags.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	设定编译参数.
## @version	1.0
###############################################################################

ifeq ($(debug),)
        debug           = 1
endif


ARFLAGS		        := rcs

ifeq ($(DEFAULT_FLAGS),)
	DEFAULT_FLAGS	:= 1
endif

ifeq ($(DEFAULT_FLAGS),1)
ifeq ($(debug),1)
        LOCAL_CFLAGS	:= -Wall -g -D_DEBUG
        LOCAL_CXXFLAGS	:= $(LOCAL_CFLAGS)
        LOCAL_LDFLAGS	:= -D_DEBUG -DDEBUG
else
        LOCAL_CFLAGS	:= -Wall -O3
        LOCAL_CXXFLAGS	:= $(LOCAL_CFLAGS)
        LOCAL_LDFLAGS	:= -Wl,-O3
endif
else
	LOCAL_CFLAGS	:=
	LOCAL_CXXFLAGS	:=
	LOCAL_LDFLAGS	:=
endif

ifeq ($(debug),1)
	LOCAL_CFLAGS	+= $(DCFLAGS)
	LOCAL_CXXFLAGS	+= $(DCFLAGS)
	LOCAL_LDFLAGS	+= $(DLDFLAGS)
else
	LOCAL_CFLAGS	+= $(CFLAGS)
	LOCAL_CXXFLAGS	+= $(CFLAGS)
	LOCAL_LDFLAGS	+= $(LDFLAGS)
endif
