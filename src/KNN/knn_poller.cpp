/*************************************************************************
	> File Name: knn_poller.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月09日 星期四 16时59分53秒

 ************************************************************************/

#include "knn_poller.h"

namespace kelp
{
KNNPoller::KNNPoller(ENM::Node& node, ConfLoader& loader)
	:node_(node),loader_(loader),groups_(loader.GetCollectionGroups()),
	globals_(loader.GetGlobals()),us_channel_(loader.GetUDPSendChannel()),
	ur_channel_(loader.GetUDPRecvChannel()),cluster_name_(loader.GetClusterName()),
	tcp_port_(loader.GetTCPAcceptPort())
{
	log_ = log4cxx::Logger::getLogger("knn_poller");

	InitKNNPoller();
}

void KNNPoller::Start(void)
{
	while(loop)
	{
		LOG4CXX_INFO(log_,"starting...");
		std::list<boost::shared_ptr<DataCollector> >::iterator iter = producers_ptr_.begin();
		for(;iter!=producers_ptr_.end();++iter)
		{
			(*iter)->open(0);
		}
		sender_ptr_->open(0);
		c_receiver_->open(0);
		c_sender_->open(0);

		//check if need to restart
		while(!reload)
		{
			LOG4CXX_DEBUG(log_,"wait for next reload check point");
			boost::this_thread::sleep_for(boost::chrono::seconds(CHECK_TIME));
		}

		if(!loop)
			return ;

		LOG4CXX_INFO(log_,"reloading...");
		InitKNNPoller();
	}

	//sender_ptr_->wait();
	//c_receiver_->wait();
	//c_sender_->wait();
}

void KNNPoller::InitKNNPoller()
{
	//load config
	if(!globals_.mute)
		//not mute
		//collect the data from host
	{
		CollectionGroups::iterator iter = groups_.begin();
		int groups_size = groups_.size();
		int min_time = iter->time_threshold;

		sender_ptr_ = new DataSender(us_channel_);

		for(int g_s=0;g_s<groups_size;g_s++)
		{
			min_time = iter->time_threshold < min_time ? iter->time_threshold : min_time;
			//使用模块装载者装载模块
			module_loader_.InitModules((*iter).modules);

			//如果只收集一次，收集完后便擦除
			LOG4CXX_DEBUG(log_,iter->collection_once);
			if((*iter).collection_once)
			{
				module_loader_.CleanModules(iter->modules);
				if(iter!=groups_.end())
					iter = groups_.erase(iter);
				else
					groups_.pop_back();
				//groups_size --;
			}
			else
			{
				//注册数据收集者（采用ACE_Task实现的生产者）
				boost::shared_ptr<DataCollector> co_ptr(new DataCollector(iter->collection_every,iter->modules,sender_ptr_));
				producers_ptr_.push_back(co_ptr);

				++iter;
			}
		}
		//注册数据发送者(采用ACE_Task实现的消费者)
		sender_ptr_->set_time(min_time);
	}
	if(!globals_.deaf)
		//not deaf
		//collect the data from cluster
	{
		c_sender_ = new ClusterSender(tcp_port_,cluster_name_);
		c_receiver_ = new ClusterReceiver(ur_channel_,c_sender_);
	}

	reload = false;
}

void KNNPoller::Clean(void)
{
	if(sender_ptr_)
	{
		sender_ptr_->Exit();
		delete sender_ptr_;
		sender_ptr_ = NULL;
		LOG4CXX_DEBUG(log_,"==== host sender destroy ====");
	}
	if(!producers_ptr_.empty())
	{
		producers_ptr_.clear();
		LOG4CXX_DEBUG(log_,"==== host collector destroy ====");
	}
	if(c_sender_)
	{
		c_sender_->Exit();
		delete c_sender_;
		c_sender_ = NULL;
		LOG4CXX_DEBUG(log_,"==== cluster sender destroy ====");
	}
	if(c_receiver_)
	{
		c_receiver_->Exit();
		delete c_receiver_;
		c_receiver_ = NULL;
		LOG4CXX_DEBUG(log_,"==== cluster collector destroy ====");
	}
	CollectionGroups::iterator it=groups_.begin();
	for(int i=0;i<groups_.size();i++)
	{
		module_loader_.CleanModules(it->modules);
		++it;
		LOG4CXX_DEBUG(log_,"==== groups modules cleand ====");
	}
}

void KNNPoller::Stop(void)
{
	LOG4CXX_INFO(log_,"stopping...");
	Clean();
	loop = false;
	reload = true;
}

void KNNPoller::Reload(void)
{
	LOG4CXX_DEBUG(log_,"reload callback");

	reload = true;
}

void KNNPoller::UDPSendCallback(void)
{
	LOG4CXX_DEBUG(log_,"udp send channel callback");

	//call sender_ptr_ reload interface
	sender_ptr_->Reload();
}

void KNNPoller::UDPRecvCallback(void)
{
	LOG4CXX_DEBUG(log_,"udp recv channel callback");

	//call c_receiver_ reload interface
	c_receiver_->Reload();
}

void KNNPoller::TCPAcceptCallback(void)
{
	LOG4CXX_DEBUG(log_,"tcp accept callback");

	//call c_sender_ reload interface
	c_sender_->Reload();
}
};
