/*************************************************************************
	> File Name: example_module.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年03月31日 星期二 09时18分38秒
 ************************************************************************/

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>

#include "mongo/bson/bson.h"

#include "comm/module_info.h"

int InitCallback(int,char **);
void HandlerCallback(char**,int &);
int CleanupCallback(void);

kelp::ModuleInfo module_info = {
	InitCallback,
	HandlerCallback,
	CleanupCallback,
};

int InitCallback(int argc,char* argv[])
{
	std::cout << "This is Init Callback" << std::endl;
	std::cout << "argc=" << argc << std::endl;
	for(int i=0;i<argc;i++)
	{
		std::cout << "argv[" << i << "]:" << argv[i] << std::endl;
	}

	std::cout << "End of Init Callback" << std::endl;
	return 0;
}

void HandlerCallback(char **buf,int &size)
{
	std::cout << "This is Handler Callback" << std::endl;
	
	mongo::BSONObjBuilder builder;
	builder.append("heartbeat",(long long)time(NULL));
	builder.append("module_info",BSON("time"<<(long long)time(NULL)<<"rand"<<(rand()%100+1)));
	mongo::BSONObj obj = builder.obj();
	std::cout << obj << std::endl;

	size = obj.objsize();
	*buf = new char[size]();
	memcpy(*buf,obj.objdata(),size);
	std::cout << "\nEnd of Handler Callback" << std::endl;
}

int CleanupCallback(void)
{
	std::cout << "This is Cleanup Callback" << std::endl;

	std::cout << "End of Cleanup Callback" << std::endl;
	return 0;
}
