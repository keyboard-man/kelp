/*************************************************************************
	> File Name: cluster_receiver.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月31日 星期五 15时38分43秒
 ************************************************************************/

#include "cluster_receiver.h"

namespace kelp
{
ClusterReceiver::ClusterReceiver(const UDPRecvChannel& channel,ClusterSender* sender)
	:udp_channel_(channel),sender_(sender),loop(true),reload(false)
{
	log_ = log4cxx::Logger::getLogger("cluster_receiver");
}

int ClusterReceiver::open(void*)
{
	InitChannel();
	activate(THR_NEW_LWP,THR_NUM);

	return 0;
}

int ClusterReceiver::svc(void)
{
	char buf[U_SIZE] = { };

	while(loop)
	{
		memset(buf,0,U_SIZE);
		ACE_INET_Addr remote_addr;
		int rece_size = 0;
		ACE_Time_Value tv(1.5);
		//check reload
		if(reload)
		{
			//close orign channel
			switch(recv_type_)
			{
				case MCAST:
					mcast_.leave(addr_);
					mcast_.close();
					addr_.dump();
					break;
				case UCAST:
					ucast_.close();
			}

			//join new channel
			InitChannel();

			reload = false;
		}

		switch(recv_type_)
		{
			case MCAST:
				{
					rece_size = mcast_.recv((void*)buf,U_SIZE,remote_addr,0,&tv);
				}
				break;
			case UCAST:
				{
					rece_size = ucast_.recv((void*)buf,U_SIZE,remote_addr,0,&tv);
				}
				break;
		}
		if(rece_size && (*buf))
		{
			mongo::BSONObj temp((char*)buf);
			std::cout << temp << std::endl;
			std::vector<mongo::BSONElement> ele;
			temp.elems(ele);

			if(ele.size()<3)
			{
				LOG4CXX_WARN(log_,"Too little BSONObj fields");
			}
			else if(!temp.hasField("host_ID") || !temp.hasField("heartbeat"))
			{
				LOG4CXX_WARN(log_,"This BSONObj do not hace necessary fields!");
			}
			else
			{
				char* ch = new char[temp.objsize()];
				memcpy(ch,buf,temp.objsize());
				msg_ = new ACE_Message_Block(ch,temp.objsize());
				sender_->Put(msg_);
			}
		}
	}

	return 0;
}

int ClusterReceiver::close(u_long)
{

	return 0;
}

void ClusterReceiver::Exit()
{
	loop = false;
	switch(recv_type_)
	{
		case MCAST:
			mcast_.leave(addr_);
			mcast_.close();
			break;
		case UCAST:
			ucast_.close();
	}
	
	thr_mgr()->cancel_all();
	wait();
}

void ClusterReceiver::InitChannel(void)
{
	recv_type_ = udp_channel_.recv_type;
	switch(recv_type_)
	{
		case MCAST:
			{
				addr_.set(udp_channel_.port,udp_channel_.mcast_join.c_str());
				mcast_.open(addr_);
				mcast_.join(addr_);
				std::stringstream ss;
				ss << "recv from <== " << addr_.get_host_addr() << ":" << addr_.get_port_number();
				LOG4CXX_INFO(log_,ss.str());
			}
			break;
		case UCAST:
			{
				addr_.set(udp_channel_.port);
				ucast_.open(addr_);
				std::stringstream ss;
				ss << "recv from <== " << addr_.get_host_addr() << ":" << addr_.get_port_number();
				LOG4CXX_INFO(log_,ss.str());
			}
	}
}
}
