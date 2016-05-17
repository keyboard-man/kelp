/*************************************************************************
	> File Name: conf_loader.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月25日 星期五 16时55分44秒
 ************************************************************************/

#include "conf_loader.h"

namespace kelp
{
boost::shared_ptr<ConfLoader> ConfLoader::s_instance_;
ConfLoader::ConfLoader(ENM::Node& node):node_(node)
{
	log_ = log4cxx::Logger::getLogger("ksn_conf_loader");

	LOG4CXX_INFO(log_,"ConfLoader Constructer");
}

ConfLoader& ConfLoader::GetInstance(ENM::Node& node)
{
	static boost::mutex mu;
	if(s_instance_.get() == NULL)
	{
		boost::mutex::scoped_lock lock(mu);
		if(s_instance_.get()  == NULL)
		{
			s_instance_.reset(new ConfLoader(node));
		}
	}

	return *s_instance_;
}

void ConfLoader::LoadAll()
{
	LoadSource(node_);
	LoadComm(node_);
}

bool ConfLoader::Handle(const std::string key, std::string value,KSNPoller* poller)
{
	if(key == "data_source")
	{
		poller->Clean();
		LoadSource(node_);
		poller->Reload();
	}
	else if(key == "tcp_accept_port")
	{
		SetTCPAcceptPort(value);
		poller->TCPAcceptCallback();
	}
	else if(key == "grid_name")
		grid_name_ = value;
	else
		throw "ILLEGAL CONFIGURATION KEY!";

	return true;
}

void ConfLoader::TopoHandle(const std::string uuid, Coral::Action action, KSNPoller* poller)
{
	std::string name = node_.getUSNConfig(uuid,"cluster_name");
	std::string ip = node_.getUSNConfig(uuid,"ip");
	unsigned int port;
	std::string port_s = node_.getUSNConfig(uuid,"tcp_accept_port");
	{
		std::stringstream ss;
		ss << port_s;
		ss >> port;
	}
	//check node is knn node or ksn node
	//knn node already have name
	//ksn node do not have name yet!
	if(name == "")
	{
		name = node_.getUSNConfig(uuid,"grid_name");
	}
	if(name == "")
	{
		std::ostringstream oss;
		oss << uuid << ": This node have no cluster or grid name";
		LOG4CXX_WARN(log_,oss.str());

		return ;
	}

	DataSources::iterator iter = source_.begin();
	//find the cluster which this node belong to
	for(;iter!=source_.end();++iter)
	{
		if(iter->name != name)
		{
			continue;
		}
		else
		{
			if(action != Coral::add)
			{
				//delete the node form this data source
				NodeList::iterator it = 
					find_if(iter->node_list.begin(),iter->node_list.end(),InCluster(ip));
				if(it != iter->node_list.end())
				{
					iter->node_list.erase(it);
					LOG4CXX_INFO(log_,"erase "+uuid+" from "+name);
					return ;
				}
			}
			else
			{
				//add the node to this data source
				NodeList::iterator it = 
					find_if(iter->node_list.begin(),iter->node_list.end(),InCluster(ip));
				if(it == iter->node_list.end())
				{
					NodeInfo node_temp;
					node_temp.ip = ip;
					node_temp.port = port;
					iter->node_list.push_back(node_temp);
					std::stringstream ss;
					ss << uuid << "(" << ip << ":" << port << ")" << "==>" << name;
					LOG4CXX_INFO(log_,ss.str());
					return ;
				}
			}
		}
	}

	//this node belong to a new cluster!!!
	//need to change the data_source FIRST!!!
	std::string str = uuid + "DO NOT BELONG ANY CLUSTER/GRID!";
	throw str.c_str();
}

void ConfLoader::LoadSource(ENM::Node& node)
{
	std::string source_temp = node.getConfig("data_source");
	LOG4CXX_DEBUG(log_,"source: " + source_temp);
	if(source_temp == "")
		throw "EMPTY CONFIGURATION:DATA_SOURCE!";

	//get all son nodes
	CGN::USNTopoMap topo_map = node.getRelation();
	std::vector<std::string> uuids = topo_map[Coral::next];
	std::map<std::string,NodeList> source_list;
	for(auto uuid : uuids)
	{
		std::string name = node.getUSNConfig(uuid,"cluster_name");
		std::string ip = node.getUSNConfig(uuid,"ip");
		unsigned int port;
		std::string port_s = node.getUSNConfig(uuid,"tcp_accept_port");
		{
			std::stringstream ss;
			ss << port_s;
			ss >> port;
		}

		//check knn node or ksn node
		if(name == "")
		{
			name = node.getUSNConfig(uuid,"grid_name");
		}
		if(name == "")
		{
			std::ostringstream oss;
			oss << uuid << "do not have name!";
			LOG4CXX_WARN(log_,oss.str());

			continue;
		}
		
		NodeInfo node_temp;
		node_temp.ip = ip;
		node_temp.port = port;
		source_list[name].push_back(node_temp);
		std::stringstream ss;
		ss << uuid << "(" << ip << ":" << port << ")" << "==>" << name;
		LOG4CXX_DEBUG(log_,ss.str());
	}

	boost::tokenizer<boost::char_separator<char> >tok(source_temp,
			boost::char_separator<char>(";"));

	//clear old data loaded before!!
	source_.clear();
	for(auto x: tok)
	{
		boost::tokenizer<boost::char_separator<char> >tk(x,
				boost::char_separator<char>(","));
		boost::tokenizer<boost::char_separator<char> >::iterator item = tk.begin();
		DataSource source;
		source.name = *item;
		std::stringstream ss;
		ss << *(++item);
		ss >> source.period;
		if(source_list.count(source.name) > 0)
		{
			source.node_list = source_list[source.name];
		}

		source_.push_back(source);
	}
}

void ConfLoader::LoadComm(ENM::Node& node)
{
	grid_name_ = node.getConfig("grid_name");
	LOG4CXX_DEBUG(log_,"grid name: " + grid_name_);
	if(grid_name_ == "")
		throw "ILLEGAL CONFIGURATION:GRID NAME!";
	std::string tcp_temp = node.getConfig("tcp_accept_port");
	LOG4CXX_DEBUG(log_,"tcp accept port: " + tcp_temp);
	if(tcp_temp == "")
		throw "EMPTY CONFIGURATION:TCP ACCEPT PORT!";
	SetTCPAcceptPort(tcp_temp);
}

void ConfLoader::SetTCPAcceptPort(std::string value)
{
	if(value == "")
		throw "ILLEAGL CONFIGURATION:TCP ACCEPT PORT!";
	std::stringstream ss(value);
	ss >> tcp_accept_port_;
}
}
