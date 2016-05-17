/*************************************************************************
	> File Name: mongo_operator.cpp
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年04月23日 星期四 09时03分57秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "mongo_operator.h"

namespace kelp{

MongoOperator::MongoOperator(const std::string &dbname,const std::string &collection_name):dbname_(dbname),collection_name_(collection_name)
{
	log_=log4cxx::Logger::getLogger("mongo_operator");
	mongo::client::initialize();
	if(ConnectDB())
	{
		LOG4CXX_ERROR(log_,"Could not able to link mongod server!");
		throw std::runtime_error("a runtime errror!");
	}
	
}

MongoOperator::~MongoOperator()
{
/*	mongo::BSONObj info;
	connection_.logout(dbname_,info);
	std::cout << info.toString() << std::endl;  */

}

bool MongoOperator::ConnectDB()
{
	try
	{
		connection_.connect("localhost");
		return 0;
	}
	catch(const mongo::UserException &e)
	{
		LOG4CXX_ERROR(log_, e.what());
	}
	return -1;
}

int MongoOperator::Insert(const std::string &key,const std::string &value)
{
	
	mongo::BSONObjBuilder bob;
	bob.append(key,value);
	mongo::BSONObj bo = bob.obj();
	connection_.insert(dbname_+"."+collection_name_,bo);
	std::string e = connection_.getLastError();
	if(!e.empty())
	{
		LOG4CXX_WARN(log_,"Insert Data failed!");
		return -1;
	}
	else
	{	
		LOG4CXX_INFO(log_,"Insert Data successfully!");
		return 0;
	}

}

int MongoOperator::Insert(mongo::BSONObj &key_value)
{

	connection_.insert(dbname_+"."+collection_name_,key_value);
	std::string e = connection_.getLastError();
	if(!e.empty())
	{
		LOG4CXX_WARN(log_,"Insert Data failed!");
		return -1;
	}
	else
	{	
		LOG4CXX_INFO(log_,"Insert Data successfully!");
		return 0;
	}
}


int MongoOperator::Insert(const std::string &key,double value)
{
	
	mongo::BSONObjBuilder bob;
	bob.append(key,value);
	mongo::BSONObj bo = bob.obj();
	connection_.insert(dbname_+"."+collection_name_,bo);
	std::string e = connection_.getLastError();
	if(!e.empty())
	{
		LOG4CXX_WARN(log_,"Insert Data failed!");
		return -1;
	}
	else
	{	
		LOG4CXX_INFO(log_,"Insert Data successfully!");
		return 0;
	}
}

int MongoOperator::Insert(const std::string &key,bool value)
{
	mongo::BSONObjBuilder bob;
	bob.append(key,value);
	mongo::BSONObj bo = bob.obj();
	connection_.insert(dbname_+"."+collection_name_,bo);
	std::string e = connection_.getLastError();
	if(!e.empty())
	{
		LOG4CXX_WARN(log_,"Insert Data failed!");
		return -1;
	}
	else
	{	
		LOG4CXX_INFO(log_,"Insert Data successfully!");
		return 0;
	}
}
/*	
int MongoOperator::Insert(const std::string &filename)
{
	mongo::GridFS gridfs(connect_,dbname_);
	mongo::BSONObj back;
	back = gridfs.storeFile(filename);
	std::cout << back.toString() << std::endl;
	return 0;
}
*/
int MongoOperator::Insert(const std::string &key,int value)
{
	mongo::BSONObjBuilder bob;
	bob.append(key,value);
	mongo::BSONObj bo = bob.obj();
	connection_.insert(dbname_+"."+collection_name_,bo);
	std::string e = connection_.getLastError();
	if(!e.empty())
	{
		LOG4CXX_WARN(log_,"Insert Data failed!");
		return -1;
	}
	else
	{	
		LOG4CXX_INFO(log_,"Insert Data successfully!");
		return 0;
	}
}


int MongoOperator::Insert(const std::string &key,long long value)
{
	mongo::BSONObjBuilder bob;
	bob.append(key,value);
	mongo::BSONObj bo = bob.obj();
	connection_.insert(dbname_+"."+collection_name_,bo);
	std::string e = connection_.getLastError();
	if(!e.empty())
	{
		LOG4CXX_WARN(log_,"Insert Data failed!");
		return -1;
	}
	else
	{	
		LOG4CXX_INFO(log_,"Insert Data successfully!");
		return 0;
	}
}




int MongoOperator::QueryData(mongo::BSONObj &query_condition,std::vector<mongo::BSONObj>&query_outcome)
{

    std::auto_ptr<mongo::DBClientCursor>cursor = connection_.query(dbname_+"."+collection_name_,query_condition);
	while(cursor->more())
		query_outcome.push_back(cursor->next());
	if(query_outcome.empty())
		LOG4CXX_WARN(log_,"Query outcome is empty!");
	return 0;

}

}






	
