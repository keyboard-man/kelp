/*************************************************************************
	> File Name: collector_test.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月10日 星期五 20时31分58秒
 ************************************************************************/

#include <iostream>
#include <functional>

#include "boost/thread.hpp"
#include "boost/functional.hpp"
#include "log4cxx/propertyconfigurator.h"

#include "KNN/collector.h"

void test(void)
{
	std::cout << "hello world" << std::endl;
}

int main(int argc, char ** argv)
{
	log4cxx::PropertyConfigurator::configure("../comm/log4cxx.properties");
	kelp::Collector collector("hah");
//	boost::thread first(boost::mem_fun(&kelp::Collector::Start),collector);
	boost::thread first(boost::bind(&kelp::Collector::Start,&collector));

	std::vector<kelp::MetaData> temp;
	std::vector<kelp::MetaData>::iterator iter;

	boost::this_thread::sleep_for(boost::chrono::seconds(10));
	temp = collector.PopSendData();
	std::cout << "pop No.1 ==========================================" << std::endl;
	for(iter=temp.begin();iter!=temp.end();++iter)
		std::cout << (*iter).bson << std::endl;
	std::cout << "end pop No.1 ==========================================" << std::endl;

	boost::this_thread::sleep_for(boost::chrono::seconds(10));
	temp = collector.PopSendData();
	std::cout << "pop No.2 ==========================================" << std::endl;
	for(iter=temp.begin();iter!=temp.end();++iter)
		std::cout << (*iter).bson << std::endl;
	std::cout << "end pop No.2 ==========================================" << std::endl;
	
	first.join();

	return 0;
}
