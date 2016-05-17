/*************************************************************************
	> File Name: send_recv_test.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月21日 星期二 09时25分20秒
 ************************************************************************/

#include <iostream>
#include <cstdlib>

#include "boost/thread.hpp"
#include "log4cxx/propertyconfigurator.h"

#include "KNN/sender.h"
#include "KNN/receiver.h"
//void send_data(kelp::Tcp & tcp, void * buf)
//{
//	tcp.Send(buf,1024);
//}
//
int main(int argc,char** argv)
{
	log4cxx::PropertyConfigurator::configure("../comm/log4cxx.properties");
	const std::string knn = "/home/machao/knn.conf";
	try{
		kelp::Sender sender(knn);
		kelp::Receiver receiver(knn);

		boost::thread send(boost::bind(&kelp::Sender::Start,&sender));
		boost::thread recv(boost::bind(&kelp::Receiver::Start,&receiver));
		boost::this_thread::sleep_for(boost::chrono::seconds(15));
		int i;
		char buf1[1024]="request";
		char buf2[1024]={};
		ACE_INET_Addr addr(30034,"127.0.0.1");
		kelp::Tcp tcp(addr);
		tcp.ConnectServer();
//		while(true)
//		{ 
//			boost::thread send_tcp(boost::bind(&send_data,tcp,buf1));
//			boost::this_thread::sleep_for(boost::chrono::seconds(10));
//		double i;
//		for(i=0;i<5000000000;i++)
//		{
//		}
//		while(true)
//		{
//		double i;
//		for(i=0;i<500000000;i++)
//		{
//		}
		for(i=0;i<10;i++)
		{
		tcp.Send(buf1,sizeof(buf1));
		tcp.Recv(buf2,sizeof(buf1));
		mongo::BSONObj bo(buf2);
		std::cout <<"================================"<<std::endl;
		std::cout<<bo<<std::endl;
		boost::this_thread::sleep_for(boost::chrono::seconds(10));
		}
		send.join();
		recv.join();
	}
	catch(std::runtime_error& e)
	{
		std::cout << "exception caught: " << e.what() << std::endl;
		exit(1);
	}

	return 0;
}
