/*************************************************************************
	> File Name: ksn_poller.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 11时39分22秒
 ************************************************************************/

#include "ksn_poller.h"

namespace kelp
{
KSNPoller::KSNPoller(ENM::Node& node, ConfLoader& loader)
	:node_(node),conf_loader_(loader),t_channel_(loader.GetTCPAcceptPort()),
	data_sources_(loader.GetDataSource()),grid_name_(loader.GetGridName())
{
	log_ = log4cxx::Logger::getLogger("ksn_poller");

	sender_ptr_ = NULL;

	InitKSNPoller(node);
}

void KSNPoller::Start(void)
{
	while(loop)
	{
		LOG4CXX_INFO(log_,"Starting...");
		std::list<boost::shared_ptr<Collector> >::iterator iter = 
			producers_ptr_.begin();
		for(;iter!=producers_ptr_.end();++iter)
		{
			(*iter)->open(0);
		}
		sender_ptr_->open(0);

		while(!reload)
		{
			boost::this_thread::sleep_for(boost::chrono::seconds(CHECK_TIME));
		}
		if(!loop)
			return;

		InitKSNPoller(node_);
	}

}

void KSNPoller::Clean()
{
	while(!producers_ptr_.empty())
	{
		producers_ptr_.front()->Exit();
		producers_ptr_.pop_front();
	}
	LOG4CXX_DEBUG(log_,"===== collector destoryed =====");
	if(sender_ptr_)
	{
		sender_ptr_->Exit();
		delete sender_ptr_;
		sender_ptr_ = NULL;
		LOG4CXX_DEBUG(log_,"===== sender destoryed =====");
	}
}
void KSNPoller::Stop()
{
	LOG4CXX_INFO(log_,"Stopping...");
	Clean();
	loop = false;
	reload = true;
}

void KSNPoller::InitKSNPoller(ENM::Node& node)
{
	DataSources::const_iterator iter = data_sources_.begin();
	sender_ptr_ = new Sender(t_channel_,grid_name_);
	for(;iter!=data_sources_.end();++iter)
	{
		boost::shared_ptr<Collector> co_ptr_(new Collector(iter->period,*iter,sender_ptr_));
		producers_ptr_.push_back(co_ptr_);
	}

	reload = false;
}

void KSNPoller::Reload()
{
	LOG4CXX_INFO(log_,"reloading...");

	reload = true;
}

void KSNPoller::TCPAcceptCallback(void)
{
	LOG4CXX_DEBUG(log_,"tcp accept callback");

	sender_ptr_->Reload();
}
}
