/*************************************************************************
	> File Name: conf_loader.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年09月26日 星期六 16时29分03秒
 ************************************************************************/

#include "conf_loader.h"

namespace kelp
{
boost::shared_ptr<ConfLoader> ConfLoader::s_instance_;

ConfLoader::ConfLoader(ENM::Node& node)
	:node_(node)
{
	log_ = log4cxx::Logger::getLogger("kcn_conf_loader");

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
	std::string db_temp = node_.getConfig("db_modules");
	LOG4CXX_DEBUG(log_,"db module:"+db_temp);
	if(db_temp == "")
		throw "EMPTY CONFIGURATION:DB MODULES!";
	else
		LoadDBModules(db_temp);

	std::string stores_temp = node_.getConfig("stores");
	LOG4CXX_DEBUG(log_,"store module:"+stores_temp);
	if(stores_temp == "")
		throw "EMPTY CONFIGURATION:STORE MODULES!";
	else
		LoadStores(stores_temp);

	std::string source_temp = node_.getConfig("data_source");
	LOG4CXX_DEBUG(log_,"source module:"+source_temp);
	if(source_temp == "")
		throw "EMPTY CONFIGURATION:SOURCE MODULES!";
	else
		LoadSources(source_temp);
}

bool ConfLoader::Handle(const std::string key, std::string value, KCNPoller* poller)
{
	if(key == "db_modules")
	{
		poller->Clean();
		LoadDBModules(value);
		poller->Reload();
	}
	else if(key == "stores")
	{
		poller->Clean();
		LoadStores(value);
		poller->Reload();
	}
	else if(key == "data_source")
	{
		poller->Clean();
		LoadSources(value);
		poller->Reload();
	}
	else
		throw "ILLEGAL CONFIGURE KEY!";

	return true;
}

bool ConfLoader::TopoHandle(const std::string uuid, Coral::Action action, KCNPoller* poller)
{
	std::string name = node_.getUSNConfig(uuid,"cluster_name");
	std::string ip = node_.getUSNConfig(uuid,"ip");
	std::string port_s = node_.getUSNConfig(uuid,"tcp_accept_port");
	unsigned int port;
	{
		std::stringstream ss;
		ss << port_s;
		ss >> port;
	}

	//node could be knn node or ksn node
	//knn node's name is cluster name
	//ksn node's name is grid name
	if(name == "")
		name = node_.getUSNConfig(uuid,"grid_name");
	if(name == "")
	{
		std::ostringstream oss;
		oss << uuid << ": This node have no cluster or grid name";
		LOG4CXX_WARN(log_,oss.str());

		return false;
	}

	DataSources::iterator iter = sources_.begin();
	for(;iter!=sources_.end();++iter)
	{
		if(iter->name != name)
			continue;
		else
		{
			//find the cluster which this node is belong to
			if(action != Coral::add)
			{
				//delete the node from this data source
				NodeList::iterator it = 
					find_if(iter->node_list.begin(),iter->node_list.end(),InCluster(ip));
				if(it!=iter->node_list.end())
				{
					iter->node_list.erase(it);
					LOG4CXX_INFO(log_,"erase "+uuid+" from "+name);
					return true;
				}
			}
			else
			{
				//add the node into this data source
				NodeList::iterator it = 
					find_if(iter->node_list.begin(),iter->node_list.end(),InCluster(ip));
				if(it == iter->node_list.end())
				{
					NodeInfo node_temp;
					node_temp.ip = ip;
					node_temp.port = port;
					iter->node_list.push_back(node_temp);
					std::stringstream ss;
					ss << uuid << "(" << ip << ":" << port << ")==>" << name;
					LOG4CXX_INFO(log_,ss.str());
					return true;
				}
			}
		}
	}


	//this node belong to a new cluster!!!
	//neet to change the data_source FIRST!!!
	std::string str = uuid + "DO NOT BELONG ANY CLUSTER/GRID!";
	throw str.c_str();
}

void ConfLoader::LoadDBModules(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION:DBModules!";

	boost::tokenizer<boost::char_separator<char> > tok(value,
			boost::char_separator<char>(";"));
	//clean old data
	db_modules_.clear();
	for(auto x : tok)
	{
		boost::tokenizer<boost::char_separator<char> >tk(x,
				boost::char_separator<char>(","));
		boost::tokenizer<boost::char_separator<char> >::iterator item = tk.begin();
		DBModule db_module;
		db_module.module_name = *item;
		++item;
		if(*item=="true")
			db_module.enable = true;
		else if(*item=="false")
			db_module.enable = false;
		else
			throw "ILLEGAL CONFIGURATION:DBModules!";

		db_module.path = *(++item);
		db_module.params = *(++item);

		db_modules_.push_back(db_module);
	}
}

void ConfLoader::LoadStores(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION:Stores!";

	boost::tokenizer<boost::char_separator<char> > tok(value,
			boost::char_separator<char>(";"));
	//clear old data
	stores_.clear();
	for(auto x : tok)
	{
		boost::tokenizer<boost::char_separator<char> >tk(x,
				boost::char_separator<char>(","));
		boost::tokenizer<boost::char_separator<char> >::iterator item = tk.begin();
		Store store;
		store.key_name = *item;
		
		boost::tokenizer<> t(*(++item));
		for(auto m : t)
		{
			store.module_name.push_back(m);
		}

		stores_.push_back(store);
	}
}

void ConfLoader::LoadSources(std::string value)
{
	if(value == "")
		throw "ILLEGAL CONFIGURATION:Sources!";

	//get all son nodes
	CGN::USNTopoMap topo_map = node_.getRelation();
	std::vector<std::string> uuids = topo_map[Coral::next];
	std::map<std::string,NodeList> source_list;
	for(auto uuid : uuids)
	{
		std::string name = node_.getUSNConfig(uuid,"cluster_name");
		std::string ip = node_.getUSNConfig(uuid,"ip");
		std::string port_s = node_.getUSNConfig(uuid,"tcp_accept_port");
		unsigned int port;
		{
			std::stringstream ss;
			ss << port_s;
			ss >> port;
		}

		//node could be knn node or ksn node
		//knn node's name is cluster name
		//ksn node's name is grid name
		if(name == "")
			name = node_.getUSNConfig(uuid,"grid_name");
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
		ss << uuid << "(" << ip << ":" << port << ")==>" << name;
		LOG4CXX_DEBUG(log_,ss.str());
	}

	boost::tokenizer<boost::char_separator<char> > tok(value,
			boost::char_separator<char>(";"));
	//clear old data
	sources_.clear();
	for(auto x : tok)
	{
		boost::tokenizer<boost::char_separator<char> > tk(x,
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

		sources_.push_back(source);
	}
}
}
