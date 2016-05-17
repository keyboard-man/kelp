/*************************************************************************
	> File Name: ../test/mongo_test.cpp
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年04月24日 星期五 08时51分01秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "mongo/client/dbclient.h"
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
#include "../comm/mongo_operator.h"

int main(int argc,char **argv)
{
	log4cxx::PropertyConfigurator::configure("../comm/log4cxx.properties");
	//插入非数值型数据
	std::string dbname1 = "test";
	std::string collection_name1 = "kelp";
	try{
		kelp::MongoOperator opt(dbname1,collection_name1);
		std::string key = "handsome";
		std::string value = "Chenjian";
		opt.Insert(key,value);//非数值型数据
		value = "ChenChen";
		mongo::BSONObj key_value =BSON(key<<value); 
		opt.Insert(key_value);
		//插入bool型数据
		bool bool_value = "true";
		for(int i = 0;i < 10; i++)
			opt.Insert(key,bool_value);
		//查询非数值型数据，测试键值对查询方式
		mongo::BSONObj query_condition = BSON(key<<value);
		std::vector<mongo::BSONObj>query_outcome;
		opt.QueryData(query_condition,query_outcome);
		for(std::vector<mongo::BSONObj> ::iterator it =query_outcome.begin();it!=query_outcome.end();++it)
			std::cout << (*it).toString() << std::endl; 
		
	}
	catch(std::runtime_error &r)
	{
		std::cout << r.what() << std::endl;
		return -1;
	}




	//插入数值型数据，测试非键值对插入方式
	std::string dbname2 = "test";
	std::string collection_name2 = "xuxijian";
	try{

		kelp::MongoOperator opt2(dbname2,collection_name2);
		std::string double_key = "id";
		int value_size = 5;
		double double_value[5] = {10086.12345,12.332,76.12,521.123,67.2234};
		for(int i = 0;i < value_size;i++)
			opt2.Insert(double_key,double_value[i]);

		//查询数值数据
		std::vector<mongo::BSONObj>query_outcome_2;
		
		mongo::BSONObj query_condition = BSON(double_key<<double_value[0]);
		opt2.QueryData(query_condition,query_outcome_2);
		for(std::vector<mongo::BSONObj> ::iterator it =query_outcome_2.begin();it!=query_outcome_2.end();++it)
			std::cout << (*it).toString() << std::endl;

		//插入图片
		//const std::string filename = "~/Kelp/src/comm/test.jpg";
		//opt2.Insert(filename);
	}
	catch(std::runtime_error &r)
	{
		std::cout << r.what() <<std::endl;
		return -1;
	}

	

	return 0;
}



		
	


