/*************************************************************************
	> File Name: testmain.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 15时09分39秒
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

#include "ksn_poller.h"
#include "conf_loader.h"

#define CGNPORT 10003
#define SERPORT 12346
#define LOG_PATH "conf/log4cxx.conf"

std::map<std::string,std::string> g_config;
CGN::USNTopoMap g_topo;
kelp::KSNPoller* g_poller;
kelp::ConfLoader* g_loader;

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
			std::cout << "ConfigCallBackI::invoke===>UNKNOW EXCEPTION!!" << std::endl;
			return ;
		}

		std::cout << "ConfigCallBackI::invoke function end!!!" << std::endl;
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
			std::cout << "TopoCallBackI::invoke==>UNKNOW EXCEPTION!" << std::endl;
			return ;
		}
		std::cout << "TopoCallBackI::invoke function end!!!" << std::endl;
	}
};

void sig_int(int num)
{
	std::cout << "\n press CTRL + C, now the program will exit!" << std::endl;

	g_poller->Stop();
}

int main(int argc,char** argv)
{
	log4cxx::PropertyConfigurator::configure(LOG_PATH);
	Ice::CommunicatorPtr ic = Ice::initialize(argc,argv);
	ENM::Node ksn("KSN",ic,"./ksn.uuid",CGNPORT,SERPORT,"KSN Node");
	ENM::ConfigCallBackPtr configCB = new ConfigCallBackI;
	ENM::TopoCallBackPtr topoCB = new TopoCallBackI;
	std::cout << "do register!" << std::endl;
	ksn.doRegister(configCB,topoCB);
	
	signal(SIGINT,sig_int);

	try
	{
		kelp::ConfLoader loader = kelp::ConfLoader::GetInstance(ksn);
		loader.LoadAll();
		g_loader = &loader;

		std::cout << "KSN Node is running!! " << std::endl;

		kelp::KSNPoller poller(ksn,loader);
		g_poller = &poller;
		boost::thread th(boost::bind(&kelp::KSNPoller::Start,&poller));

		th.join();
		std::cout << "poller thread finished" << std::endl;
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
		std::cout << "EXCEPTION!!!  KSN NODE EXIT NOW!!!" << std::endl;
		exit(-3);
	}

	std::cout << "\n\n EXIT SAFELY! \n";
	return 0;
}
