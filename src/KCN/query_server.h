/*************************************************************************
	> File Name: query_server.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月30日 星期一 20时19分48秒
 ************************************************************************/

#ifndef KELP_KCN_QUERY_SERVER_H_
#define KELP_KCN_QUERY_SERVER_H_

#include <Ice/Ice.h>
#include <node.h>
#include <log4cxx/logger.h>

#include "base_query_interface.h"
#include "web2kcn.h"
#include "cmd2kcn.h"

namespace kelp
{
class web2kcnI : public web2kcn
{
public:
	web2kcnI(ENM::Node& node)
		:node_(node) { ; }
	virtual BinData Query(const std::string& uuid, const std::string& ser_name, 
			const std::string& param, const Ice::Current&);

private:
	ENM::Node& node_;
};

class cmd2kcnI : public cmd2kcn
{
public:
    cmd2kcnI(ENM::Node& node)
        :node_(node)
    {
        ;
    }
    //set configuration for uuid node
    virtual bool setNodeConfig(const std::string& uuid, const std::string& key, const std::string& value, const Ice::Current&);

    //set configuration for self node
    virtual bool setSelfConfig(const std::string& key, const std::string& value, const Ice::Current&);

    //delete configuration for uuid node
    virtual bool delNodeConfig(const std::string& uuid, const std::string& key, const Ice::Current&);

    //delete configuration for self node
    virtual bool delSelfConfig(const std::string& key, const Ice::Current&);


    //TODO:Add more interface to change node's configure

private:
    ENM::Node& node_;
};

class QueryServer
{
public:
	QueryServer(Ice::CommunicatorPtr ic, ENM::Node& node);
	void Start(void);
	void Stop(void);

private:
	Ice::CommunicatorPtr ic_;
	ENM::Node& node_;
	log4cxx::LoggerPtr log_;
};
}

#endif
