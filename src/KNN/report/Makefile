LIB=-lboost_thread -lboost_system -lACE -shared
INCLUDE=-I./ -I/home/vimer/Kelp/src/ -I/usr/local/include/coral/ -fPIC -std=c++11

all:report.so

report.so:report.o
	g++ $(LIB) -o report.so report.o
report.o:report.cpp ../reporter_manager.h
	g++ -c $(INCLUDE) report.cpp


clean:
	rm -rf *.o *.so
