/*************************************************************************
	> File Name: conf_loader.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月09日 星期三 16时52分45秒
 ************************************************************************/

#include <sstream>
#include "conf_loader.h"

namespace kelp
{
boost::shared_ptr<ConfLoader> ConfLoader::s_instance_;
ConfLoader::ConfLoader(ENM::Node& node):node_(node)
{
	log_ = log4cxx::Logger::getLogger("knn_conf_loader");

	LOG4CXX_INFO(log_,"ConfLoader constructer");
}

ConfLoader& ConfLoader::GetInstance(ENM::Node& node)
{
	static boost::mutex mu;
	if(s_instance_.get() == NULL)
	{
		boost::mutex::scoped_lock lock(mu);
		if(s_instance_.get() == NULL)
		{
			s_instance_.reset(new ConfLoader(node));
		}
	}

	return *s_instance_;
}

void ConfLoader::LoadAll()
{
	LoadGlobal(node_);
	LoadCluster(node_);
	LoadGroups(node_);
}

bool ConfLoader::Handle(const std::string key,std::string value, void* ptr)
{
	//update member vars
	if(key == "global")
	{
		KNNPoller* poller = static_cast<KNNPoller*>(ptr);
		poller->Clean();
		SetGlobal(value);
		poller->Reload();
	}
	else if(key == "ip")
		SetIP(value);
	else if(key == "cluster_name")
		SetClusterName(value);
	else if(key == "udp_send_channel")
	{
		SetUDPSendChannel(value);
		KNNPoller* poller = static_cast<KNNPoller*>(ptr);
		poller->UDPSendCallback();
	}
	else if(key == "udp_recv_channel")
	{
		SetUDPRecvChannel(value);
		KNNPoller* poller = static_cast<KNNPoller*>(ptr);
		poller->UDPRecvCallback();
	}
	else if(key == "tcp_accept_port")
	{
		SetTCPAcceptPort(value);
		KNNPoller* poller = static_cast<KNNPoller*>(ptr);
		poller->TCPAcceptCallback();
	}
	else if(key == "db_modules" || key == "collect_groups")
	{
		KNNPoller* poller = static_cast<KNNPoller*>(ptr);
		poller->Clean();
		LoadGroups(node_);
		poller->Reload();
	}
	else if(key == "report_modules")
	{
		ReporterManager* manager = static_cast<ReporterManager*>(ptr);
		manager->Clean();
		SetReportModules(value);
		manager->Reload();
	}
	else if(key == "query_path")
	{
		throw "Query path will changed after manual restart knn process";
	}
	else
		throw "ILLEGAL CONFIGURATION!";


	return true;
}


void ConfLoader::LoadGlobal(ENM::Node& node)
{
	//get global infomation form Coral
	std::string global_temp = node.getConfig("global");
	LOG4CXX_DEBUG(log_,"global"+global_temp);
	if(global_temp == "")
		throw "EMPTY CONFIGURATION:GLOBAL!";
	else
		SetGlobal(global_temp);

	std::string ip_temp = node.getConfig("ip");
	LOG4CXX_DEBUG(log_,"ip"+ip_temp);
	if(ip_temp == "")
		throw "EMPTY CONFIGURATION:IP!";
	else
		SetIP(ip_temp);
}

void ConfLoader::LoadCluster(ENM::Node& node)
{
	//get cluster infomation form Coral
	std::string name_temp = node.getConfig("cluster_name");
	LOG4CXX_DEBUG(log_,"cluster"+name_temp);
	if(name_temp == "")
		throw "EMPTY CONFIGURATION:CLUSTER NAME!";
	else
		SetClusterName(name_temp);

	std::string udp_send_temp = node.getConfig("udp_send_channel");
	LOG4CXX_DEBUG(log_,"udp_send"+udp_send_temp);
	if(udp_send_temp == "")
		throw "EMPTY CONFIGURATION:UDP SEND CHANNEL!";
	else
		SetUDPSendChannel(udp_send_temp);

	std::string udp_recv_temp = node.getConfig("udp_recv_channel");
	LOG4CXX_DEBUG(log_,"udp_recv"+udp_recv_temp);
	if(udp_recv_temp == "")
		throw "EMPTY CONFIGURATION:UDP RECV CHANNEL!";
	else
		SetUDPRecvChannel(udp_recv_temp);

	std::string tcp_port_temp = node.getConfig("tcp_accept_port");
	LOG4CXX_DEBUG(log_,"tcp_acce"+tcp_port_temp);
	if(tcp_port_temp == "")
		throw "EMPTY CONFIGURATION:TCP PORT!";
	else
		SetTCPAcceptPort(tcp_port_temp);
}

void ConfLoader::LoadGroups(ENM::Node& node)
{
	std::string reporter_temp = node.getConfig("report_modules");
	LOG4CXX_DEBUG(log_,"report"+reporter_temp);
	if(reporter_temp == "")
		throw "EMPTY CONFIGURATION:REPORT MODULE!";
	else
		SetReportModules(reporter_temp);
	//get query path
	std::string query_temp = node.getConfig("query_path");
	LOG4CXX_DEBUG(log_,"query:"+query_temp);
	if(query_temp == "")
		throw "EMPTY CONFIGURATION:QUERY PATH!";
	else
		SetQueryPath(query_temp);
	//get collection groups infomations form Coral
	std::string modules_temp = node.getConfig("db_modules");
	LOG4CXX_DEBUG(log_,"module"+modules_temp);
	if(modules_temp == "")
		throw "EMPTY CONFIGURATION:MODULES!";
	//std::string modules_temp = "example,true,/home/vimer/Kelp/src/module/example.so,arg1 arg2;ex,false,/usr/lib/ex.so,lal hh;";
	boost::tokenizer<boost::char_separator<char> > tok(modules_temp,
			boost::char_separator<char>(";"));
	std::map<std::string,Module> module_map;
	for(auto x: tok)
	{
		boost::tokenizer<boost::char_separator<char> > tk(x,
				boost::char_separator<char>(","));
		boost::tokenizer<boost::char_separator<char> >::iterator item = tk.begin();
		Module temp;
		temp.name = *item;
		++item;
		if(*item == "true")
			temp.enable = true;
		else if(*item == "false")
			temp.enable = false;
		else
			throw "ILLEGAL CONFIGURATION!";
		temp.path = *(++item);
		temp.params = *(++item);
		module_map[temp.name] = temp;
	}

	std::string collection_groups_temp = node.getConfig("collect_groups");
	LOG4CXX_DEBUG(log_,"collection"+collection_groups_temp);
	if(collection_groups_temp == "")
		throw "EMPTY CONFIGURATION:COLLECTION GROUPS!";
	//std::string collection_groups_temp = "false,5,10,example,ex;";
	tok.assign(collection_groups_temp,boost::char_separator<char>(";"));
	collection_groups_.clear();
	for(auto x: tok)
	{
		boost::tokenizer<boost::char_separator<char> > tk(x,
				boost::char_separator<char>(","));
		boost::tokenizer<boost::char_separator<char> >::iterator item = tk.begin();
		CollectionGroup group_temp;
		if(*item == "true")
			group_temp.collection_once = true;
		else if(*item == "false")
			group_temp.collection_once = false;
		else
			throw "ILLEGAL CONFIGURATION!";
		std::stringstream ss(*(++item));
		ss >> group_temp.collection_every;
		ss.clear();
		ss.str(*(++item));
		ss >> group_temp.time_threshold;
		for(++item;item!=tk.end();++item)
		{
			if(module_map.count(*item) > 0)
				group_temp.modules.push_back(module_map[*item]);
		}
		collection_groups_.push_back(group_temp);
	}
}

void ConfLoader::SetGlobal(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION!";
	//std::string global_temp = "true,false";
	boost::tokenizer<> tok(value);
	boost::tokenizer<>::iterator beg = tok.begin();

	if(*beg == "true")
		globals_.mute = true;
	else if(*beg == "false")
		globals_.mute = false;
	else
		throw "ILLEGAL CONFIGURATION!";
	++beg;
	if(*beg == "true")
		globals_.deaf = true;
	else if(*beg == "false")
		globals_.deaf = false;
	else
		throw "ILLEGAL CONFIGURATION!";
}

void ConfLoader::SetIP(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION!";
	ip_ = value;
}

void ConfLoader::SetClusterName(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION!";
	cluster_name_ = value;
}

void ConfLoader::SetUDPSendChannel(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION!";
	//std::string udp_send_temp = "MCAST,114.214.114.24,80";
	boost::tokenizer<boost::char_separator<char> > tok(value,
			boost::char_separator<char>(","));
	boost::tokenizer<boost::char_separator<char> >::iterator beg = tok.begin();
	if(*beg == "MCAST")
		udp_send_channel_.send_type = MCAST;
	else if(*beg == "UCAST")
		udp_send_channel_.send_type = UCAST;
	else
		throw "ILLEGAL CONFIGURATION!";
	udp_send_channel_.ip = *(++beg);
	std::stringstream ss(*(++beg));
	ss >> udp_send_channel_.port;
}

void ConfLoader::SetUDPRecvChannel(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION!";
	//std::string udp_recv_temp = "UCAST,222.214.114.24,443";
	boost::tokenizer<boost::char_separator<char> > tok(value,
			boost::char_separator<char>(","));
	boost::tokenizer<boost::char_separator<char> >::iterator beg = tok.begin();
	if(*beg == "MCAST")
		udp_recv_channel_.recv_type = MCAST;
	else if(*beg == "UCAST")
		udp_recv_channel_.recv_type = UCAST;
	else
		throw "ILLEGAL CONFIGURATION!";
	udp_recv_channel_.mcast_join = *(++beg);
	std::stringstream ss(*(++beg));
	ss >> udp_recv_channel_.port;
}

void ConfLoader::SetTCPAcceptPort(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION!";
	std::stringstream ss(value);
	ss >> tcp_accept_port_;
}

void ConfLoader::SetReportModules(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION!";
	report_path_ = value;
}

void ConfLoader::SetQueryPath(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION!";
	query_path_ = value;
}
};
