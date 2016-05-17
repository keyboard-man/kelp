INCLUDE=-I/home/vimer/Kelp/src/ -I./
LIBS=-lIce -lIceUtil
CXXFLAG=-fPIC -g -std=c++11
Test_OBJ=test.o test_obj.o
OBJ=base_query_interface.o query_a.o
SO=test.so query_a.so query_b.so

all:$(SO)

test.so:$(Test_OBJ)
	g++ $(Test_OBJ) $(LIB) -shared -o test.so
test.o:test.cpp test.h
	g++ -c test.cpp $(INCLUDE) $(CXXFLAG)
test_obj.o:test_obj.cpp test_obj.h
	g++ -c test_obj.cpp $(INCLUDE) $(CXXFLAG)

query_a.so:base_query_interface.o query_a.o
	g++ base_query_interface.o query_a.o $(LIB) $(CXXFLAG) -o query_a.so -shared
query_a.o:query_a.cpp query_a.h
	g++ -c query_a.cpp $(INCLUDE) $(CXXFLAG)

query_b.so:base_query_interface.o query_b.o
	g++ base_query_interface.o query_b.o $(LIB) $(CXXFLAG) -o query_b.so -shared
query_b.o:query_b.cpp query_b.h
	g++ -c query_b.cpp $(INCLUDE) $(CXXFLAG)

base_query_interface.o:base_query_interface.cpp base_query_interface.h
	g++ -c base_query_interface.cpp $(INCLUDE) $(CXXFLAG)
base_query_interface.cpp:base_query_interface.ice
	slice2cpp base_query_interface.ice

clean:
	rm -rf *.o *.so
