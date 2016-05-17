/*************************************************************************
	> File Name: kcn.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月03日 星期一 09时30分40秒
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

#include "kcn_poller.h"
#include "conf_loader.h"
#include "report_server.h"
#include "query_server.h"

#define CGNPORT 10003
#define SERPORT 12346
#define LOG_PATH "conf/log4cxx.conf"

std::map<std::string,std::string> g_config;
CGN::USNTopoMap g_topo;
kelp::KCNPoller* g_poller;
kelp::ConfLoader* g_loader;
kelp::ReportServer* g_report;
kelp::QueryServer* g_query;

class ConfigCallBackI : public ENM::ConfigCallBack
{
public:
	virtual void invoke(const std::string& key,const std::string& value, const Ice::Current&)
	{
		std::cout << "Config Changed : " << key << " -> " << value << std::endl;
		try
		{
			g_loader->Handle(key,value,g_poller);
		}
		catch(const char* msg)
		{
			std::cout << msg << std::endl;
			return ;
		}
		catch(...)
		{
			std::cout << "ConfigCallBackI::invoke==>UNKNOW EXCEPTION!" << std::endl;
			return ;
		}
		std::cout << "ConfigCallBackI::invoke function end!" << std::endl;
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

		try
		{
			if(rel==Coral::next)
				g_loader->TopoHandle(UUID,act,g_poller);
			else
				throw "Can not deal with the parent/neighbor node!";
		}
		catch(const char* msg)
		{
			std::cout << msg << std::endl;
			return ;
		}
		catch(...)
		{
			std::cout << "TopoCallBackI:invoke==>UNKNOW EXCEPTION!" << std::endl;
		}
		std::cout << "TopoCallBackI:invoke function end!!!" << std::endl;
	}
};

void sig_int(int num)
{
	std::cout << "\n press CTRL + C, now the program will exit!" << std::endl;

	g_poller->Stop();
	g_report->Stop();
	g_query->Stop();

}

int main(int argc,char** argv)
{
	log4cxx::PropertyConfigurator::configure(LOG_PATH);
	Ice::CommunicatorPtr ic = Ice::initialize(argc,argv);
	ENM::Node kcn("KCN",ic,"./kcn.uuid",CGNPORT,SERPORT,"KCN Node");
	ENM::ConfigCallBackPtr configCB = new ConfigCallBackI;
	ENM::TopoCallBackPtr topoCB = new TopoCallBackI;
	std::cout << "do register!" << std::endl;
	kcn.doRegister(configCB,topoCB);

	signal(SIGINT,sig_int);

	//for test
	//kelp::QueryInterfacePrx proxy;
	//proxy = kcn.service()->getServiceProxy<kelp::QueryInterfacePrx>(
	//		"287b8371-eac8-467a-9153-f304685ca239","query_a");
	//kelp::BinData result = proxy->Foo("");
	//for(int i=0;i<result.size();i++)
	//	std::cout << result[i];
	//std::cout << std::endl;

	try
	{
		kelp::ConfLoader loader = kelp::ConfLoader::GetInstance(kcn);
		loader.LoadAll();
		g_loader = &loader;

		std::cout << "KCN Node is running!!" << std::endl;

		//poll service
		kelp::KCNPoller poller(kcn,loader);
		g_poller = &poller;

		//report service
		kelp::ReportServer report;
		g_report = &report;

		//query service
		kelp::QueryServer query(ic,kcn);
		g_query = &query;

		boost::thread th_p(boost::bind(&kelp::KCNPoller::Start,&poller));
		boost::thread th_re(boost::bind(&kelp::ReportServer::Start,&report));
		boost::thread th_qu(boost::bind(&kelp::QueryServer::Start,&query));

		th_p.join();
		th_re.join();
		th_qu.join();
	}
	catch(std::runtime_error& e)
	{
		std::cout << "exception caught: " << e.what() << std::endl;
		exit(-1); }
	catch(const char* msg)
	{
		std::cerr << msg << std::endl;
		exit(-2);
	}
	catch(...)
	{
		std::cout << "EXCEPTION!!!  KCN NODE EXIT NOW!!!" << std::endl;
		exit(-3);
	}
	
	std::cout << "\n\nEXIT SAFELY!\n";

	return 0;
}
