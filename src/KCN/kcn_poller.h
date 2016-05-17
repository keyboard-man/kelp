/*************************************************************************
	> File Name: kcn_poller.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月03日 星期一 08时58分46秒
 ************************************************************************/

#ifndef KELP_KCN_KCN_POLLER_H_
#define KELP_KCN_KCN_POLLER_H_

#include <string>
#include <list>
#include <log4cxx/logger.h>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

#include "collector.h"
#include "processer.h"
#include "conf_loader.h"

#include "comm/config_data.h"

#include "node.h"

namespace kelp
{
const int CHECK_TIME = 5;
class ConfLoader;
class KCNPoller
{
public:
	KCNPoller(ENM::Node&,ConfLoader&);
	void Start(void);
	void Clean(void);
	void Stop(void);

	friend class ConfLoader;
private:
	void InitKCNPoller(ENM::Node&);
	void Reload(void);

	log4cxx::LoggerPtr log_;
	std::list<boost::shared_ptr<Collector> > col_list_;
	Processer* processer_ = NULL;
	bool reload = false;
	bool loop = true;
	
	ENM::Node& node_;
	ConfLoader& conf_loader_;
	
	const Stores& stores_;
	DBModules& modules_;
	const DataSources& sources_;
};
}

#endif
