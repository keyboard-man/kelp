/*************************************************************************
	> File Name: testmain.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月05日 星期三 09时00分11秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/logger.h>

#include "data_collector.h"
#include "data_sender.h"
#include "cluster_receiver.h"
#include "cluster_sender.h"
#include "reporter_manager.h"

int main()
{
	log4cxx::PropertyConfigurator::configure("log4cxx.conf");

	//kelp::UDPSendChannel us_channel;
	//us_channel.send_type = kelp::MCAST;
	//us_channel.ip = "239.0.0.1";
	//us_channel.port = 30033;
	//us_channel.ttl = 1;
	//
	//kelp::CollectionGroup group;
	//group.collection_once = false;
	//group.collection_every = 3;
	//group.time_threshold = 5;
	//group.last_collected = 0;
	//kelp::Metric metric;
	//metric.name = "testMetric";
	//metric.description = "this is test metric";
	//group.metrics.push_back(metric);
	//kelp::Module module;
	//module.name = "testModule";
	//module.enable = true;
	//module.path = "/home/vimer/Kelp/src/KNN/restruct/test.so";
	//module.argc = 0;
	//module.argv = NULL;
	//module.dl_handler = NULL;
	//module.init = NULL;
	//module.handler = NULL;
	//module.cleanup = NULL;
	//group.modules.push_back(module);

	//kelp::UDPRecvChannel ur_channel;
	//ur_channel.recv_type = kelp::MCAST;
	//ur_channel.mcast_join = "239.0.0.1";
	//ur_channel.port = 30033;

	//kelp::TCPAcceptChannel t_channel;
	//t_channel.port = 30034;

	//kelp::Cluster cluster;
	//cluster.name = "c1";
	//cluster.owner = "VIM";
	//cluster.url = "vim.ustc.edu.cn";

	//kelp::DataSender* ptr = new kelp::DataSender(us_channel);
	//kelp::DataCollector* d_coll = new kelp::DataCollector(group.collection_every,group.modules,ptr);
	//ptr->set_time(20);
	//kelp::ClusterSender* c_sen = new kelp::ClusterSender(t_channel,cluster.name);
	//kelp::ClusterReceiver* c_rec = new kelp::ClusterReceiver(300,ur_channel,c_sen);
	//std::cout << " ========  BEGIN  ======== " << std::endl; 
	//ptr->open(0);
	//d_coll->open(0);
	//c_sen->open(0);
	//c_rec->open(0);
	//boost::this_thread::sleep_for(boost::chrono::seconds(5));
	//std::cout << " ========   EXIT   ======== " << std::endl;
	//ptr->Exit();
	//d_coll->Exit();
	//c_sen->Exit();
	//c_rec->Exit();

	//boost::this_thread::sleep_for(boost::chrono::seconds(5));

	kelp::Reporter reporter("111.111.11.11","1-1-1-1");
	//kelp::ReporterClient client(&reporter,"111");
	//client.open(0);
	reporter.open(0);

	boost::this_thread::sleep_for(boost::chrono::seconds(5));
	//client.Exit();
	reporter.Exit();


	return 0;
}
