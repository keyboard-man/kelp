/*************************************************************************
	> File Name: query_b.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月30日 星期一 11时06分36秒
 ************************************************************************/

#include "query_b.h"

namespace kelp
{
QueryB::QueryB()
{
	;
}

BinData QueryB::Foo(const std::string& str, const Ice::Current&)
{
	//do something real
	const char* msg = "Use ICE !";
	BinData buf(msg, msg+strlen(msg));
	return buf;
}
}

kelp::QueryObj HandlerCallback(void)
{
	Ice::ObjectPtr object = new kelp::QueryB;
	kelp::QueryObj result;
	result.name = "query_b";
	result.object = object;

	return result;
}
