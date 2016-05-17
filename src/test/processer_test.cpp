/*************************************************************************
	> File Name: processer_test.cpp
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年05月04日 星期一 22时28分32秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "mongo/client/dbclient.h"
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
#include "KCN/processer.h"
#include "time.h"
int main(int argc,char **argv)
{	
	log4cxx::PropertyConfigurator::configure("../comm/log4cxx.properties");
	mongo::Date_t time_d = mongo::Date_t(1430365323000);
	time_t now = time(NULL);
	mongo::BSONObj bo_cpu1 = BSON("time"<<(long long)now<<"cpu1"<<84);
	mongo::BSONObj bo_cpu2 = BSON("time"<<(long long)(now+10)<<"cpu2"<<87);
	mongo::BSONObj bo_mem1 = BSON("time"<<(long long)(now+20)<<"mem1"<<78);
	mongo::BSONObj bo_mem2 = BSON("time"<<(long long)(now+30)<<"mem2"<<16);
	mongo::BSONObjBuilder temp_bob;
	temp_bob.append("host_ID","machao");
	temp_bob.append("heartbeat",time_d);
	temp_bob.append("module_info",bo_cpu1);
	temp_bob.append("module_info",bo_cpu2);
	temp_bob.append("module_info",bo_mem1);
	temp_bob.append("module_info",bo_mem2);
	mongo::BSONObj bo_host = temp_bob.obj();
	mongo::BSONArray boa_host_data = BSON_ARRAY(bo_host);
	mongo::BSONObjBuilder bob;
	bob.append("cluster_ID","cluster_NO.1");

	bob.appendArray("host_data",boa_host_data);
	mongo::BSONObj bo_cluster = bob.obj();
	std::cout << bo_cluster.toString() << std::endl;          //输出待解析的bson数据
	kelp::Processer proc("/home/vimer/Kelp/src/comm/kcn.conf");
	//proc.Handler(bo_cluster);

	mongo::BSONArray arr = BSON_ARRAY(bo_cluster);
	mongo::BSONObjBuilder grid_bob;
	grid_bob.append("grid_ID","g1");
	grid_bob.appendArray("cluster_data",arr);
	mongo::BSONObj bo_grid = grid_bob.obj();
	std::cout << bo_grid.toString() << std::endl;
	proc.Handler(bo_grid);

/*	bo_grid = bo_grid.removeField("grid_ID");

	std::vector<mongo::BSONElement> elem;
	bo_grid.elems(elem);
	std::cout << "elem's size:" << endl;
	std::cout << "############\n" << elem << std::endl;
	std::cout << elem[1].Array()[0] <<std::endl;

	std::vector<mongo::BSONObj> objs;
	bo_grid.vals(objs);
	std::cout << "########################################\n";
	std::cout << objs[0] << std::endl; */
	//mongo::DBClientConnection c; //连接数据库
	//c.connect("localhost");
//	std::string dbname = "kelp";
/*	std::string collection_name = "SCSN cluster NO.1machao";
	std::auto_ptr<mongo::DBClientCursor>cursor = c.query(dbname+"."+collection_name,mongo::BSONObj());
	while(cursor->more())
		std::cout << cursor->next().toString() << std::endl; */

	return 0;
}

	





	

