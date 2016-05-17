/*************************************************************************
	> File Name: mcast_recv.cpp
	> Author: MC
    > mail: machaolyn@163.com
	> Created Time: 2015年03月26日 星期四 20时41分02秒
 ************************************************************************/


#include <iostream>
#include <string>

#include "ace/SOCK_Dgram_Mcast.h"
#include "mongo/bson/bson.h"
#include "ace/INET_Addr.h"

#include "../comm/udp.h"

int main(int  argc,char * argv[] )
{
	ACE_INET_Addr addr(3000,"239.192.2.3");
	kelp::Udp mcast(addr,5);
	char buf[1024]={};
	mcast.Recv(buf,1024);
	mongo::BSONObj bo(buf);
	std::cout<<"recv: "<<bo<<std::endl;
	return 0;
}
