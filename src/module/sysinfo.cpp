/*************************************************************************
	> File Name: sysinfo.cpp
	> Author: zhuce
    > mail: zc619340855@163.com
	> Created Time: 2015年07月10日 星期五 10时26分25秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>

#include "mongo/bson/bson.h"

#include "comm/module_info.h"

int InitCallback(int,char **);
void HandlerCallback(char**,int&);
int CleanupCallback(void);
int getlocalip(char*);

kelp::ModuleInfo system_info = 
{
	InitCallback,
	HandlerCallback,
	CleanupCallback
};

int InitCallback(int argc, char* argv[])
{
	std::cout << "collect sysinfo" << std::endl;
	return 0;
}

void HandlerCallback(char **buf,int &size)
{
	struct sysinfo* info = new struct sysinfo;
	char ip[20];
	sysinfo(info);
	getlocalip(ip);

	mongo::BSONObjBuilder builder;
	builder.append("heartbeat",(long long)time(NULL));
	builder.append("sys_info",BSON("time"<<(long long)time(NULL)<<"total_ram"<<
				   (long long)info->totalram));
	builder.append("sys_info",BSON("time"<<(long long)time(NULL)<<"shared_ram"<<(long long)info->sharedram));
	builder.append("sys_info",BSON("time"<<(long long)time(NULL)<<"total_swap"<<(long long)info->totalswap));
	builder.append("sys_info",BSON("time"<<(long long)time(NULL)<<"IP"<<ip));
	mongo::BSONObj obj = builder.obj();

	size = obj.objsize();
	*buf = new char[size]();
	memcpy(*buf,obj.objdata(),size);
}

int CleanupCallback(void)
{
	return 0;
}

int getlocalip(char* outip)
{
	int i = 0;
	int sockfd;
	struct ifconf ifconf;
	char buf[512];
	struct ifreq * ifreq;
	char * ip;

	ifconf.ifc_len = 512;
	ifconf.ifc_buf = buf;

	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		return -1;
	}
	ioctl(sockfd,SIOCGIFCONF,&ifconf);
	close(sockfd);

	ifreq = (struct ifreq*)buf;

	for(i=(ifconf.ifc_len/sizeof(struct ifreq));i>0;i--)
	{
		ip = inet_ntoa(((struct sockaddr_in *)&(ifreq->ifr_addr))->sin_addr);
		if(strcmp(ip,"127.0.0.1")==0)
		{
			ifreq ++;
			continue;
		}
		strcpy(outip,ip);
		return 0;
	}

	return -1;
}
