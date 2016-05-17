/*************************************************************************
	> File Name: rrd_module.cpp
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年05月05日 星期二 11时41分02秒
 ************************************************************************/

#include "rrd_module.h"

kelp::DBModuleInfo rrdtool = {
	RRDModule::InitCallback,
	RRDModule::HandlerCallback,
	RRDModule::CleanupCallback,
};

std::string root_file_path;
int RRDModule::InitCallback(int argc,char** argv)
{
	std::cout << "This is Init Callback" << std::endl;
	std::cout << "argc=" << argc << std::endl;
	for(int i=0;i<argc;i++)
	{
		std::cout << "argv[" << i << "]:" << argv[i] << std::endl;
	}
	root_file_path = argv[0];
	std::cout << "End of Init Callback:" << root_file_path << std::endl;
	return 0;
}

void RRDModule::HandlerCallback(const char*objdata,int objsize, const char* path)
{
	std::cout << "This is  RRD Handler Callback" << std::endl;
	std::string str_path(path);
	mongo::BSONObj bo_data = mongo::BSONObj(objdata);
	long long time_long =  bo_data["time"].numberLong();
	time_t timestamp = time_t(time_long);
	bo_data = bo_data.removeField("time");
	const char* key = bo_data.firstElementFieldName();            //获取数据源名称
	const std::string ds_name(key);
	std::string str_path_d =root_file_path +str_path+'/';
	std::string str_path_x;
	int mkdir_sgn;
	while(str_path_d !="")
	{
		mkdir_sgn = str_path_d.find('/');
		str_path_x = str_path_x+'/'+str_path_d.substr(0,mkdir_sgn);
		if(access(str_path_x.c_str(),0))
			mkdir(str_path_x.c_str(),0755);
		str_path_d =str_path_d.substr(mkdir_sgn+1);
	}
	std::string	str_file =root_file_path +str_path +'/'+ ds_name +".rrd";
	const std::string filename = str_file;
	kelp::RRDOperator opt(filename,ds_name);
	double data;
	data = bo_data[ds_name].numberDouble();
	opt.InsertNum(timestamp,data);
	std::cout << "\nEnd of RRD Handler Callback!" <<std::endl;
}


int RRDModule::CleanupCallback(void)
{
	std::cout << "This is Cleanup Callback" << std::endl;

	std::cout << "End of Cleanup Callback" << std::endl;
	return 0;
}
