LIB=-lmongoclient -lboost_thread -lboost_system -lboost_regex -lpthread -lACE -llog4cxx -lIce -lIceUtil -lENM -ldl -ljsoncpp -luuid
INCLUDE=-I/home/vimer/Kelp/src/ -I/usr/local/include/coral/ -g -std=c++11 -I./
OBJ=collector.o processer.o dbmodules_loader.o kcn.o kcn_poller.o ../comm/async_timer.o conf_loader.o report_server.o query_server.o base_query_interface.o web2kcn.o cmd2kcn.o
#OBJ=collector.o processer.o dbmodules_loader.o kcn.o kcn_poller.o image_collector.o image_poller.o ../comm/async_timer.o conf_loader.o report_server.o
EXE=/home/vimer/Kelp/bin/kcn

$(EXE):$(OBJ)
	g++ $(OBJ) $(LIB) -o $(EXE) 
kcn.o:kcn.cpp
	g++ -c kcn.cpp $(INCLUDE)
kcn_poller.o:kcn_poller.cpp kcn_poller.h
	g++ -c kcn_poller.cpp $(INCLUDE)
collector.o:collector.cpp collector.h
	g++ -c collector.cpp $(INCLUDE)
processer.o:processer.cpp processer.h
	g++ -c processer.cpp $(INCLUDE)
dbmodules_loader.o:dbmodules_loader.cpp dbmodules_loader.h
	g++ -c dbmodules_loader.cpp $(INCLUDE)
image_collector.o:image_collector.cpp image_collector.h
	g++ -c image_collector.cpp $(INCLUDE)
image_poller.o:image_poller.cpp image_poller.h
	g++ -c image_poller.cpp $(INCLUDE)
../comm/async_timer.o:../comm/async_timer.cpp ../comm/async_timer.h
	cd ../comm/ && make
conf_loader.o:conf_loader.cpp conf_loader.h
	g++ -c conf_loader.cpp $(INCLUDE)
report_server.o:report_server.cpp report_server.h
	g++ -c report_server.cpp $(INCLUDE)
query_server.o:query_server.cpp query_server.h base_query_interface.h web2kcn.h cmd2kcn.h
	g++ -c query_server.cpp $(INCLUDE)
base_query_interface.o:base_query_interface.cpp base_query_interface.h
	g++ -c base_query_interface.cpp $(INCLUDE)
web2kcn.o:web2kcn.cpp web2kcn.h
	g++ -c $(INCLUDE) web2kcn.cpp
cmd2kcn.o:cmd2kcn.cpp cmd2kcn.h
	g++ -c $(INCLUDE) cmd2kcn.cpp
base_query_interface.cpp:base_query_interface.ice
	slice2cpp base_query_interface.ice
base_query_interface.h:base_query_interface.ice
	slice2cpp base_query_interface.ice
web2kcn.cpp:web2kcn.ice
	slice2cpp web2kcn.ice
web2kcn.h:web2kcn.ice
	slice2cpp web2kcn.ice
cmd2kcn.cpp:cmd2kcn.ice
	slice2cpp cmd2kcn.ice
cmd2kcn.h:cmd2kcn.ice
	slice2cpp cmd2kcn.ice

clean:
	rm -rf $(OBJ) $(EXE)
