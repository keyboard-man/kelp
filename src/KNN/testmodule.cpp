/*************************************************************************
	> File Name: testmodule.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月30日 星期四 19时15分30秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <mongo/bson/bson.h>

#include "comm/module_info.h"

int InitCallback(std::string);
void HandlerCallback(char**,int&);
int CleanupCallback(void);

kelp::ModuleInfo testModule = {
	InitCallback,
	HandlerCallback,
	CleanupCallback,
};

int InitCallback(std::string params)
{
	std::cout << "testModule InitCallback" << std::endl;

	return 0;
}

void HandlerCallback(char** buf,int& size)
{
	std::cout << "testModule HandlerCallback" << std::endl;

	mongo::BSONObjBuilder builder;
	builder.append("testModule",(rand()%100+1));
	mongo::BSONObj obj = builder.obj();

	size = obj.objsize();
	*buf = new char[size]();
	memcpy(*buf,obj.objdata(),size);
}

int CleanupCallback(void)
{
	std::cout << "testModule CleanupCallback" << std::endl;

	return 0;
}
