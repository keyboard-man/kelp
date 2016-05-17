/*************************************************************************
	> File Name: knn_poller.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月09日 星期四 16时57分51秒

 ************************************************************************/

#ifndef KELP_KNN_KNN_POLLER_H_
#define KELP_KNN_KNN_POLLER_H_

#include <string>
#include <list>

#include "log4cxx/logger.h"
#include "boost/thread.hpp"
#include "boost/smart_ptr.hpp"

#include "data_collector.h"
#include "data_sender.h"
#include "cluster_receiver.h"
#include "cluster_sender.h"
#include "modules_loader.h"
#include "conf_loader.h"

#include "comm/config_data.h"

#include "node.h"


#define CHECK_TIME 5
namespace kelp
{
class ConfLoader;
class KNNPoller
{
public:
	KNNPoller(ENM::Node & ,ConfLoader& loader);
	void Start(void);
	void Stop(void);
	void Clean(void);

	void Reload(void);
	void UDPSendCallback(void);
	void UDPRecvCallback(void);
	void TCPAcceptCallback(void);

	friend class ConfLoader;
private:
	void InitKNNPoller();

	log4cxx::LoggerPtr log_;
	std::list<boost::shared_ptr<DataCollector> > producers_ptr_;
	DataSender* sender_ptr_ = NULL;
	ClusterReceiver* c_receiver_ = NULL;
	ClusterSender* c_sender_ = NULL;
	bool reload = false;
	bool loop = true;

	ConfLoader& loader_;
	ModulesLoader module_loader_;
	ENM::Node& node_;
	CollectionGroups& groups_;
	const Globals& globals_;
	const UDPSendChannel& us_channel_;
	const UDPRecvChannel& ur_channel_;
	const std::string& cluster_name_;
	const int& tcp_port_;
};
}

#endif
