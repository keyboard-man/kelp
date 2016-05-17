#polymer_test:polymer_test.o ../KNN/cluster_polymer.o ../KSN/grid_polymer.o ../KCN/top_grid_polymer.o
#	g++ polymer_test.o ../KNN/cluster_polymer.o ../KSN/grid_polymer.o ../KCN/top_grid_polymer.o -lmongoclient -lboost_system -lboost_thread -o polymer_test -llog4cxx
#polymer_test.o:polymer_test.cpp
#	g++ -c polymer_test.cpp -o polymer_test.o -I/home/vimer/Kelp/src/ -g -llog4cxx
#../KNN/cluster_polymer.o:../KNN/cluster_polymer.cpp ../KNN/cluster_polymer.h
#	g++ -c ../KNN/cluster_polymer.cpp -o ../KNN/cluster_polymer.o -I/home/vimer/Kelp/src/ -g -llog4cxx
#../KSN/grid_polymer.o:../KSN/grid_polymer.cpp ../KSN/grid_polymer.h
#	g++ -c ../KSN/grid_polymer.cpp -o ../KSN/grid_polymer.o -I/home/vimer/Kelp/src/ -g -llog4cxx
#../KCN/top_grid_polymer.o:../KCN/top_grid_polymer.cpp ../KCN/top_grid_polymer.h
#	g++ -c ../KCN/top_grid_polymer.cpp -o ../KCN/top_grid_polymer.o -I/home/vimer/Kelp/src/ -g -llog4cxx
#

#collector_test:collector_test.o ../KNN/collector.o ../KNN/modules_loader.o example.so
#	g++ collector_test.o ../KNN/collector.o ../KNN/modules_loader.o -lmongoclient -lboost_thread -lboost_system -lpthread -ldl -llog4cxx -o collector_test
#collector_test.o:collector_test.cpp
#	g++ -c collector_test.cpp -I/home/vimer/Kelp/src/ -g -lboost_thread -lboost_system -lpthread -lmongoclient -llog4cxx
#../KNN/collector.o:../KNN/collector.cpp
#	g++ -c ../KNN/collector.cpp -I/home/vimer/Kelp/src -g -lboost_thread -lboost_system -lpthread -lmongoclient -llog4cxx -o ../KNN/collector.o
#../KNN/modules_loader.o:../KNN/modules_loader.cpp
#	g++ -c ../KNN/modules_loader.cpp -I/home/vimer/Kelp/src -g -lboost_thread -lboost_system -lpthread -lmongoclient -llog4cxx -o ../KNN/modules_loader.o
#example.so:example_module.cpp
#	g++ example_module.cpp -shared -fPIC -I/home/vimer/Kelp/src -o example.so -lmongoclient
#

send_recv_test:send_recv_test.o ../KNN/sender.o ../KNN/receiver.o example.so ../KNN/collector.o ../KNN/cluster_polymer.o ../comm/conf_loader.o ../comm/udp.o ../comm/tcp.o ../KNN/modules_loader.o
	g++  send_recv_test.o ../KNN/sender.o ../KNN/receiver.o ../KNN/collector.o ../KNN/cluster_polymer.o ../comm/conf_loader.o ../comm/tcp.o ../comm/udp.o ../KNN/modules_loader.o -lmongoclient -lboost_thread -lboost_system -lboost_regex -lpthread -ldl -llog4cxx -lACE -o send_recv_test
send_recv_test.o:send_recv_test.cpp
	g++ -c send_recv_test.cpp -I/home/machao/Kelp/src/ -g -lboost_thread -lboost_system -lpthread -lmongoclient -llog4cxx
../KNN/sender.o:../KNN/sender.cpp
	g++ -c ../KNN/sender.cpp -o ../KNN/sender.o -g -I/home/machao/Kelp/src/ -lboost_thread -lboost_system -lpthread -lmongoclient -llog4cxx -lACE
../KNN/receiver.o:../KNN/receiver.cpp
	g++ -c ../KNN/receiver.cpp -o ../KNN/receiver.o -g -I/home/machao/Kelp/src/ -lboost_thread -lboost_system -lpthread -lmongoclient -llog4cxx -lACE
example.so:example_module.cpp
	g++ example_module.cpp -shared -fPIC -I/home/machao/Kelp/src -o example.so -lmongoclient
../KNN/collector.o:../KNN/collector.cpp
	g++ -c ../KNN/collector.cpp -I/home/machao/Kelp/src -g -lboost_thread -lboost_system -lpthread -lmongoclient -llog4cxx -o ../KNN/collector.o -Wcpp
../KNN/cluster_polymer.o:../KNN/cluster_polymer.cpp ../KNN/cluster_polymer.h
	g++ -c ../KNN/cluster_polymer.cpp -o ../KNN/cluster_polymer.o -I/home/machao/Kelp/src/ -g -llog4cxx
../comm/conf_loader.o:../comm/conf_loader.cpp
	g++ -c ../comm/conf_loader.cpp -o ../comm/conf_loader.o -I/home/machao/Kelp/src/ -g -llog4cxx -lboost_regex
../comm/udp.o:../comm/udp.cpp
	g++ ../comm/udp.cpp -c -o ../comm/udp.o -I/home/machao/Kelp/src -g -llog4cxx -lACE
../comm/tcp.o:../comm/tcp.cpp
	g++ ../comm/tcp.cpp -c -o ../comm/tcp.o -I/home/machao/Kelp/src -g -llog4cxx -lACE
../KNN/modules_loader.o:../KNN/modules_loader.cpp
	g++ -c ../KNN/modules_loader.cpp -I/home/machao/Kelp/src -g -lboost_thread -lboost_system -lpthread -lmongoclient -llog4cxx -o ../KNN/modules_loader.o
rrd_test:../module/rrd_operator.cpp ../module/rrd_operator.h
	g++ ../module/rrd_operator.cpp -I/home/vimer/Kelp/include/ -I/home/vimer/Kelp/src /usr/lib/librrd.a -o rrd_test -lrrd -lgmodule-2.0 -llog4cxx -lboost_thread -lboost_system
