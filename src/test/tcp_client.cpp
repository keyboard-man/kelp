/*************************************************************************
	> File Name: tcp_client.cpp
	> Author: MC
    > mail: machaolyn@163.com
	> Created Time: 2015年03月30日 星期一 18时46分10秒
 ************************************************************************/

#include <iostream>

#include "ace/INET_Addr.h"
#include "mongo/bson/bson.h"

#include "../comm/tcp.h"

int main(int argc ,char * argv[])
{
//	log4cxx::PropertyConfigurator::configure(g_log_path);
	ACE_INET_Addr tcp_addr(3000,"127.0.0.1");
	kelp::Tcp client(tcp_addr);

	client.ConnectServer();
	mongo::BSONObj bo =BSON("name"<<"Ma Chao"<<"age"<<"23");
	char  buf[1024]={};
	int i;
	for(i=0;i<10;i++)
	{
	client.Send(bo.objdata(),bo.objsize());
	std::cout<<"send: \t"<<bo<<std::endl;
	client.Recv(buf,1024);

//	mongo::BSONObj b1(buf);
	std::cout<<"recv: \t"<<buf<<std::endl;
	}


	return 0;
}


