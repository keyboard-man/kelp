/*************************************************************************
	> File Name: cluster_sender.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月31日 星期五 16时00分03秒
 ************************************************************************/

#ifndef KELP_KNN_CLUSTER_SENDER_H_
#define KELP_KNN_CLUSTER_SENDER_H_

#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Stream.h>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <log4cxx/logger.h>
#include <list>
#include <string>

#include "comm/config_data.h"

#define THR_NUM 1
#define T_SIZE 32
#define U_SIZE 4*1024

namespace kelp
{
class ClusterSender : public ACE_Task<ACE_MT_SYNCH>
{
public:
	ClusterSender(const int&,const std::string&);
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
	mongo::BSONObj ClusterData();

	ACE_Message_Block* msg_;
	const int& tcp_channel_;
	ACE_INET_Addr ser_addr_;
	ACE_SOCK_Acceptor acceptor_;
	ACE_SOCK_Stream peer_;
	log4cxx::LoggerPtr log_;
	const std::string& cluster_name_;
	bool loop;
	bool reload;
};
}
#endif
