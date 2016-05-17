/*************************************************************************
	> File Name: load_test.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年03月31日 星期二 17时24分16秒
 ************************************************************************/

#include <iostream>

#include "mongo/bson/bson.h"

#include "KNN/modules_loader.h"

int main()
{
	kelp::Module module;
	kelp::Modules modules;

	module.name = "example";
	module.enable = true;
	module.path = "/home/vimer/Kelp/src/test/example.so";
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

	char buf[1024]={ };
	int size = 0;
	kelp::ModulesLoader load(modules);
	modules[0].handler(buf,size);
	modules[0].cleanup();
	load.CleanModules(modules);

	load.InitModule(module);
	module.handler(buf,size);
	mongo::BSONObj obj(buf);
	std::cout << obj << std::endl;
	std::cout << size << std::endl;
	module.cleanup();
	load.CleanModule(module);

	return 0;
}
