################################################################################
## @file: 	template.dir.mk
## @author:	徐陈锋 <johnx@mail.ustc.edu.cn>
## @brief	包含子目录makefile模板.
## @version	1.0
###############################################################################

## NOTE: 这里认为一个生成目标对应一个工程. '当前目录'指$(MAKEFILE)所在目录.

## makefile 文件名，默认为 'Makefile'. 如果文件名不为'Makefile', 必须设定.
MAKEFILE	:=

## 子目录列表. 必须设定, 只能为当前目录的子目录.
DIRS		:=


## 是否使用默认的编译参数. 默认编译参数, 
##	debug: 		CFLAGS=-Wall -g -D_DEBUG, LDFLAGS= 
##	release:	CFLAGS=-Wall -O3, LDFLAGS=-Wl,-O3 
## 在使用默认参数的情况下, 还可以使用下面的CFLAGS, LDFLAGS, DCFLAGS, DLDFLAGS
## 增加编译参数, 甚至覆盖. 默认为使用编译参数
#DEFAULT_FLAGS	:= 0

## 编译和链接参数设定. 无论C还是C++都使用CFLAGS LDFLAGS, 即CPPFLAGS or CXXFLAGS
## 没有被使用. 注意: 这样是不支持C和C++或其他语言混编的, 当然C代码可以当成C++来
## 编译. 如果是个子项目, 使用父项目的编译参数, 注释掉相应的行. 如果要在父项目的
## 编译参数的基础上增加或覆盖, 使用'+=', 如"CFLAGS += $(CFLAGS) YOUR_OWN_FLAGS".
## 如果不想使用父项目或环境变量的参数, 使用如 "CFLAGS := "这样的方式. CFLAGS和
## LDFLAGS用于release编译参数; DCFLAGS和DLDFLAGS用于debug编译参数.
CFLAGS		:= $(CFLAGS_PASS)
DCFLAGS		:= $(DCFLAGS_PASS)
LDFLAGS		:= $(LDFLAGS_PASS)
DLDFLAGS	:= $(DLDFLAGS_PASS)

## 设定make和make all的默认编译参数为release还是debug. 默认为debug, 即release=0
#release	:= 1

## 需要设定环境变量'MAKE_RULES_DIR'.
## 如果不设定环境变量，则在此设定其相对路径
#MAKE_RULES_DIR := ../../make.rules
include $(MAKE_RULES_DIR)/rules.dirs.mk
