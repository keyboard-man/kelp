/*************************************************************************
	> File Name: rrd_module.h
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年05月05日 星期二 11时38分12秒
 ************************************************************************/

#ifndef KELP_MODULE_RRD_MODULE_H_
#define KELP_MODULE_RRD_MODULE_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <stdarg.h>  
#include <sys/stat.h>  
#include "mongo/client/dbclient.h"
#include "comm/module_info.h"
#include "rrd_operator.h"

class RRDModule
{
public:
	static int InitCallback(int argc,char** argv);
	static void HandlerCallback(const char* objdata,int objsize,const char* path);
	static int CleanupCallback(void);

private:
	std::string path;
};

#endif
