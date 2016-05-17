/*************************************************************************
	> File Name: data_collector.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月30日 星期四 14时55分24秒
 ************************************************************************/

#ifndef KELP_KNN_DATA_COLLECTOR_H_
#define KELP_KNN_DATA_COLLECTOR_H_

#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <ace/OS.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <log4cxx/logger.h>
#include <mongo/bson/bson.h>

#include "comm/async_timer.h"
#include "comm/config_data.h"
#include "data_sender.h"

#define THR_NUM 1

namespace kelp
{
class DataCollector : public ACE_Task<ACE_MT_SYNCH>
{
public:
	DataCollector(int,const Modules&,DataSender* sender);
	int open(void*);
	int svc(void);
	int close(u_long);
	void Exit();

private:
	void Collect();

	ACE_Message_Block* msg_;
	AsyncTimer* timer_;
	DataSender* sender_;
	boost::asio::io_service ios_;
	int time_;
	const Modules& modules_;
	log4cxx::LoggerPtr log_;
};
}

#endif
