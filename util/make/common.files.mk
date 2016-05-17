################################################################################
## @file: 	common.files.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	设定各种文件变量和文件列表变量.
## @version	1.0
###############################################################################

ifeq ($(FILE_H_SUFFIX),)
	FILE_H_SUFFIX 	:= .h
endif

ifeq ($(FILE_SUFFIX),)
	FILE_SUFFIX	:= .cpp
endif

ifeq ($(ICE_FILES),)
	ICE_FILES 	:= $(wildcard *.ice)
endif

ifneq ($(ICE_FILES),)
	ICE_H_FILES	:=  $(patsubst %.ice,%.h,$(ICE_FILES)) 
	ICE_CPP_FILES 	:=  $(patsubst %.ice,%.cpp,$(ICE_FILES))
endif

ifeq ($(FILES_H),)
	FILES_H		:= $(wildcard *$(FILE_H_SUFFIX))
	FILES_H		:= $(filter-out $(ICE_H_FILES),$(FILES_H))
endif

FILES_H			+= $(ICE_H_FILES)

ifeq ($(FILES),)
	FILES		:= $(wildcard *$(FILE_SUFFIX))
	FILES		:= $(filter-out $(ICE_CPP_FILES),$(FILES))
endif

FILES			+= $(ICE_CPP_FILES)

FILES_DEPS		:= $(patsubst %$(FILE_SUFFIX),%.dep,$(FILES))
OBJECTS			:= $(patsubst %$(FILE_SUFFIX),%.o,$(FILES))


ifeq ($(DOXYFILE),)
	DOXYFILE	:= Doxyfile
endif

ifeq ($(MAKEFILE),)
        MAKEFILE        := Makefile
endif
