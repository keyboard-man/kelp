/*************************************************************************
	> File Name: mcast_recv.cpp
	> Author: MC
    > mail: machaolyn@163.com
	> Created Time: 2015年03月26日 星期四 20时19分54秒
 ************************************************************************/

#include <iostream>
#include <string>

#include "ace/INET_Addr.h"
#include "mongo/bson/bson.h"

#include "../comm/udp.h"

int main(int argc,char * argv[])
{
	ACE_INET_Addr mcast_addr(3000,"239.192.2.3");
	kelp::Udp mcast(mcast_addr,5);
	
	mongo::BSONObj bson=BSON("name"<<"Ma Chao"<<"age"<<"23");
	mcast.Send(bson.objdata(),bson.objsize());
	std::cout<<"send: "<<bson<<std::endl;
	return 0;
}

	
	
