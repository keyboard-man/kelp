/*************************************************************************
	> File Name: report_server.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月28日 星期一 10时01分12秒
 ************************************************************************/


#include "report_server.h"

namespace kelp
{
boost::shared_ptr<ReportCache> ReportCache::s_instance_;

ReportCache::ReportCache(int size):size_(size)
{
	log_ = log4cxx::Logger::getLogger("report_cache");
}

ReportCache& ReportCache::GetInstance(int size)
{
	static boost::mutex mu;
	if(s_instance_.get() == NULL)
	{
		boost::mutex::scoped_lock lock(mu);
		if(s_instance_.get() == NULL)
		{
			s_instance_.reset(new ReportCache(size));
		}
	}

	return *s_instance_;
}

bool ReportCache::Insert(time_t time,const char *uuid,unsigned char level,const char *event)
{
	ReportRecord temp;
	temp.time = time;
	strcpy(temp.uuid,uuid);
	temp.level = level;
	strcpy(temp.event,event);
	
	return Insert(temp);
}

bool ReportCache::Insert(ReportRecord temp)
{
	if(records_.size()>=size_)
	{
		records_.pop_front();

		LOG4CXX_INFO(log_,"record list is full, fornt will be poped");
	}

	records_.push_back(temp);
	std::ostringstream oss;
	oss << "new record pushed into list: " << temp.event;
	LOG4CXX_INFO(log_,oss.str());

	return true;
}

ServerHandler::ServerHandler()
{
	log_ = log4cxx::Logger::getLogger("server_handler");
}

int ServerHandler::open(void *p)
{
	if(super::open(p) == -1)
	{
		return -1;
	}

	ACE_INET_Addr peer_addr;
	if(this->peer().get_remote_addr(peer_addr) == 0)
	{
		LOG4CXX_INFO(log_,"Connected");
	}

	return 0;
}

int ServerHandler::handle_input(ACE_HANDLE)
{
	const int INPUT_SIZE = 2* 1024;
	char buffer[INPUT_SIZE];
	memset(buffer,0,INPUT_SIZE);

	int recv_cnt = this->peer().recv(buffer,INPUT_SIZE);

	if(recv_cnt <= 0)
	{
		LOG4CXX_WARN(log_,"Connnection close");
		return -1;
	}

	ReportRecord record;
	//memcpy(&record,buffer,sizeof(buffer));
	memcpy(&record,buffer,recv_cnt);
	ReportCache& cache = ReportCache::GetInstance();
	std::ostringstream oss; 
	oss << "recv " << recv_cnt << " bytes";
	LOG4CXX_DEBUG(log_,oss.str());
	cache.Insert(record);

	//TODO: insert the record into db!

	return 0;
}

ReportServer::ReportServer():cache_(ReportCache::GetInstance())
{
	log_ = log4cxx::Logger::getLogger("report_server");
}

void ReportServer::Start()
{
	const int ACCEPT_PORT = 30036;
	ACE_INET_Addr port_to_accept(ACCEPT_PORT);

	if(server.open(port_to_accept) == -1)
	{
		LOG4CXX_ERROR(log_,"Can not open report server");
		return;
	}

	ACE_Reactor::instance()->run_reactor_event_loop();

	while(!ACE_Reactor::instance()->reactor_event_loop_done())
		;

	LOG4CXX_INFO(log_,"Report server stoped");
	return;
}

void ReportServer::Stop()
{
	ACE_Reactor::instance()->end_reactor_event_loop();
	LOG4CXX_DEBUG(log_,"stop the reactor");

	server.close();
}

void ReportServer::Reload()
{
	Stop();

	ACE_Reactor::instance()->run_reactor_event_loop();
}
}
