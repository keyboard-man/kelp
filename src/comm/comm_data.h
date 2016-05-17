/*************************************************************************
	> File Name: comm_data.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年03月24日 星期二 16时53分43秒
 ************************************************************************/

#ifndef KELP_COMM_COMM_DATA_H_
#define KELP_COMM_COMM_DATA_H_

#include <string>
#include <vector>

#include "mongo/bson/bson.h"

#include "config_data.h"

struct HostMetrics
{
	std::string host_uuid;
	std::vector<kelp::MetaData> host_metrics;
	time_t last_heartbeat;
};

struct ClusterMetrics
{
	std::string cluster_id;
	std::vector<mongo::BSONObj> cluster_metrics;
};

struct GridMetrics
{
	std::string grid_id;
	std::vector<mongo::BSONObj> grid_metrics;
};
#endif
