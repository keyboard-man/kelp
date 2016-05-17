/*************************************************************************
	> File Name: testmain.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 20时16分38秒
 ************************************************************************/

#include <iostream>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/logger.h>
#include <boost/thread.hpp>
#include "processer.h"
#include "collector.h"

int main()
{
	log4cxx::PropertyConfigurator::configure("log4cxx.conf");
	kelp::Stores stores;
	kelp::Store store;
	kelp::DBModules modules;
	kelp::DBModule module;
	kelp::DataSources dss;
	kelp::DataSource ds;
	store.key_name = "testModule";
	store.module_name.push_back("MongoDB");
	stores.push_back(store);
	module.module_name = "MongoDB";
	module.enable = true;
	module.argc = 1;
	char* buf = "kelp";
	module.argv = &buf;
	module.path = "/home/vimer/Kelp/src/KCN/restruct/mongo.so";
	module.dl_handler = NULL;
	module.init = NULL;
	module.handler = NULL;
	module.cleanup = NULL;
	modules.push_back(module);
	ds.name = "c1";
	ds.period = 10;
	ds.node_list.push_back("127.0.0.1");
	dss.push_back(ds);

	kelp::Processer* pro = new kelp::Processer(stores,modules);
	pro->open(0);
	std::cout << "processer started" << std::endl;

	mongo::BSONObj obj;
	mongo::BSONArrayBuilder a_builder;

	obj = BSON("host_ID"<<"vimer"<<"heartbeat"<<1438396746<<"testModule"<<84);
	a_builder.append(obj);
	obj = BSON("host_ID"<<"vimer"<<"heartbeat"<<1438396751<<"testModule"<<87);
	a_builder.append(obj);
	obj = BSON("host_ID"<<"vimer"<<"heartbeat"<<1438396756<<"testModule"<<78);
	a_builder.append(obj);
	obj = BSON("host_ID"<<"vimer"<<"heartbeat"<<1438396761<<"testModule"<<16);
	a_builder.append(obj);

	obj = BSON("cluster_ID"<<"c1"<<"host_data"<<a_builder.arr());
	std::cout << obj << std::endl;

	pro->Handle(obj);
	
	kelp::Collector* col = new kelp::Collector(ds.period,ds,pro);
	col->open(0);
	std::cout << "collector started" << std::endl;

	boost::this_thread::sleep_for(boost::chrono::seconds(1));
	//pro->loop = false;
	//pro->msg_queue()->deactivate();
	//pro->wait();
	pro->Exit();
	delete pro;
	std::cout << "processer stopped" << std::endl;

	//col->close(0);
	col->Exit();
	delete col;
	std::cout << "collector stopped" << std::endl;

	return 0;
}
