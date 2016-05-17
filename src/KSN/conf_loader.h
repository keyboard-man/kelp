/*************************************************************************
	> File Name: conf_loader.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月23日 星期三 16时17分52秒
 ************************************************************************/

#ifndef KELP_KSN_CONF_LOADER_H_
#define KELP_KSN_CONF_LOADER_H_

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/tokenizer.hpp>
#include <log4cxx/logger.h>
#include <node.h>

#include "ksn_poller.h"
#include "comm/config_data.h"

namespace kelp
{
class KSNPoller;
class ConfLoader
{
public:
	static ConfLoader& GetInstance(ENM::Node&);
	void LoadAll();
	//This function is for config change
	bool Handle(const std::string, std::string,KSNPoller*);
	//This function is for topo change
	void TopoHandle(const std::string, Coral::Action,KSNPoller*);
	const DataSources& GetDataSource(void) const
	{
		//inline
		return source_;
	}
	const int& GetTCPAcceptPort(void) const
	{
		//inline
		return tcp_accept_port_;
	}
	const std::string& GetGridName(void) const
	{
		//inline
		return grid_name_;
	}

private:
	ConfLoader(ENM::Node&);

	void LoadSource(ENM::Node&);
	void LoadComm(ENM::Node&);
	void SetTCPAcceptPort(std::string);

	static boost::shared_ptr<ConfLoader> s_instance_;

	log4cxx::LoggerPtr log_;
	ENM::Node& node_;

	DataSources source_;
	int tcp_accept_port_;
	std::string grid_name_;
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
