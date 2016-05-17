/*************************************************************************
	> File Name: rrd_operator.h
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年04月01日 星期三 21时43分40秒
 ************************************************************************/

#ifndef KELP_COMM_RRD_OPERATOR_H_
#define KELP_COMM_RRD_OPERATOR_H_

#include <string>
#include <time.h>
#include <vector>
#include "log4cxx/logger.h"


namespace kelp
{
class RRDOperator
{
public:
	RRDOperator(const std::string &filename,const std::string &ds_name);
	~RRDOperator();
	int InsertNum(time_t timestamp,double data);
	int FetchData(time_t start, time_t end,std::vector<double>&outcome);

private:
	std::string filename_;
	std::string ds_name_;
	log4cxx::LoggerPtr log_;
};
}

#endif

