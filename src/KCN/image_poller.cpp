/*************************************************************************
	> File Name: image_poller.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月03日 星期一 17时38分14秒
 ************************************************************************/

#include "image_poller.h"

namespace kelp
{
ImagePoller::ImagePoller(ENM::Node& node)
	:node_(node),conf_loader_(node)
{
	log_ = log4cxx::Logger::getLogger("image_poller");

	InitialPoller(node);
}

void ImagePoller::Start()
{
	LOG4CXX_DEBUG(log_,"starting...");

	ios_.run();
}

void ImagePoller::Stop()
{
	LOG4CXX_DEBUG(log_,"stopping...");

	timer_->Cancel();
	delete timer_;
	ios_.stop();
}

void ImagePoller::Reload()
{
	LOG4CXX_DEBUG(log_,"reloading...");

	Stop();
	InitialPoller(node_);
	Start();
}

void ImagePoller::InitialPoller(ENM::Node& node)
{
	//time_ = conf_loader_.LoadImageTime();
	//path_ = conf_loader_.LoadImagePath();
	
	//for test
	time_ = 30;
	path_ = "/home/vimer/image/";

	timer_ = new AsyncTimer(ios_,time_,boost::bind(&ImagePoller::Collect,this));

	CGN::USNTopoMap topo;
	std::list<std::string> t_list;
	std::map<std::string,bool> recode;
	CGN::UUIDs uuids = node.getAllUSN();

	//initial map
	for(int i=0;i<uuids.size();i++)
	{
		recode[uuids[i]] = false;
	}

	//initial list
	t_list.push_back(node.selfUUID());

	std::string uuid;
	while(!t_list.empty())
	{
		//pop from the queue
		uuid = t_list.front();
		t_list.pop_front();

		//check if loops exist
		if(recode[uuid])
		{
			continue;
		}
		else
		{
			recode[uuid] = true;
			topo = node.getRelation(uuid);
			if(topo[Coral::next].size()==0)
			{
				//find leaf node
				node_list_.push_back(uuid);
			}
			else
			{
				//middle node
				//push son node into queue
				for(int i=0;i<topo[Coral::next].size();i++)
					t_list.push_back(topo[Coral::next][i]);
			}
		}
	}
}

void ImagePoller::Collect()
{
	//collect image file just from leaf nodes!!
	ImageCollectorPrx collector;
	ImageData data;
	char* ptr = NULL;
	for(std::list<std::string>::iterator it=node_list_.begin();
			it!=node_list_.end();++it)
	{
		collector = node_.service()->
			getServiceProxy<ImageCollectorPrx>(*it,"image");
		data = collector->GetImage(path_);

		//insert into mongoDB
		ptr = (char *)data.data.data();
		mongo::BSONObj bson(ptr);
	}
}
}
