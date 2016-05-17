/*************************************************************************
	> File Name: report_server.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月28日 星期一 09时27分38秒
 ************************************************************************/

#ifndef KELP_KCN_REPORT_SERVER_H_
#define KELP_KCN_REPORT_SERVER_H_

#include <ace/Svc_Handler.h>
#include <ace/Reactor.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Stream.h>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <log4cxx/logger.h>
#include <string>
#include <list>

namespace kelp
{
struct ReportRecord
{
	time_t time;
	char uuid[40];
	unsigned char level;
	char event[1024];
};

class ReportCache
{
public:
	static ReportCache& GetInstance(int size = 20);
	const std::list<ReportRecord>& GetCache() const
	{
		return records_;
	}
	bool Insert(time_t,const char*,unsigned char,const char*);
	bool Insert(ReportRecord);

private:
	ReportCache(int);

	int size_;
	log4cxx::LoggerPtr log_;
	static boost::shared_ptr<ReportCache> s_instance_;
	std::list<ReportRecord> records_;
};

class ServerHandler : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH> super;
public:
	ServerHandler();
	int open(void* =0);
	virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);

private:
	log4cxx::LoggerPtr log_;
};

class ReportServer
{
public:
	ReportServer();
	void Start();
	void Stop();
	void Reload();
	const std::list<ReportRecord>& GetCache() const
	{
		return cache_.GetCache();
	}

private:
	ReportCache& cache_;
	ACE_Acceptor<ServerHandler,ACE_SOCK_ACCEPTOR> server;

	log4cxx::LoggerPtr log_;
};
}

#endif
