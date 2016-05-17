/*************************************************************************
	> File Name: ../test/mongo_module_test.cpp
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年05月08日 星期五 11时29分25秒
 ************************************************************************/


#include <iostream>
#include <string>
#include "module/mongo_module.h"
#include "module/rrd_module.h"
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
int main(int argc,char ** argv)
{	
	log4cxx::PropertyConfigurator::configure("../comm/log4cxx.properties");
	mongo::BSONObj bo = BSON("time"<<1430365308<<"cpu"<<84.88);
	const char* objdata = bo.objdata();
	int size_objdata = sizeof(objdata);
	std::string	path = "test";
//	MongoModule::HandlerCallback(objdata,size_objdata,path.c_str());
	RRDModule::HandlerCallback(objdata,size_objdata,path.c_str());

	return 0;
}
	
