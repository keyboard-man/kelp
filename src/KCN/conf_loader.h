/*************************************************************************
	> File Name: conf_loader.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月23日 星期三 16时12分52秒
 ************************************************************************/

#ifndef KELP_KCN_CONF_LOADER_H_
#define KELP_KCN_CONF_LOADER_H_

#include <iostream>
#include <string>
#include <map>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/tokenizer.hpp>
#include <log4cxx/logger.h>
#include <node.h>

#include "kcn_poller.h"
#include "comm/config_data.h"

namespace kelp
{
class KCNPoller;
class ConfLoader
{
public:
	static ConfLoader& GetInstance(ENM::Node&);
	void LoadAll();
	bool Handle(const std::string, std::string, KCNPoller*);
	bool TopoHandle(const std::string, Coral::Action, KCNPoller*);

	DBModules& GetDBModules(void)
	{
		return db_modules_;
	}

	const Stores& GetStores(void) const
	{
		return stores_;
	}

	const DataSources& GetSources(void) const
	{
		return sources_;
	}

private:
	ConfLoader(ENM::Node&);

	void LoadDBModules(std::string);
	void LoadStores(std::string);
	void LoadSources(std::string);

	static boost::shared_ptr<ConfLoader> s_instance_;

	log4cxx::LoggerPtr log_;
	ENM::Node& node_;

	DBModules db_modules_;
	Stores stores_;
	DataSources sources_;

};
class InCluster
{
public:
	InCluster(std::string ip):ip_(ip)
	{
		;
	}
	bool operator()(NodeInfo info)
	{
		return (info.ip == ip_);
	}

private:
	std::string ip_;
};
}

#endif
