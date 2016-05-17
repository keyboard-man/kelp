/*************************************************************************
	> File Name: cluster_sender.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月31日 星期五 16时07分34秒
 ************************************************************************/

#include "cluster_sender.h"

namespace kelp
{
ClusterSender::ClusterSender(const int& channel,const std::string& c_name)
	:tcp_channel_(channel),cluster_name_(c_name),loop(true),reload(false)
{
	log_ = log4cxx::Logger::getLogger("cluster_sender");
}

int ClusterSender::open(void*)
{
	ser_addr_.set(tcp_channel_);
	acceptor_.open(ser_addr_);

	activate(THR_NEW_LWP,THR_NUM);

	return 0;
}

int ClusterSender::svc(void)
{
	char buf[T_SIZE] = { };
	const char *request = "request";
	while(loop)
	{
		if(reload)
		{
			acceptor_.close();

			ser_addr_.set(tcp_channel_);
			acceptor_.open(ser_addr_);

			reload = false;
		}
		ACE_Addr* remote_addr = NULL;
		ACE_Time_Value tv(1.5);
		acceptor_.accept(peer_,remote_addr,&tv);
		memset(buf,0,T_SIZE);
		peer_.recv(buf,T_SIZE);
		if(!strcmp(request,buf))
		{
			mongo::BSONObj temp = ClusterData();
			peer_.send(temp.objdata(),temp.objsize());
		}
		peer_.close();
	}
	acceptor_.close();

	return 0;
}

int ClusterSender::close(u_long)
{
	return 0;
}

void ClusterSender::Exit()
{
	loop = false;
	peer_.close();
	acceptor_.close();
	msg_queue()->deactivate();
	thr_mgr()->cancel_all();
	wait();
}

void ClusterSender::Put(ACE_Message_Block* blk)
{
	std::ostringstream oss;
	oss << "add message into queue!" << std::endl;
	LOG4CXX_INFO(log_,oss.str());

	if(msg_queue()->is_full())
	{
		msg_ = 0;
		getq(msg_);
		delete [] msg_->rd_ptr();
		delete msg_;
	}

	putq(blk);

}

mongo::BSONObj ClusterSender::ClusterData()
{
	mongo::BSONObjBuilder cluster_builder;
	mongo::BSONArrayBuilder a_builder;

	char ch[U_SIZE] = { };
	while(!msg_queue()->is_empty())
	{
		try
		{
			msg_ = 0;
			getq(msg_);
			if((!msg_) || (!msg_->rd_ptr()))
				throw "MESSAGE ERROR!!";
			memset(ch,0,U_SIZE);
			memcpy(ch,msg_->rd_ptr(),msg_->size());
			if(*ch)
			{
				mongo::BSONObj bson(ch);

				a_builder.append(bson);
			}

			delete [] msg_->rd_ptr();
			//msg_->release();
			delete msg_;
		}
		catch(const char* ch)
		{
			LOG4CXX_ERROR(log_,ch);
		}
	}
	cluster_builder.append("cluster_ID",cluster_name_);
	cluster_builder.appendArray("host_data",a_builder.arr());

	return cluster_builder.obj();
}
}
