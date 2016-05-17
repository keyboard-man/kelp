/*************************************************************************
	> File Name: ../modlue/mongo_module.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月28日 星期二 21时14分39秒
 ************************************************************************/

#include "mongo_module.h"

kelp::DBModuleInfo MongoDB = {
	MongoModule::InitCallback,
	MongoModule::HandlerCallback,
	MongoModule::CleanupCallback,
};
std::string dbname;
int MongoModule::InitCallback(int argc,char** argv)
{
	std::cout << "This is Init Callback" << std::endl;
	std::cout << "argc=" << argc << std::endl;
	for(int i=0;i<argc;i++)
	{
		std::cout << "argv[" << i << "]:" << argv[i] << std::endl;
	}

	dbname = argv[0];
	std::cout << "End of Init Callback" << std::endl;
	return 0;
}

void MongoModule::HandlerCallback(const char* objdata,int objsize,const char* path)
{
	std::cout << "This is mongo Handler Callback" << std::endl;
	std::string str_path(path);
	int loc;
	std::string dot_path;
	while(str_path !="")
	{	
		loc =str_path.find('/');
		if(loc ==str_path.npos)
		{
			dot_path +=str_path;
			break;
		}
		dot_path = dot_path+str_path.substr(0,loc)+'.';
		str_path =str_path.substr(loc+1);
	}
	kelp::MongoOperator opt(dbname, dot_path);
	mongo::BSONObj data = mongo::BSONObj(objdata);
	opt.Insert(data);
	std::cout << "\nEnd of MongoDB Handler Callback" << std::endl;
}

int MongoModule::CleanupCallback(void)
{
	std::cout << "This is Cleanup Callback" << std::endl;

	std::cout << "End of Cleanup Callback" << std::endl;
	return 0;
}
