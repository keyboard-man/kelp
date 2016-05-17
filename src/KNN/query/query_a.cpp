/*************************************************************************
	> File Name: query_a.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月30日 星期一 10时48分22秒
 ************************************************************************/

#include "query_a.h"

namespace kelp
{
QueryA::QueryA()
{
	;
}

BinData QueryA::Foo(const std::string& str, const Ice::Current&)
{
	//do something real
	const char* msg = "hello world";
	std::vector<unsigned char> bindata(msg, msg+strlen(msg));

	return bindata;
}
}

kelp::QueryObj HandlerCallback(void)
{
	Ice::ObjectPtr object = new kelp::QueryA;
	kelp::QueryObj result;
	result.name = "query_a";
	result.object = object;

	return result;
}
