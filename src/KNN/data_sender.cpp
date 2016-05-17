/*************************************************************************
	> File Name: data_sender.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月30日 星期四 16时02分54秒
 ************************************************************************/

#include "data_sender.h"

namespace kelp
{
DataSender::DataSender(int time,const UDPSendChannel& channel)
	:time_(time),send_channel_(channel),host_name_(HostName())
{
	log_ = log4cxx::Logger::getLogger("data_sender");
	InitChannel();
}

DataSender::DataSender(const UDPSendChannel& channel)
	:send_channel_(channel),host_name_(HostName())
{
	log_ = log4cxx::Logger::getLogger("data_sender");
	InitChannel();
}

int DataSender::open(void*)
{
	activate(THR_NEW_LWP,THR_NUM);

	return 0;
}

int DataSender::svc(void)
{
	timer_ = new AsyncTimer(ios_,time_,boost::bind(&DataSender::Send,this));

	ios_.run();

	return 0;
}

int DataSender::close(u_long)
{
	return 0;
}

void DataSender::Put(ACE_Message_Block* blk)
{
	if(msg_queue()->is_full())
	{
		msg_ = 0;
		getq(msg_);
		kelp::MetaData* metadata = (kelp::MetaData*)msg_->rd_ptr();
		delete [] metadata->buf;
		delete msg_->rd_ptr();
		delete msg_;
	}

	putq(blk);
}

void DataSender::Exit()
{
	timer_->Cancel();
	delete timer_;
	ios_.stop();
	msg_queue()->deactivate();
	thr_mgr()->cancel_all();

	switch(send_type_)
	{
		case MCAST:
			mcast_.leave(addr_);
			mcast_.close();
			break;
		case UCAST:
			ucast_.close();
	}

	wait();
}

void DataSender::Send()
{
	//send the data in the message queue
	//to udp channel
	std::vector<mongo::BSONElement> ele;
	mongo::BSONObj bson_obj;

	//reload check
	if(reload)
	{
		//exit origin send channel
		switch(send_type_)
		{
			case MCAST:
				mcast_.leave(addr_);
				mcast_.close();
				break;
			case UCAST:
				ucast_.close();
		}

		//join new send channel
		InitChannel();

		reload = false;
	}

	while(!msg_queue()->is_empty())
	{
		std::ostringstream oss;
		oss << "deal with the message queue" << std::endl;
		LOG4CXX_DEBUG(log_,oss.str());

		try
		{
			//get the data from message queue
			msg_ = 0;
			getq(msg_);
			if((!msg_) || (!msg_->rd_ptr()))
				throw "MESSAGE IS EMPTY!!";
			kelp::MetaData* metadata = (kelp::MetaData*)msg_->rd_ptr();
			//handle the metadata
			mongo::BSONObjBuilder builder;
			mongo::BSONObj bson_temp = metadata->bson;
			bson_temp.elems(ele);
			builder.append("host_ID",host_name_);
			builder.append("heartbeat",(long long)metadata->time);
			for(int i=0;i<ele.size();i++)
				builder.append(ele[i]);
			bson_obj = builder.obj();
			builder.abandon();
			ele.clear();

			//send data to udp channel
			switch(send_type_)
			{
				case MCAST:
					mcast_.send(bson_obj.objdata(),bson_obj.objsize());
					break;
				case UCAST:
					ucast_.send(bson_obj.objdata(),bson_obj.objsize(),addr_);
			}

			//free the resource
			delete [] metadata->buf;
			delete metadata;
			//msg_->release();
			delete msg_;
		}
		catch(const char* ch)
		{
			LOG4CXX_ERROR(log_,ch);
		}
	}
}

std::string DataSender::HostName(void)
{
	char name[65] = { };
	gethostname(name,sizeof(name));
	std::string result(name);

	//replace - .
	boost::algorithm::replace_all(result,"-","_");
	boost::algorithm::replace_all(result,".","_");
	
	return result;
}

void DataSender::InitChannel()
{
	send_type_ = send_channel_.send_type;
	switch(send_type_)
	{
		case MCAST:
			{
				//init mcase
				addr_.set(send_channel_.port,send_channel_.ip.c_str());
				mcast_.open(addr_);
				mcast_.join(addr_);
				std::stringstream ss;
				ss << "Send to==> " << addr_.get_host_addr() << ":" << addr_.get_port_number();
				LOG4CXX_INFO(log_,ss.str());
			}
			break;
		case UCAST:
			{
				//init ucast
				addr_.set(send_channel_.port,send_channel_.ip.c_str());
				ucast_.open(local_addr_);
				std::stringstream ss;
				ss << "Send to==> " << addr_.get_host_addr() << ":" << addr_.get_port_number();
				LOG4CXX_INFO(log_,ss.str());
			}
	}
}
}
