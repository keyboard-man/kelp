/*************************************************************************
	> File Name: rrd_operatpr.cpp
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年03月30日 星期一 15时22分35秒
 ************************************************************************/

#include <iostream>
#include <string.h>
#include <time.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>

#include "rrd.h"
#include "rrd_tool.h"
#include "rrd_operator.h"


namespace kelp{
RRDOperator::RRDOperator(const std::string &filename,const std::string &ds_name):filename_(filename),ds_name_(ds_name){
	//init the log
	log_=log4cxx::Logger::getLogger("rrd_operator");
}

RRDOperator::~RRDOperator(){}

int  RRDOperator::InsertNum(time_t timestamp,double data)
{
	int cs=0;
	int us=0;
	char ds_argu[50]="DS:";
	
//定义命令行参数的主要元素
	
	char create_arg[] = "create";
	char start_arg[] = "-b";
	char time[] = "-s 30";
	char cf_arg[] = "RRA:AVERAGE:0.5:1:6000";
	char update_arg[]="update";
	int argc_upd=3;
	
	std::string str_time="";
	std::string str_data="";
	std::stringstream stream_upd;

	stream_upd << timestamp;
	stream_upd >> str_time;
	stream_upd.clear();

	stream_upd << data;
	stream_upd >> str_data;
	stream_upd.clear();
    
	char *c_str_time=const_cast<char*>(str_time.c_str());
	strcat(ds_argu,ds_name_.c_str());
	strcat(ds_argu,":GAUGE:6000:U:U");

	if(access(filename_.c_str(),0)!=0)
	{
		LOG4CXX_WARN(log_,"RRD file does not exist,a new RRD file will be found.");
		//创建RRD文件
		char *argv_cre[]={create_arg,const_cast<char*>(filename_.c_str()),start_arg,c_str_time,ds_argu,cf_arg};

		int argc_cre=6;

		cs=rrd_create(argc_cre,argv_cre);

		if(cs!=0)
		{
			LOG4CXX_ERROR(log_,"A runtime_error is detected,rrd file is not found successfully!")
			throw std::runtime_error("A runtime_error!");
		}
		timestamp +=1;
		stream_upd << timestamp;
		stream_upd >> str_time;
		stream_upd.clear();
		c_str_time = const_cast<char*>(str_time.c_str());

	}

	//插入数据
	strcat(c_str_time,":");
	strcat(c_str_time,const_cast<char*>(str_data.c_str()));
	char *time_data_argu=c_str_time;
	char *argv_upd[]={update_arg,const_cast<char*>(filename_.c_str()),time_data_argu};

	us = rrd_update(argc_upd,argv_upd);

	//write the log
	if(us)
		LOG4CXX_WARN(log_,"Insert data failed!");

    if(cs||us)
		return -1;
	else
		return 0;
}

int RRDOperator::FetchData(time_t start,time_t end,std::vector<double>&outcome)
{
	int fetch_status;
	unsigned long step=300;
	unsigned long ds_cnt=1;
	char **ds_namv=NULL;
	double  *data=NULL;
	int rows=(end-start)/ step+1;

	fetch_status=rrd_fetch_fn(const_cast<char*>(filename_.c_str()),(cf_en)0,&start,&end,&step,&ds_cnt,&ds_namv,&data);

	if(fetch_status)
		return -1;
	else
	{
		for(int i=0;i<rows;i++)
			outcome[i]=*(data+i);
		return 0;
	}
}


		
}


