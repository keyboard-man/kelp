/*************************************************************************
	> File Name: data_collector.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月30日 星期四 15时12分11秒
 ************************************************************************/

#include "data_collector.h"

namespace kelp
{
DataCollector::DataCollector(int time,const Modules& mod,DataSender* sender)
	:time_(time),modules_(mod),sender_(sender)
{
	log_ = log4cxx::Logger::getLogger("data_collector");
}

int DataCollector::open(void *)
{
	activate(THR_NEW_LWP,THR_NUM);

	return 0;
}

int DataCollector::svc(void)
{
	timer_ = new AsyncTimer(ios_,time_,boost::bind(&DataCollector::Collect,this));

	ios_.run();
	return 0;
}

int DataCollector::close(u_long)
{
	timer_->Cancel();
	delete timer_;

	return 0;
}

void DataCollector::Exit()
{
	ios_.stop();
	thr_mgr()->cancel_all();
	wait();
}

void DataCollector::Collect()
{
	//call the handler function in Modules
	//to collect the real data
	int size = 0;
	char* buf = NULL;
	Modules::const_iterator iter = modules_.begin();
	for(;iter!=modules_.end();++iter)
	{
		if(iter->handler)
		{
			std::ostringstream oss;
			oss << "collect from: " << iter->name << std::endl;
			LOG4CXX_INFO(log_,oss.str());

			iter->handler(&buf,size);

			kelp::MetaData* metadata = new kelp::MetaData();
			metadata->buf = new char[size]();
			memcpy(metadata->buf,buf,size);
			metadata->size = size;
			metadata->bson = mongo::BSONObj(metadata->buf);

			//change the MetaData 
			//this is added
			metadata->time = time(NULL);

			//put into sender's message queue
			msg_ = new ACE_Message_Block((char *)metadata,sizeof(*metadata));
			sender_->Put(msg_);

			if(buf)
			{
				delete [] buf;
				buf = NULL;
			}
		}
		else
		{
			std::ostringstream oss;
			oss << "The handler of " << iter->name << " is NULL" << std::endl;
			LOG4CXX_WARN(log_,oss.str());
		}
	}
}
}
