OBJ=async_timer.o 
INCLUDE=-I/usr/local/include/coral/
LIBS=-lboost_thread

all:$(OBJ)

async_timer.o:async_timer.cpp async_timer.h
	g++ -c async_timer.cpp -g $(INCLUDE)

clean:
	rm -f $(OBJ)
