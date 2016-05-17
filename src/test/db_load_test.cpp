/*************************************************************************
	> File Name: db_load_test.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月28日 星期二 22时16分59秒
 ************************************************************************/

#include <iostream>

#include "mongo/bson/bson.h"
#include "log4cxx/propertyconfigurator.h"

#include "KCN/dbmodules_loader.h"

int main()
{
	log4cxx::PropertyConfigurator::configure("../comm/log4cxx.properties");
	kelp::DBModule module;
	kelp::DBModules modules;

	module.module_name = "MongoDB";
	module.enable = true;
	module.path = "/home/vimer/Kelp/src/modlue/mongo_module.so";
	module.argc = 2;
	char* p1 = (char *)"first";
	char* p2 = (char *)"second";
	char* argv[2];
	argv[0] = p1;
	argv[1] = p2;
	module.argv = argv;
	module.dl_handler = NULL;
	module.init = NULL;
	module.handler = NULL;
	module.cleanup = NULL;

	modules.push_back(module);

	kelp::DBModulesLoader load(modules);
	modules[0].handler(p1,2,p2);
	modules[0].cleanup();

	return 0;
}
