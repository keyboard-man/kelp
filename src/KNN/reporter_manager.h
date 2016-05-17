/*************************************************************************
	> File Name: reporter_manager.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月28日 星期一 16时34分05秒
 ************************************************************************/

#ifndef KELP_KNN_REPORTER_MANAGER_H_
#define KELP_KNN_REPORTER_MANAGER_H_

#include <string>
#include <cstring>
#include <list>
#include <log4cxx/logger.h>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <ace/OS.h>
#include <ace/SOCK_Connector.h>
#include "node.h"

#include "conf_loader.h"
#include "comm/config_data.h"

namespace kelp
{
class ConfLoader;
struct ReportRecord
{
	time_t time;
	char uuid[40];
	unsigned char level;
	char event[1024];
};

class Reporter : public ACE_Task<ACE_MT_SYNCH>
{
public:
	Reporter(std::string ip,std::string uuid,unsigned char level = 1);
	int open(void*);
	int svc(void);
	int close(u_long);
	void Exit();
	bool loop = true;

private:
	ACE_Message_Block* msg_;
	log4cxx::LoggerPtr log_;
	std::string kcn_ip_,uuid_;
	unsigned char level_;
	ACE_INET_Addr addr_;
	ACE_SOCK_Stream peer_;
	ACE_SOCK_Connector connector_;
	const int PORT = 30036;
};

class ReporterManager
{
public:
	ReporterManager(ENM::Node&, ConfLoader& loader);
	void Start(void);
	void Stop(void);
	void Clean(void);
	void Reload(void);

	friend class ConfLoader;
private:
	void Init();
	void GetFile();
	void LaunchReport();

	ENM::Node& node_;
	ConfLoader& loader_;
	log4cxx::LoggerPtr log_;
	std::list<std::string> file_list_;
	std::list<void *> handle_list_;
	std::list<void (*)(Reporter*)> launch_list_;
	Reporter* reporter_ptr_ = NULL;
	boost::filesystem::path path_;
	bool reload = false;
	bool loop = true;
	std::string kcn_uuid_ = "";
	std::string kcn_ip_ = "";
	const std::string g_launch_name = "Launch";
};
}

#endif
