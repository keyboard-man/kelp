/*************************************************************************
	> File Name: data_sender.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月30日 星期四 15时56分44秒
 ************************************************************************/

#ifndef KELP_KNN_DATA_SENDER_H_
#define KELP_KNN_DATA_SENDER_H_

#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Dgram.h>
#include <ace/SOCK_Dgram_Mcast.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <vector>
#include <log4cxx/logger.h>
#include <boost/algorithm/string/replace.hpp>
#include <mongo/bson/bson.h>

#include "comm/async_timer.h"
#include "comm/config_data.h"

#define THR_NUM 1

namespace kelp
{
class DataSender : public ACE_Task<ACE_MT_SYNCH>
{
public:
	DataSender(int,const UDPSendChannel&);
	DataSender(const UDPSendChannel&);
	void set_time(int time)
	{
		//inline
		time_ = time;
	}
	int open(void*);
	int svc(void);
	int close(u_long);
	void Put(ACE_Message_Block*);
	void Exit();
	void Reload(void)
	{
		//inline
		reload = true;
	}

private:
	void Send();
	std::string HostName();
	void InitChannel();

	ACE_Message_Block* msg_;
	AsyncTimer* timer_;
	boost::asio::io_service ios_;
	int time_;
	log4cxx::LoggerPtr log_;
	const UDPSendChannel& send_channel_;
	CastType send_type_;
	ACE_INET_Addr addr_;
	ACE_INET_Addr local_addr_;
	ACE_SOCK_Dgram_Mcast mcast_;
	ACE_SOCK_Dgram ucast_;
	bool reload = false;
	const std::string host_name_;
};
}

#endif
