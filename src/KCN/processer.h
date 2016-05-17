/*************************************************************************
	> File Name: processer.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 16时45分52秒
 ************************************************************************/

#ifndef KELP_KCN_PROCESSER_H_
#define KELP_KCN_PROCESSER_H_

#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <log4cxx/logger.h>
#include <mongo/bson/bson.h>

#include "comm/config_data.h"
#include "dbmodules_loader.h"

#define THR_NUM 1
#define SIZE 4*1024

namespace kelp
{
class Processer : public ACE_Task<ACE_MT_SYNCH>
{
public:
	Processer(const Stores&,DBModules&);
	int open(void*);
	int svc(void);
	int close(u_long);
	void Exit(void);

	void Handle(mongo::BSONObj&);
private:
	void DoCluster(const std::string&,mongo::BSONObj&);
	void DoHost(const std::string&,const std::string&,mongo::BSONObj&);
	ACE_Message_Block* msg_;
	DBModulesLoader db_loader;
	const Stores& stores_;
	DBModules& db_modules_;
	log4cxx::LoggerPtr log_;
    //do not need callback list any more
	//std::map<std::string,std::list<void(*)(const char*,int,const char*)> > callback_;
	bool loop;
	
};
}

#endif
