/*************************************************************************
	> File Name: conf_loader.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月09日 星期三 16时44分10秒
 ************************************************************************/

#ifndef KELP_KNN_CONF_LOADER_H_
#define KELP_KNN_CONF_LOADER_H_

#include <iostream>
#include <map>
#include <string>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/tokenizer.hpp>
#include <log4cxx/logger.h>
#include <node.h>


#include "knn_poller.h"
#include "reporter_manager.h"
#include "comm/config_data.h"

namespace kelp
{
class KNNPoller;
class ConfLoader
{
public:
	static ConfLoader& GetInstance(ENM::Node&);
	void LoadAll();
	//bool RegiestCallback(std::string,callback_ptr);
	bool Handle(const std::string, std::string, void*);

	const Globals& GetGlobals() const
	{
		return globals_;
	}
	const std::string& GetIP() const 
	{
		return ip_;
	}
	const std::string& GetClusterName() const
	{
		return cluster_name_;
	}
	const UDPSendChannel& GetUDPSendChannel() const
	{
		return udp_send_channel_;
	}
	const UDPRecvChannel& GetUDPRecvChannel() const
	{
		return udp_recv_channel_;
	}
	const int& GetTCPAcceptPort() const 
	{
		return tcp_accept_port_;
	}
	CollectionGroups& GetCollectionGroups() 
	{
		return collection_groups_;
	}
	const std::string& GetReportModules()
	{
		return report_path_;
	}
	const std::string& GetQueryPath() const
	{
		return query_path_;
	}

private:
	ConfLoader(ENM::Node&);

	void LoadGlobal(ENM::Node&);
	void LoadCluster(ENM::Node&);
	void LoadGroups(ENM::Node&);

	void SetGlobal(std::string);
	void SetIP(std::string);
	void SetClusterName(std::string);
	void SetUDPSendChannel(std::string);
	void SetUDPRecvChannel(std::string);
	void SetTCPAcceptPort(std::string);
	void SetReportModules(std::string);
	void SetQueryPath(std::string);

	static boost::shared_ptr<ConfLoader> s_instance_;

	log4cxx::LoggerPtr log_;
	ENM::Node& node_;

	//knn global infomation
	Globals globals_;
	std::string ip_;
	//cluster infomation
	std::string cluster_name_;
	UDPSendChannel udp_send_channel_;
	UDPRecvChannel udp_recv_channel_;
	int tcp_accept_port_;
	//collection metric infomation
	CollectionGroups collection_groups_;
	//report modules infomation
	std::string report_path_;
	//query infomation
	std::string query_path_;
};
};

#endif
