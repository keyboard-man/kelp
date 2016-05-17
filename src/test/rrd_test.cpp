/*************************************************************************
	> File Name: RRD_test.cpp
	> Author: ChenJian
    > mail: 543348250@qq.com
	> Created Time: 2015年04月07日 星期二 09时04分43秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <stdexcept>
#include <boost/thread.hpp>
#include "../module/rrd_operator.h"

#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"


int main(int argc,char *argv[])
{
	log4cxx::PropertyConfigurator::configure("../comm/log4cxx.properties");

    const	std::string filename="chenjian.rrd";
	const   std::string ds_name="chenjian";
	kelp::RRDOperator R1(filename,ds_name);
	int insrt_sgn[10],fetch_sgn;
	double data=10;
	time_t now=time(NULL);
	log4cxx::LoggerPtr main_log=log4cxx::Logger::getLogger("rrd_test");
	for (int i =0;i<10;i++)
	{
		try
		{

			insrt_sgn[i]=R1.InsertNum(now,data);
		}
		catch (std::runtime_error &r)
		{
			std::cout << "Caught a runtime error:" << r.what() << std::endl;
			break;
		}
			
//		delay(300);
		boost::thread::sleep(boost::get_system_time()+boost::posix_time::seconds(10));
		now=now+10;
		std::cout<<"插入数据判断标志位是："<<insrt_sgn[i]<<std::endl;

	}


	time_t end=time(NULL);
	time_t start=end-3000;
	const unsigned long cstep=300;
	int rows=(end-start)/cstep+1;
	std::vector<double>outcome(rows);
	fetch_sgn=R1.FetchData(start,end,outcome);
	if(!fetch_sgn)
	{
		LOG4CXX_INFO(main_log,"Fetch data successfully!");	
		for(std::vector<double>::iterator a=outcome.begin();a!=outcome.end();++a)
			std::cout<<*a<<std::endl;
	}
	else
		LOG4CXX_WARN(main_log,"Fetch data failed!");
    return 0;
}


	

