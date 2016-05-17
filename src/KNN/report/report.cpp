/*************************************************************************
	> File Name: report.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年12月02日 星期三 11时23分06秒
 ************************************************************************/

#include <boost/thread.hpp>

#include "KNN/reporter_manager.h"

extern "C" void Launch(kelp::Reporter*);

void Report(kelp::Reporter* report)
{
	while(true)
	{
		int v = rand() % 60;
		boost::this_thread::sleep_for(boost::chrono::seconds(v));
		char* str = "ALERT!! NO NECESSARY MEMORY!!";
		ACE_Message_Block* msg = new ACE_Message_Block(str,sizeof(str));
		report->putq(msg);
		std::cout << "ALERT!! NO NECESSARY MEMORY!!" << std::endl;
	}
}

void Launch(kelp::Reporter* report)
{
	boost::thread th(Report,report);

	th.detach();
}
