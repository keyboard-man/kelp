/*************************************************************************
	> File Name: knn.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月30日 星期四 19时29分29秒
 ************************************************************************/

#include <iostream>
#include <exception>
#include <cstdlib>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/logger.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <node.h>

#include "knn_poller.h"
#include "conf_loader.h"
#include "query_service.h"
#include "reporter_manager.h"

#define CGNPORT 10003
#define SERPORT 12346
#define LOG_PATH "conf/log4cxx.conf"

std::map<std::string,std::string> g_config;
CGN::USNTopoMap g_topo;
kelp::KNNPoller* g_poller;
kelp::ReporterManager* g_reporter;
kelp::ConfLoader* g_loader;
Ice::CommunicatorPtr g_ic;

class ConfigCallBackI : public ENM::ConfigCallBack
{
public:
	virtual void invoke(const std::string& key,const std::string& value, const Ice::Current&)
	{
		std::cout << "Config Changed : " << key << " -> " << value << std::endl;

		std::string c_value = value;
		try 
		{
			if(key == "report_modules")
				g_loader->Handle(key,c_value,g_reporter);
			else
				g_loader->Handle(key,c_value,g_poller);
		} 
		catch(const char* msg)
		{
			std::cout << msg << std::endl;
			return;
		}
		catch (...) {
			std::cout << "UNKONW EXCEPTION!!!" << std::endl;
			return;
		}
		std::cout << "ConfigCallBackI::invoke function is finished!!!!!" << std::endl;
	}
};

class TopoCallBackI : public ENM::TopoCallBack
{
public:
	virtual void invoke(Coral::Relation rel, const std::string& UUID,
						Coral::Action act, const Ice::Current&)
	{
		std::cout << "Topology changed ";
		if(rel==Coral::prev)
			std::cout << "parent";
		else if(rel==Coral::next)
			std::cout << "son";
		else
			std::cout << "neighbor";

		std::cout << ' ';

		if(act==Coral::add)
			std::cout << "add";
		else
			std::cout << "del";

		std::cout << ' ' << UUID << std::endl;
	}
};

void sig_int(int num)
{
	std::cout << "\n press CTRL + C, now the program will exit!" << std::endl;

	g_poller->Stop();
	g_reporter->Stop();

	if(g_ic)
		g_ic->shutdown();
}

int main(int argc,char** argv)
{
	log4cxx::PropertyConfigurator::configure(LOG_PATH);
	Ice::CommunicatorPtr ic = Ice::initialize(argc,argv);
	g_ic = ic;
	ENM::Node knn("KNN1",ic,"./knn.uuid",CGNPORT,SERPORT,"KNN Node");
	ENM::ConfigCallBackPtr configCB = new ConfigCallBackI;
	ENM::TopoCallBackPtr topoCB = new TopoCallBackI;
	std::cout << "do register!" << std::endl;
	knn.doRegister(configCB,topoCB);

	signal(SIGINT,sig_int);

	try
	{
		//get knn node configure infomation
		kelp::ConfLoader loader = kelp::ConfLoader::GetInstance(knn);
		loader.LoadAll();
		g_loader = &loader;

		//query collection
		kelp::QueryService queryer(knn,loader.GetQueryPath());

		//report collection
		kelp::ReporterManager reporter(knn,loader);
		g_reporter = &reporter;

		//poller collection
		kelp::KNNPoller poller(knn,loader);
		g_poller = &poller;

		std::cout << "KNN Node is running!! " << std::endl;

		boost::thread th(boost::bind(&kelp::KNNPoller::Start,&poller));
		boost::thread query_th(boost::bind(&kelp::ReporterManager::Start,&reporter));

		th.join();
		std::cout << "poller thread finished" << std::endl;
		query_th.join();
		std::cout << "query thread finished" << std::endl;
	}
	catch(std::runtime_error& e)
	{
		std::cout << "exception caught: " << e.what() << std::endl;
		exit(-1);
	}
	catch(const char* msg)
	{
		std::cerr << msg << std::endl;
		exit(-2);
	}
	catch(...)
	{
		std::cout << "UNKNOW EXCEPTION!!!  KNN NODE EXIT NOW!!!" << std::endl;
		exit(-3);
	}

	std::cout << "\n\n EXIT SAFELY! \n";
	return 0;
}
