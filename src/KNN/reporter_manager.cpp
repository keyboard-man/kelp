/*************************************************************************
	> File Name: reporter_manager.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月28日 星期一 20时55分34秒
 ************************************************************************/

#include <ace/INET_Addr.h>
#include <ace/SOCK_Connector.h>
#include <cstdlib>
#include <ctime>
#include "reporter_manager.h"

namespace kelp
{
Reporter::Reporter(std::string kcn_ip,std::string uuid,unsigned char level)
	:kcn_ip_(kcn_ip),uuid_(uuid),level_(level)
{
	log_ = log4cxx::Logger::getLogger("reporter");
}

int Reporter::open(void *)
{
	addr_.set(PORT,kcn_ip_.c_str());

	activate(THR_NEW_LWP,THR_NUM);

	return 0;
}

int Reporter::svc(void)
{
	while(loop)
	{
		msg_ = 0;
		LOG4CXX_DEBUG(log_,"wait for msg");
		getq(msg_);

		if(msg_)
		{
			LOG4CXX_DEBUG(log_,"deal with the msg");
			//send it
			char* ch = (char*)msg_->rd_ptr();
			std::string str(ch);
			ReportRecord record;
			record.time = time(NULL);
			strcpy(record.uuid,uuid_.c_str());
			record.level = level_;
			strcpy(record.event,str.c_str());

			if(connector_.connect(peer_,addr_) != 0)
			{
				LOG4CXX_ERROR(log_,"can not connect to kcn");
				peer_.close();
				msg_->release();
				continue;
			}
			peer_.send((char*)&record,sizeof(record));
			std::ostringstream oss;
			oss << "send " << sizeof(record) << " bytes";
			LOG4CXX_DEBUG(log_,oss.str());
			//peer_.close();
			msg_->release();
		}

	}

	peer_.close();
	LOG4CXX_DEBUG(log_,"svc finished");
	return 1;
}

int Reporter::close(u_long)
{
	LOG4CXX_DEBUG(log_,"reporter destroyed");

	return 0;
}

void Reporter::Exit()
{
	loop = false;
	msg_queue()->deactivate();
	LOG4CXX_DEBUG(log_,"queue deactivated");
	thr_mgr()->cancel_all();
	LOG4CXX_DEBUG(log_,"thread all canceled");

	wait();
	LOG4CXX_DEBUG(log_,"wait finished");
}

ReporterManager::ReporterManager(ENM::Node& node, ConfLoader& loader)
	:node_(node),loader_(loader),path_(loader.GetReportModules())
{
	log_ = log4cxx::Logger::getLogger("reporter_manager");

	Init();
}

void ReporterManager::Start(void)
{
	LOG4CXX_INFO(log_,"starting...");
	while(loop)
	{
		reporter_ptr_->open(0);
		LaunchReport();

		while(!reload)
		{
			boost::this_thread::sleep_for(boost::chrono::seconds(CHECK_TIME));
		}

		if(!loop)
			return ;

		LOG4CXX_INFO(log_,"reloading...");
		Init();
	}

	//reporter_ptr_->wait();
}

void ReporterManager::Init()
{
	//find the kcn node
	CGN::USNTopoMap topo_map = node_.getRelation();
	std::vector<std::string> uuids = topo_map[Coral::prev];
	std::list<std::string> stack;
	std::vector<std::string> top_nodes;
	for(auto x : uuids)
	{
		stack.push_back(x);
		LOG4CXX_DEBUG(log_,x+"==>stack");
	}
	while(!stack.empty())
	{
		std::string uuid_temp = stack.back();
		LOG4CXX_DEBUG(log_,uuid_temp+"<==stack");
		stack.pop_back();
		CGN::USNTopoMap temp_map = node_.getRelation(uuid_temp);
		std::vector<std::string> temp = temp_map[Coral::prev];
		if(temp.empty())
		{
			//find the top level node
			top_nodes.push_back(uuid_temp);
			LOG4CXX_DEBUG(log_,"find kcn:"+uuid_temp);
		}
		else
		{
			for(auto x : temp)
			{
				stack.push_back(x);
				LOG4CXX_DEBUG(log_,x+"==>stack");
			}
		}
	}
	if(top_nodes.size() <= 0)
	{
		//can not find the kcn node
		LOG4CXX_WARN(log_,"can not find kcn node");
		throw "can not find kcn node";
	}
	else if(top_nodes.size() > 1)
	{
		//find more than one kcn node
		kcn_uuid_ = top_nodes.front();
		kcn_ip_ = node_.getUSNConfig(kcn_uuid_,"ip");
		LOG4CXX_WARN(log_,"find more than one kcn node,use:"+kcn_uuid_);
	}
	else
	{
		//find the only kcn node
		kcn_uuid_ = top_nodes.front();
		kcn_ip_ = node_.getUSNConfig(kcn_uuid_,"ip");
		LOG4CXX_INFO(log_,"find the kcn node:"+kcn_uuid_);
	}

	//make up reporter
	if(kcn_ip_ != "")
	{
		std::string uuid = node_.selfUUID();
		reporter_ptr_ = new Reporter(kcn_ip_,uuid);
	}
	else
		throw "illeagl kcn ip address!";

	//make up repprter client
	if(reporter_ptr_)
	{
		GetFile();
	}
	else
		throw "have no leagl kcn node!";

	reload = false;
}

void ReporterManager::Clean()
{
	if(!handle_list_.empty())
	{
		std::list<void*>::iterator iter
			= handle_list_.begin();
		for(;iter!=handle_list_.end();++iter)
		{
			dlclose(*iter);
			const char* dlsym_err = dlerror();
			if(dlsym)
				LOG4CXX_DEBUG(log_,dlsym_err);
		}

		handle_list_.clear();
		launch_list_.clear();
		LOG4CXX_DEBUG(log_,"reporter module clean");
	}

	if(reporter_ptr_)
	{
		reporter_ptr_->Exit();
		delete reporter_ptr_;
		reporter_ptr_ = NULL;
		LOG4CXX_DEBUG(log_,"reporter destroy");
	}
}

void ReporterManager::Stop()
{
	LOG4CXX_INFO(log_,"stopping...");
	//Clean();
	loop = false;
	reload = true;
}

void ReporterManager::Reload()
{
	LOG4CXX_DEBUG(log_,"reload callback");

	reload = true;
}

void ReporterManager::GetFile()
{
	if(!boost::filesystem::exists(path_))
	{
		LOG4CXX_WARN(log_,"path do not exists!!");
	}
	else if(path_.empty())
	{
		LOG4CXX_WARN(log_,"path is empty");
	}
	else
	{
		boost::filesystem::directory_iterator end_it;
		for(boost::filesystem::directory_iterator it(path_);
				it!=end_it;++it)
		{
			boost::filesystem::path temp(*it);
			//only load so file
			if((temp.extension() == ".so"))
			{
				file_list_.push_back(temp.string());
				std::ostringstream oss;
				oss << "find" << temp.filename();
				LOG4CXX_DEBUG(log_,oss.str());
			}
		}
	}

	//load so file
	void *handle_temp;
	void (*lanuch)(Reporter*);

	std::list<std::string>::iterator iter = file_list_.begin();
	for(;iter!=file_list_.end();++iter)
	{
		std::string temp_path = *iter;
		LOG4CXX_INFO(log_,temp_path);
		handle_temp = dlopen(temp_path.c_str(),RTLD_LAZY);

		if(!handle_temp)
		{
			//load failed
			LOG4CXX_WARN(log_,"Can not load so: "+*iter);
			continue;
		}
		dlerror();

		lanuch = (void(*)(Reporter*))dlsym(handle_temp,g_launch_name.c_str());
		const char* dlsym_error = dlerror();
		if(dlsym_error)
		{
			LOG4CXX_WARN(log_,dlsym_error);
			dlclose(handle_temp);
			LOG4CXX_WARN(log_,"Can not find lanuch function in "+*iter);
			continue;
		}

		handle_list_.push_back(handle_temp);
		launch_list_.push_back(lanuch);
	}
}

void ReporterManager::LaunchReport()
{
	std::list<void(*)(Reporter*)>::iterator iter = launch_list_.begin();
	for(;iter!=launch_list_.end();++iter)
	{
		(*iter)(reporter_ptr_);
	}
}
}
