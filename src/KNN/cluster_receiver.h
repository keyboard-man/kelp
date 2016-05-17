/*************************************************************************
	> File Name: cluster_receiver.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月31日 星期五 15时25分50秒
 ************************************************************************/

#ifndef KELP_KNN_CLUSTER_RECEIVER_H_
#define KELP_KNN_CLUSTER_RECEIVER_H_

#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Dgram.h>
#include <ace/SOCK_Dgram_Mcast.h>
#include <boost/smart_ptr.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <log4cxx/logger.h>
#include <mongo/bson/bson.h>

#include "comm/async_timer.h"
#include "comm/config_data.h"
#include "cluster_sender.h"

#define THR_NUM 1
#define U_SIZE 4*1024

namespace kelp
{
class ClusterReceiver : public ACE_Task<ACE_MT_SYNCH>
{
public:
	ClusterReceiver(const UDPRecvChannel&,ClusterSender* sender);
	int open(void*);
	int svc(void);
	int close(u_long);
	void Exit();
	void Reload(void)
	{
		//inline
		reload = true;
	}

private:
	void InitChannel(void);
	ACE_Message_Block* msg_;
	ClusterSender* sender_;
	const UDPRecvChannel& udp_channel_;
	CastType recv_type_;
	ACE_INET_Addr addr_;
	ACE_SOCK_Dgram_Mcast mcast_;
	ACE_SOCK_Dgram ucast_;
	log4cxx::LoggerPtr log_;
	bool loop;
	bool reload;
};
}
#endif
