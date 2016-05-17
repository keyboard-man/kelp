/*************************************************************************
	> File Name: ksn_poller.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 11时32分11秒
 ************************************************************************/

#ifndef KELP_KSN_KSN_POLLER_H_
#define KELP_KSN_KSN_POLLER_H_

#include <string>
#include <list>

#include <log4cxx/logger.h>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

#include "collector.h"
#include "sender.h"
#include "conf_loader.h"

#include "comm/config_data.h"

#include "node.h"

#define CHECK_TIME 5
namespace kelp
{
class ConfLoader;
class KSNPoller
{
public:
	KSNPoller(ENM::Node &,ConfLoader&);
	void Start(void);
	void Stop(void);
	void Clean(void);

	friend class ConfLoader;
private:
	void InitKSNPoller(ENM::Node&);
	void Reload(void);
	void TCPAcceptCallback(void);

	log4cxx::LoggerPtr log_;
	std::list<boost::shared_ptr<Collector> > producers_ptr_;
	Sender* sender_ptr_;
	bool reload = false;
	bool loop = true;

	ENM::Node& node_;
	ConfLoader& conf_loader_;

	const int& t_channel_;
	const DataSources& data_sources_;
	const std::string& grid_name_;
};
}

#endif
