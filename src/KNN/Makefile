LIB=-lmongoclient -lboost_thread -lboost_system -lboost_regex -lboost_filesystem -lpthread -lACE -llog4cxx -lIce -lIceUtil -lENM -ldl -ljsoncpp -luuid  
INCLUDE=-I/home/vimer/Kelp/src/ -I/usr/local/include/coral/ -g -std=c++11
OBJ=cluster_receiver.o cluster_sender.o conf_loader.o data_collector.o data_sender.o knn_poller.o knn.o modules_loader.o ../comm/async_timer.o query_service.o reporter_manager.o
EXE=/home/vimer/Kelp/bin/knn

$(EXE):$(OBJ)
	g++ $(OBJ) $(LIB) -o $(EXE)
knn.o:knn.cpp
	g++ -c knn.cpp $(INCLUDE)
data_collector.o:data_collector.cpp data_collector.h
	g++ -c data_collector.cpp $(INCLUDE)
data_sender.o:data_sender.cpp data_sender.h
	g++ -c data_sender.cpp $(INCLUDE)
knn_poller.o:knn_poller.cpp knn_poller.h
	g++ -c knn_poller.cpp $(INCLUDE)
cluster_receiver.o:cluster_receiver.cpp cluster_receiver.h
	g++ -c cluster_receiver.cpp $(INCLUDE)
cluster_sender.o:cluster_sender.cpp cluster_sender.h
	g++ -c cluster_sender.cpp $(INCLUDE)
conf_loader.o:conf_loader.cpp conf_loader.h
	g++ -c conf_loader.cpp $(INCLUDE)
modules_loader.o:modules_loader.cpp modules_loader.h
	g++ -c modules_loader.cpp $(INCLUDE)
../comm/async_timer.o:../comm/async_timer.cpp ../comm/async_timer.h
	cd ../comm/ && make 
query_service.o:query_service.cpp query_service.h
	g++ -c query_service.cpp $(INCLUDE)
reporter_manager.o:reporter_manager.cpp reporter_manager.h
	g++ -c reporter_manager.cpp $(INCLUDE)

clean:
	rm -rf $(OBJ) $(EXE)
