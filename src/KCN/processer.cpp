/*************************************************************************
	> File Name: processer.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年08月02日 星期日 16时53分31秒
 ************************************************************************/

#include "processer.h"

namespace kelp
{
Processer::Processer(const Stores& stores,DBModules& modules)
	:stores_(stores),db_modules_(modules),db_loader(modules),loop(true)
{
	log_ = log4cxx::Logger::getLogger("processer");

    //do not need callback list any more!!
    //just callback all the dbmodules
    //
	//creat callback function list
	//for(Stores::const_iterator it=stores_.begin();it!=stores_.end();++it)
	//{
	//	std::list<void(*)(const char*,int,const char*)> temp;
	//	for(int i=0;i<it->module_name.size();++i)
	//	{
	//		std::string mod_temp = it->module_name[i];
	//		DBModules::iterator dbit = db_modules_.begin();
	//		while(dbit!=db_modules_.end() && (mod_temp!=dbit->module_name))
	//			++dbit;
	//		if(dbit!=db_modules_.end())
	//			temp.push_back(dbit->handler);
	//	}
	//	callback_[it->key_name] = temp;
	//}
}

int Processer::open(void*)
{
	activate(THR_NEW_LWP,THR_NUM);
	return 0;
}

int Processer::svc(void)
{
	char ch[SIZE] = { };
	while(loop)
	{
		try
		{
			msg_ = 0;
			getq(msg_);

			//change to mongo::BSONObj
			//handle it
			if(msg_)
			{
				memset(ch,0,SIZE);
				memcpy(ch,msg_->rd_ptr(),SIZE);
				if(!(*ch))
					throw "EMPTY BSONOBJ";
				mongo::BSONObj bson(ch);
				std::cout << bson << std::endl;

				Handle(bson);

				delete [] msg_->rd_ptr();
				msg_ ->release();
			}
		}
		catch(const char* ch)
		{
			LOG4CXX_ERROR(log_,ch);
		}
	}

	return 0;
}

int Processer::close(u_long)
{
	//clean the loaded modules
	db_loader.CleanModules(db_modules_);
	LOG4CXX_DEBUG(log_,"===== db modules destroyed =====");

	return 0;
}

void Processer::Exit()
{
	loop = false;
	msg_queue()->deactivate();
	wait();
}

void Processer::Handle(mongo::BSONObj& bson)
{
	//handle the bson
	//maybe grid-bosn;maybe cluster-bson
	std::string grid_id;

	if(bson.hasField("grid_ID") && bson.hasField("cluster_data"))
	{
		grid_id = bson.getStringField("grid_ID");
		std::vector<mongo::BSONElement> c_ele = bson["cluster_data"].Array();
		for(int i=0;i<c_ele.size();i++)
		{
			mongo::BSONObj obj = c_ele[i].Obj();
			DoCluster(grid_id,obj);
		}
	}
	else
	{
		grid_id = "";
		DoCluster(grid_id,bson);
	}
}

void Processer::DoCluster(const std::string& grid,mongo::BSONObj& cluster)
{
	std::string cluster_id;

	if(cluster.hasField("cluster_ID") && cluster.hasField("host_data"))
	{
		cluster_id = cluster.getStringField("cluster_ID");
		std::vector<mongo::BSONElement> h_ele = cluster["host_data"].Array();
		for(int i=0;i<h_ele.size();i++)
		{
			mongo::BSONObj obj = h_ele[i].Obj();
			DoHost(grid,cluster_id,obj);
		}
	}
	else
	{
		std::stringstream oss;
		oss << "This data is illegal! Drop!!";
		LOG4CXX_WARN(log_,oss.str());
		std::cout << cluster << std::endl;
	}

}

void Processer::DoHost(const std::string& grid,const std::string& cluster,mongo::BSONObj& host)
{
	std::string host_id;
	std::cout << host << std::endl;
	if(host.hasField("host_ID") && host.hasField("heartbeat"))
	{
        //deal the record with host level
        //do not need to cut it off
        DBModules::iterator iter = db_modules_.begin();
        for(;iter!=db_modules_.end();++iter)
        {
            iter->handler(host.objdata(),host.objsize(),NULL);
        }

	//	host_id = host.getStringField("host_ID");
	//	std::vector<mongo::BSONElement> ele;
	//	host.elems(ele);
	//	for(int i=0;i<ele.size();i++)
	//	{
	//		if((!strcmp(ele[i].fieldName(),"host_ID")) || 
	//				(!strcmp(ele[i].fieldName(),"heartbeat")))
	//		{
	//			continue;
	//		}
	//		else
	//		{
	//			std::string ds_name = ele[i].fieldName();
	//			std::string path;
	//			if(grid!="")
	//				path = grid + '/' + cluster + '/' + host_id;
	//			else
	//				path = cluster + '/' + host_id;
	//			mongo::BSONObj obj = ele[i].wrap();
	//			std::cout << obj << std::endl;

	//			std::list<void(*)(const char*,int,const char*)>::iterator iter;
	//			iter = callback_[ds_name].begin();
	//			for(;iter!=callback_[ds_name].end();++iter)
	//			{
	//				(*iter)(obj.objdata(),obj.objsize(),path.c_str());
	//			}
	//		}
	//	}
	}
	else
	{
		std::stringstream oss;
		oss << "This data is illegal! Drop!!";
		LOG4CXX_WARN(log_,oss.str());
	}
}
}
