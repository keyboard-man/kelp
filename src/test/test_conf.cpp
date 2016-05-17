/*************************************************************************
	> File Name: test_conf.cpp
	> Author: MC
    > mail: machaolyn@163.com
	> Created Time: 2015年04月02日 星期四 14时42分21秒
 ************************************************************************/

#include <iostream>

#include "../comm/conf_loader.h"
int main()
{
//	kelp::ConfLoader config("knn.conf");
//	kelp::Globals ret_globals;
//	ret_globals=config.LoadGlobals();
//
//	std::cout<<ret_globals.del_host_max<<std::endl;
//	std::cout<<ret_globals.cleanup_throshold<<std::endl;
//	std::cout<<ret_globals.mute<<std::endl;
/*//
	kelp::ConfLoader conf("/home/machao/knn.conf");
	kelp::Modules modules;
	modules=conf.LoadModules();
	std::cout<<modules[0].path<<std::endl;
	std::cout<<modules[0].argc<<std::endl;
	std::cout<<*modules[0].argv<<std::endl;
	std::cout<<"name"<<modules[0].name<<std::endl;
	std::cout<<"enable"<<modules[0].enable<<std::endl;
	std::cout<<"path"<<modules[0].path<<std::endl;
	std::cout<<"argc"<<modules[0].argc<<std::endl;
	std::cout<<*modules[0].argv<<std::endl;


	kelp::CollectionGroups back;
	back=conf.LoadCollectionGroups();
	std::cout<<back[0].collection_every<<std::endl;
	std::cout<<back[0].collection_once<<std::endl;
	std::cout<<back[0].time_threshold<<std::endl;
	std::cout<<back[0].metrics[0].name<<std::endl;
	std::cout<<back[0].modules[0].path<<std::endl;
	std::cout<<back[0].metrics[0].name<<std::endl;


	kelp::UDPSendChannel udp_send_channel;
	udp_send_channel=conf.LoadUDPSendChannel();
	std::cout<<udp_send_channel.ip<<std::endl;
	
	kelp::TCPAcceptChannel tcp_accept_channel;
	tcp_accept_channel=conf.LoadTCPAcceptChannel();
	std::cout<<tcp_accept_channel.port<<std::endl;

	kelp::Globals globals;
	globals=conf.LoadGlobals();
	std::cout<<globals.mute<<std::endl;

	kelp::Cluster cluster;
	cluster=conf.LoadCluster();
	std::cout<<cluster.name<<std::endl;

	kelp::UDPRecvChannel udp_recv_channel;
	udp_recv_channel=conf.LoadUDPRecvChannel();
	std::cout<<udp_recv_channel.mcast_join<<std::endl;

	kelp::Host host;
	host=conf.LoadHost();
	std::cout<<host.location<<std::endl;
*/
	kelp::ConfLoader conf("kcn.conf");
//	kelp::DataSources data_sources;
//	data_sources=conf.LoadDataSources();
//	std::vector<kelp::DataSource>::iterator s1=data_sources.begin();
//	for(;s1!=data_sources.end();s1++)
//	{
//		std::cout<<(*s1).name<<std::endl;
//		std::cout<<(*s1).period<<std::endl;
//		std::vector<std::string>::iterator s2=(*s1).node_list.begin();
//		for(;s2!=(*s1).node_list.end();++s2)
//			std::cout<<(*s2)<<std::endl;
//	}
//
/*	kelp::DBModules db_modules;
	db_modules=conf.LoadDBModules();
	std::vector<kelp::DBModule>::iterator s1=db_modules.begin();
	for(;s1!=db_modules.end();s1++)
	{
		std::cout<<(*s1).name<<std::endl;
		std::cout<<(*s1).enable<<std::endl;
		std::cout<<(*s1).argc<<std::endl;
		std::cout<<(*s1).argv[0]<<std::endl;
		std::cout<<(*s1).path<<std::endl;
	}
*/
	kelp::Stores stores;
	stores=conf.LoadStores();
	std::vector<kelp::Store>::iterator s1=stores.begin();
	for(;s1!=stores.end();s1++)
	{
		std::cout<<(*s1).key_name<<std::endl;
		int j=(*s1).module_name.size();
		std::cout<<j<<std::endl;
		for(int m=0;m<j;m++)
		{
			std::cout<<(*s1).module_name[m]<<std::endl;
		}
	}

//	std::map<std::string,std::string> m=conf.LoadGridName();
//	std::cout<<m["gridname"]<<std::endl;




	return 0;
}
