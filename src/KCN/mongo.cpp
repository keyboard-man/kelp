/*************************************************************************
	> File Name: mongo.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 21时40分26秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <mongo/client/dbclient.h>
#include "comm/module_info.h"

int InitCallback(int,char**);
void HandlerCallback(const char*,int,const char*);
int CleanupCallback(void);

kelp::DBModuleInfo MongoDB = {
	InitCallback,
	HandlerCallback,
	CleanupCallback
};

std::string dbname;
int InitCallback(int argc,char** argv)
{
	dbname = argv[0];

	return 0;
}

void HandlerCallback(const char* objdata,int objsize,const char* path)
{
	std::string collection(path);
	mongo::BSONObj obj(objdata);

	std::cout << "OBJ: " << obj << std::endl;
	std::cout << "will be insert to " << dbname << "." << collection << std::endl;
}

int CleanupCallback(void)
{

	return 0;
}
