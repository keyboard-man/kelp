/*************************************************************************
	> File Name: kcn_poller.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月03日 星期一 09时03分56秒
 ************************************************************************/

#include "kcn_poller.h"

namespace kelp
{
KCNPoller::KCNPoller(ENM::Node& node,ConfLoader& loader)
	:node_(node),conf_loader_(loader),stores_(loader.GetStores()),
	modules_(loader.GetDBModules()),sources_(loader.GetSources())
{
	log_ = log4cxx::Logger::getLogger("kcn_poller");

	InitKCNPoller(node);
}

void KCNPoller::Start(void)
{
	while(loop)
	{
		LOG4CXX_DEBUG(log_,"starting...");
		std::list<boost::shared_ptr<Collector> >::iterator it = col_list_.begin();
		for(;it!=col_list_.end();++it)
		{
			(*it)->open(0);
		}

		processer_->open(0);

		while(!reload)
		{
			boost::this_thread::sleep_for(boost::chrono::seconds(CHECK_TIME));
		}
		if(!loop)
			return;

		InitKCNPoller(node_);
	}

//	processer_->wait();
}

void KCNPoller::Clean(void)
{
	while(!col_list_.empty())
	{
		col_list_.front()->Exit();
		col_list_.pop_front();
	}
	LOG4CXX_DEBUG(log_,"===== collectors destroyed =====");

	if(processer_)
	{
		processer_->Exit();
		delete processer_;
		processer_ = NULL;
		LOG4CXX_DEBUG(log_,"===== processer destroyed =====");
	}
}

void KCNPoller::Stop(void)
{
	LOG4CXX_DEBUG(log_,"stopping...");
	reload = true;
	loop = false;
	Clean();
	LOG4CXX_INFO(log_,"kcn poller stopped safely");
}

void KCNPoller::InitKCNPoller(ENM::Node& node)
{
	processer_ = new Processer(stores_,modules_);

	DataSources::const_iterator it = sources_.begin();
	for(;it!=sources_.end();++it)
	{
		boost::shared_ptr<Collector> temp(new Collector(it->period,*it,processer_));
		col_list_.push_back(temp);
	}

	reload = false;
}

void KCNPoller::Reload(void)
{
	LOG4CXX_DEBUG(log_,"reloading ...");

	reload = true;
}
}
