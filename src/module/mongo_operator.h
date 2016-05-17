/*************************************************************************
	> File Name: mongo_operator.h
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年04月21日 星期二 11时21分42秒
 ************************************************************************/


#ifndef KELP_COMM_MONGO_OPERATOR_H_
#define KELP_COMM_MONGO_OPERATOR_H_

#include <string>
#include <vector>
#include "mongo/client/dbclient.h"
#include "log4cxx/logger.h"

namespace kelp
{
class MongoOperator
{
public:
	MongoOperator(const std::string &dbname,const std::string &collection_name);
	~MongoOperator();

	bool ConnectDB();
	int Insert(const std::string &key,const std::string &value);
	int Insert(mongo::BSONObj &key_value);
	int Insert(const std::string &key,double value);
	int Insert(const std::string &key,bool value);
	int Insert(const std::string &key,int value);
	int Insert(const std::string &key,long long value);
	//int Insert(const std::string &filename);	
	int QueryData(mongo::BSONObj &query_condition,std::vector<mongo::BSONObj>&query_outcome);
	
private:
	std::string dbname_;
	std::string collection_name_;
	mongo::DBClientConnection connection_;
	log4cxx::LoggerPtr log_;

};
}

#endif
