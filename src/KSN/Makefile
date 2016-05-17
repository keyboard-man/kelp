LIB=-lmongoclient -lboost_thread -lboost_system -lboost_regex -lpthread -lACE -llog4cxx -lIce -lIceUtil -lENM -ldl -ljsoncpp -luuid
INCLUDE=-I/home/vimer/Kelp/src -I/usr/local/include/coral/ -g -std=c++11
OBJ=ksn_poller.o sender.o collector.o ksn.o ../comm/async_timer.o conf_loader.o 
EXE=/home/vimer/Kelp/bin/ksn

$(EXE):$(OBJ)
	g++ $(OBJ) $(LIB) -o $(EXE) 
ksn.o:ksn.cpp
	g++ -c ksn.cpp $(INCLUDE)
ksn_poller.o:ksn_poller.cpp ksn_poller.h
	g++ -c ksn_poller.cpp $(INCLUDE)
sender.o:sender.cpp sender.h
	g++ -c sender.cpp $(INCLUDE)
collector.o:collector.cpp collector.h
	g++ -c collector.cpp $(INCLUDE)
../comm/async_timer.o:../comm/async_timer.cpp ../comm/async_timer.h
	cd ../comm/ && make
conf_loader.o:conf_loader.cpp conf_loader.h
	g++ -c conf_loader.cpp $(INCLUDE)

clean:
	rm -rf $(OBJ) $(EXE)
