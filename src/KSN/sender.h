/*************************************************************************
	> File Name: sender.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 10时59分22秒
 ************************************************************************/

#ifndef KELP_KSN_SENDER_H_
#define KELP_KSN_SENDER_H_

#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Stream.h>
#include <sstream>
#include <string>
#include <log4cxx/logger.h>
#include <mongo/bson/bson.h>

#include "comm/config_data.h"

#define THR_NUM 1
#define T_SIZE 4*1024

namespace kelp
{
class Sender : public ACE_Task<ACE_MT_SYNCH>
{
public:
	Sender(const int&,const std::string&);
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
	mongo::BSONObj GridData();

	ACE_Message_Block* msg_;
	const int& channel_;
	const std::string& grid_name_;
	log4cxx::LoggerPtr log_;
	bool loop;
	ACE_INET_Addr ser_addr_;
	ACE_SOCK_Acceptor acceptor_;
	ACE_SOCK_Stream peer_;
	bool reload;
};
}

#endif
