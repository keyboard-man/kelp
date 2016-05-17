/*************************************************************************
	> File Name: query_service.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月27日 星期五 15时36分53秒
 ************************************************************************/

#include "query_service.h"

namespace kelp
{
QueryService::QueryService(ENM::Node& node,const std::string& path)
	:node_(node),path_(path)
{
	//init log
	log_ = log4cxx::Logger::getLogger("query_service");
	//get all so file under path
	GetFile();

	AddService();

	node_.service()->run(false);
}

void QueryService::GetFile()
{
	if(!boost::filesystem::exists(path_))
	{
		std::ostringstream oss;
		oss << "path do not exists!!";
		LOG4CXX_WARN(log_,oss.str());
	}
	else if(path_.empty())
	{
		std::ostringstream oss;
		oss << "path is empty!";
		LOG4CXX_WARN(log_,oss.str());
	}
	else
	{
		boost::filesystem::directory_iterator end_it;
		for(boost::filesystem::directory_iterator it(path_);
				it!=end_it;++it)
		{
			boost::filesystem::path temp(*it);
			//only load so file
			if(temp.extension() == ".so")
			{
				file_list_.push_back(temp.string());
				std::ostringstream oss;
				oss << "find " << temp.filename();
				LOG4CXX_DEBUG(log_,oss.str());
			}
		}
	}
}

void QueryService::AddService()
{
	std::list<std::string>::iterator iter = file_list_.begin();
	void* handler;
	QueryInfo* query;
	QueryObj result;

	for(;iter!=file_list_.end();++iter)
	{
		std::string temp_path = *iter;
		LOG4CXX_INFO(log_,temp_path);
		handler = dlopen(temp_path.c_str(),RTLD_LAZY);

		if(!handler)
		{
			//load failed
			LOG4CXX_WARN(log_,"Can not load so: "+*iter);
			continue;
		}
		dlerror();

		query = (QueryInfo *)dlsym(handler,g_query_name.c_str());
		const char* dlsym_error = dlerror();
		if(dlsym_error)
		{
			dlclose(handler);
			LOG4CXX_WARN(log_,"Can not find QueryInfo in "+*iter);
			continue;
		}
		
		result = query->handler();
		node_.service()->addService(result.name,result.object,false);
		LOG4CXX_INFO(log_,"add service "+result.name);
	}
}
}
