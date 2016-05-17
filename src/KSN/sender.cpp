/*************************************************************************
	> File Name: sender.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 11时06分59秒
 ************************************************************************/

#include "sender.h"

namespace kelp
{
Sender::Sender(const int& channel,const std::string& g_name)
	:channel_(channel),grid_name_(g_name),loop(true),reload(false)
{
	log_ = log4cxx::Logger::getLogger("ksn_sender");
}

int Sender::open(void*)
{
	ser_addr_.set(channel_);
	acceptor_.open(ser_addr_);

	activate(THR_NEW_LWP,THR_NUM);

	return 0;
}

int Sender::svc(void)
{
	char buf[T_SIZE] = { };
	const char * request = "request";
	while(loop)
	{
		if(reload)
		{
			acceptor_.close();

			ser_addr_.set(channel_);
			acceptor_.open(ser_addr_);

			reload = false;
		}

		ACE_Time_Value tv(1.5);
		ACE_INET_Addr* remote_addr;
		acceptor_.accept(peer_,remote_addr,&tv);
		peer_.recv(buf,T_SIZE);
		if(!strcmp(request,buf))
		{
			mongo::BSONObj temp = GridData();
			peer_.send(temp.objdata(),temp.objsize());
		}
		memset(buf,0,T_SIZE);
		peer_.close();
	}

	acceptor_.close();
	return 0;
}

int Sender::close(u_long)
{
	return 0;
}

void Sender::Exit()
{
	loop = false;
	peer_.close();
	acceptor_.close();
	msg_queue()->deactivate();
	thr_mgr()->cancel_all();
	wait();
}

mongo::BSONObj Sender::GridData()
{
	mongo::BSONObjBuilder grid_builder;
	mongo::BSONArrayBuilder a_builder;

	char ch[T_SIZE] = { };
	while(!msg_queue()->is_empty())
	{
		try
		{
			msg_ = 0;
			getq(msg_);
			if((!msg_) || (!msg_->rd_ptr()))
				throw "MESSAGE ERROR!!";
			memset(ch,0,T_SIZE);
			memcpy(ch,msg_->rd_ptr(),T_SIZE);
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
	grid_builder.append("grid_ID",grid_name_);
	grid_builder.appendArray("cluster_data",a_builder.arr());

	return grid_builder.obj();
}
}
