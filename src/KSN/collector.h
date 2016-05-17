/*************************************************************************
	> File Name: collector.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 10时10分44秒
 ************************************************************************/

#ifndef KELP_KSN_COLLECTOR_H_
#define KELP_KSN_COLLECTOR_H_

#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <ace/OS.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <sstream>
#include <string>
#include <log4cxx/logger.h>
#include <mongo/bson/bson.h>

#include "comm/async_timer.h"
#include "comm/config_data.h"
#include "sender.h"

#define THR_NUM 1
#define T_SIZE 4*1024

namespace kelp
{
class Collector : public ACE_Task<ACE_MT_SYNCH>
{
public:
	Collector(int,const DataSource&,Sender*);
	int open(void*);
	int svc(void);
	int close(u_long);
	void Exit();

private:
	void PollData();
	bool TryToConnect(ACE_SOCK_Connector&,ACE_SOCK_Stream&);

	ACE_Message_Block* msg_;
	boost::asio::io_service ios_;
	Sender* sender_;
	const DataSource& data_source_;
	log4cxx::LoggerPtr log_;
	int time_;
	AsyncTimer* timer_;

};
}

#endif
