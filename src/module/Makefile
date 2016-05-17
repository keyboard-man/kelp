INCLUDE=-I/home/zhuce/workspace/kelp/src/
LIBS=-pthread -lmongoclient -lboost_thread -lboost_system
FLAGS=-shared -fPIC
libmongo_module.so:mongo_module.cpp  mongo_module.h mongo_operator.cpp mongo_operator.h ../comm/module_info.h
	g++ mongo_module.cpp mongo_operator.cpp -shared -fPIC -I/home/vimer/Kelp/src -o mongo_module.so -lmongoclient -fpermissive
image_module.so:image_module.cpp ../comm/image_metadata.h
	g++ image_module.cpp -o image_module.so $(INCLUDE) $(FLAGS) -llog4cxx
librrd_module.so:rrd_module.cpp rrd_module.h rrd_operator.cpp rrd_operator.h ../comm/module_info.h
	g++ rrd_module.cpp  rrd_operator.cpp -shared -fPIC -I/home/zhuce/workspace/kelp/include/ -I/home/zhuce/workspace/kelp/src /usr/lib/librrd.a -o ../../lib/rrd_module.so -lmongoclient -lrrd -lgmodule-2.0 -fpermissive  
example.so:example_module.cpp
	g++ example_module.cpp -o example.so $(INCLUDE) $(LIBS) $(FLAGS)
rrd_operator.o:rrd_operator.cpp rrd_operator.h
	g++ -c rrd_operator.cpp -I/home/zhuce/kelp/include  -lmongoclient -lrrd -lgmodule-2.0 -llog4cxx
sysinfo.so:sysinfo.cpp
	g++ sysinfo.cpp -o sysinfo.so $(INCLUDE) $(LIBS) $(FLAGS)
