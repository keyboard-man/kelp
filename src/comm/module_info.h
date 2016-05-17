/*************************************************************************
	> File Name: module_info.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年03月27日 星期五 15时18分15秒
 ************************************************************************/

#ifndef KELP_COMM_MODULE_INFO_H_
#define KELP_COMM_MODULE_INFO_H_
#include <string>
#include <Ice/Ice.h>
#include <Ice/Object.h>

namespace kelp{
struct ModuleInfo
{
	//int (*init)(int argc,char** argv);
	int (*init)(std::string);
	void (*handler)(char**,int&);
	int (*cleanup)(void);
};

struct DBModuleInfo
{
	//int (*init)(int argc,char** argv);
	int (*init)(std::string);
	void (*handler)(const char* objdata,int objsize,const char* path);
	int (*cleanup)(void);
};

struct QueryObj
{
	std::string name;
	Ice::ObjectPtr object;
};

struct QueryInfo
{
	QueryObj (*handler)(void);
};

const std::string g_query_name = "QueryModule";
};

#endif
