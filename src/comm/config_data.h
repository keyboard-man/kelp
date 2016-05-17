/*************************************************************************
	> File Name: config_data.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年03月27日 星期五 15时29分45秒
 ************************************************************************/

#ifndef KELP_COMM_CONFIG_DATA_H_
#define KELP_COMM_CONFIG_DATA_H_

#include <string>
#include <vector>
#include <list>
#include <map>

#include "mongo/bson/bson.h"

namespace kelp{
enum CastType {MCAST,UCAST};
struct Globals
{
	bool mute;
	bool deaf;
};

struct UDPSendChannel
{
	CastType send_type;
	std::string ip;
	unsigned int port;
};

struct UDPRecvChannel
{
	CastType recv_type;
	std::string mcast_join;
	unsigned int port;
};

struct Module
{
	std::string name;
	bool enable;
	std::string path;
	std::string params;
	void* dl_handler;
	int (*init)(std::string);
	void (*handler)(char**,int&);
	int (*cleanup)(void);
};

typedef std::vector<Module> Modules;

struct CollectionGroup
{
	bool collection_once;
	int collection_every;
	int time_threshold;
	time_t last_collected;
	Modules modules;
};

typedef std::vector<CollectionGroup> CollectionGroups;

struct NodeInfo
{
	std::string ip;
	unsigned int port;
};

typedef std::vector<NodeInfo> NodeList;

struct DataSource
{
	std::string name;
	int  period;
	NodeList node_list;
};

typedef std::vector<DataSource> DataSources;

struct MetaData
{
	char *buf;
	unsigned int size;
	mongo::BSONObj bson;
	time_t time;
};

struct DBModule
{
	std::string module_name;
	bool enable;
	std::string params;
	std::string path;
	void* dl_handler;
	int (*init)(std::string);
	void (*handler)(const char*,int,const char*);
	int (*cleanup)(void);
};

typedef std::vector<DBModule> DBModules;

struct Store
{
	std::string key_name;
	std::vector<std::string> module_name;
};

typedef std::vector<Store> Stores;

struct ImageChannel{
	bool enable;
	int every;
	std::string host;
	unsigned int port;
	std::string path;
	int argc;
	char ** argv;
};

struct ImageModule{
	unsigned int port;
	std::string dbname;
};

struct ReportModule
{
	std::string name;
	bool enable;
	std::string path;
};

typedef std::vector<ReportModule> ReportModules;

}
#endif
