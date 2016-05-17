/*************************************************************************
	> File Name: tcp_server.cpp
	> Author: MC
    > mail: machaolyn@163.com
	> Created Time: 2015年03月30日 星期一 17时10分11秒
 ************************************************************************/

#include <iostream>

#include "mongo/bson/bson.h"
#include "../comm/tcp.h"

int main(int argc ,char * argv[])
{
	ACE_INET_Addr tcp_addr(3000);
	kelp::Tcp server(tcp_addr);
	server.AcceptClient();        

	while(true)
	{
	char buf[1024]={};
	char buf1[1024]="request";
	server.Recv(buf,1024);
	mongo::BSONObj bo(buf);
	std::cout<<"recv: "<<bo<<std::endl;
	server.Send(buf1,1024);
	std::cout<<"send: "<<buf1<<std::endl;
	
	}



	return 0;
}
