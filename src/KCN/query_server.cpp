/*************************************************************************
	> File Name: query_server.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月30日 星期一 20时28分19秒
 ************************************************************************/

#include "query_server.h"

namespace kelp
{
BinData web2kcnI::Query(const std::string& uuid,const std::string& ser_name, 
		const std::string& param, const Ice::Current&)
{
	QueryInterfacePrx proxy;
	proxy = node_.service()->getServiceProxy<QueryInterfacePrx>(uuid,ser_name);
	BinData result;
	result = proxy->Foo(param);

	return result;
}

bool cmd2kcnI::setNodeConfig(const std::string& uuid, const std::string& key, const std::string& value, const Ice::Current&)
{
    return node_.setConfig(uuid, key, value);
}

bool cmd2kcnI::setSelfConfig(const std::string& key, const std::string& value, const Ice::Current&)
{
    return node_.setConfig(key, value);
}

bool cmd2kcnI::delNodeConfig(const std::string& uuid, const std::string& key, const Ice::Current&)
{
    return node_.delUSNConfig(uuid, key);
}

bool cmd2kcnI::delSelfConfig(const std::string&key, const Ice::Current&)
{
    return node_.delConfig(key);
}

QueryServer::QueryServer(Ice::CommunicatorPtr ic, ENM::Node& node)
	:ic_(ic),node_(node)
{
	log_ = log4cxx::Logger::getLogger("query_server");
}

void QueryServer::Start(void)
{
	try
	{
		Ice::ObjectAdapterPtr adapter
			= ic_->createObjectAdapterWithEndpoints("QueryServerAdapter",
					"default -p 30038");
		Ice::ObjectPtr object = new web2kcnI(node_);
        Ice::ObjectPtr cmdObject = new cmd2kcnI(node_);
		adapter->add(object,ic_->stringToIdentity("QueryServer"));
        adapter->add(cmdObject,ic_->stringToIdentity("CmdServer"));
		adapter->activate();

		LOG4CXX_DEBUG(log_,"query server && cmd server start");
		ic_->waitForShutdown();
	}
	catch(const Ice::Exception &e)
	{
		std::cerr << e<< std::endl;
	}
	catch(const char * msg)
	{
		std::cerr << msg << std::endl;
	}
	
	LOG4CXX_DEBUG(log_,"query server && cmd server exit");
	return ;
}

void QueryServer::Stop(void)
{
	ic_->shutdown();

	return ;
}
}
