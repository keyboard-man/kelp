/*************************************************************************
	> File Name: collector.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 15时56分05秒
 ************************************************************************/

#include "collector.h"

namespace kelp
{
Collector::Collector(int time,const DataSource& source,Processer* pro)
	:time_(time),data_source_(source),processer_(pro)
{
	log_ = log4cxx::Logger::getLogger("kcn_collector");
}

int Collector::open(void*)
{
	activate(THR_NEW_LWP,THR_NUM);

	return 0;
}

int Collector::svc(void)
{
	timer_ = new AsyncTimer(ios_,time_,boost::bind(&Collector::PollData,this));

	ios_.run();
	return 0;
}

int Collector::close(u_long)
{
	timer_->Cancel();
	delete timer_;

	return 0;
}

void Collector::Exit()
{
	ios_.stop();
}

void Collector::PollData()
{
	ACE_SOCK_Stream peer;
	ACE_SOCK_Connector connector;
	try
	{
		if(TryToConnect(connector,peer))
		{
			std::ostringstream oss;
			oss << "poll data from cluster/grid: " << data_source_.name;
			LOG4CXX_INFO(log_,oss.str());

			char buf[T_SIZE] = "request";
			if((peer.send(buf,sizeof(buf)))<=0)
				throw "KCN POLLER COLLECTOR SEND REQUEST ERROR!!";
			char* ch = new char[T_SIZE]();
			if((peer.recv(ch,T_SIZE)<=0))
				throw "KCN POLLER COLLECTOR RECV ERROR!!";

			msg_ = new ACE_Message_Block(ch,sizeof(*ch));
			processer_->putq(msg_);
		}
		else
		{
			std::ostringstream oss;
			oss << "Can not poll data form: " << data_source_.name;
			LOG4CXX_WARN(log_,oss.str());
		}
	}
	catch(const char* ch)
	{
		LOG4CXX_ERROR(log_,ch);
	}
}

bool Collector::TryToConnect(ACE_SOCK_Connector& con,ACE_SOCK_Stream& peer)
{
	if(data_source_.node_list.size() == 0)
	{
		std::ostringstream oss;
		oss << data_source_.name << " have no legal IP";
		LOG4CXX_WARN(log_,oss.str());

		return false;
	}

	for(int i=0;i<data_source_.node_list.size();i++)
	{
		std::string ip_temp = data_source_.node_list[i].ip;
		unsigned int port = data_source_.node_list[i].port;
		ACE_INET_Addr addr(port,ip_temp.c_str());
		
		if(con.connect(peer,addr)==0)
		{
			return true;
		}
	}

	std::ostringstream oss;
	oss << "can not connect every host in cluster: " << data_source_.name;
	LOG4CXX_WARN(log_,oss.str());

	return false;
}
}
