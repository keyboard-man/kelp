/*************************************************************************
	> File Name: /home/vimer/bson.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年03月24日 星期二 22时17分16秒
 ************************************************************************/
#include <iostream>

#include "log4cxx/propertyconfigurator.h"

#include "comm/comm_data.h"
#include "KNN/cluster_polymer.h"
#include "KSN/grid_polymer.h"
#include "KCN/top_grid_polymer.h"

int main()
{
	log4cxx::PropertyConfigurator::configure("../comm/log4cxx.properties");
	mongo::BSONObj h1_1 = BSON("host_ID"<<"H1"<<
			"heartbeat"<<(long long int)1234567890 << "cpu" << 
			BSON("cpu1"<<55<<"cpu2"<<45));
	mongo::BSONObj h1_2 = BSON("host_ID"<<"H1"<<
			"heartbeat"<<(long long int)1234567891 << "memory" << 
			BSON("memory1"<<12<<"memory2"<<34));
	mongo::BSONObj h1_3 = BSON("host_ID"<<"H1"<<
			"heartbeat"<<(long long int)1234567892 << "cpu" << 
			BSON("cpu1"<<55<<"cpu2"<<3));
	mongo::BSONObj h2_2 = BSON("host_ID"<<"H2"<<
			"heartbeat"<<(long long int)1234567893 << "memory" << 
			BSON("memory1"<<5<<"memory2"<<45));

	std::cout << "h1_1:\t" << h1_1 << std::endl <<
				 "h1_2:\t" << h1_2 << std::endl <<
				 "h1_3:\t" << h1_3 << std::endl <<
				 "h2_2:\t" << h2_2 << std::endl;
	std::cout << h1_1.objsize() << std::endl;
	
	kelp::ClusterPolymer polymer("c1");
	polymer.Append(h1_1);
	polymer.Append(h1_2);
	polymer.Append(h1_3);
	polymer.Append(h2_2);
	polymer.PrintHostData();

	mongo::BSONObj cluster_data = polymer.ClusterData();
	std::cout << cluster_data << std::endl;
	std::cout << cluster_data.objsize() << std::endl;

	std::cout << cluster_data["host_data"].Obj()[0]["heartbeat"].type() << std::endl;

	kelp::ClusterPolymer cluster("c2");
	cluster.Append(h1_1);
	cluster.Append(h2_2);
	mongo::BSONObj cluster_data2 = cluster.ClusterData();

	kelp::GridPolymer grid("g1");
	grid.Append(cluster_data);
	grid.Append(cluster_data2);
	mongo::BSONObj grid_data = grid.GridData();
	std::cout << "Grid Data:\n" << grid_data << std::endl;

	kelp::TopGridPolymer top("t1");
	top.Append(grid_data);
	top.Append(cluster_data);
	mongo::BSONObj top_data = top.TopGridData();
	std::cout << "\nTop Data:\n" << top_data << std::endl;

	return 0;
}

