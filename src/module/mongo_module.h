/*************************************************************************
	> File Name: ../modlue/mongo_module.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月28日 星期二 21时21分19秒
 ************************************************************************/

#ifndef KELP_MODULE_MONGO_MODULE_H_
#define KELP_MODULE_MONGO_MODULE_H_

#include <iostream>
#include <string>
#include <cstdlib>

#include "comm/module_info.h"
#include "mongo_operator.h"
class MongoModule
{
public:
	static int InitCallback(int argc,char** argv);
	static void HandlerCallback(const char* objdata,int objsize,const char* path);
	static int CleanupCallback(void);

private:
	std::string path_;
};

#endif
