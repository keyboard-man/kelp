/*************************************************************************
	> File Name: test_obj.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月25日 星期三 20时11分37秒
 ************************************************************************/

#include "test_obj.h"

namespace kelp
{
TestObj::TestObj()
{
	;
}

std::string TestObj::Foo(const Ice::Current&)
{
	return "test successfully!";
}
}

kelp::QueryObj HandlerCallback(void)
{
	Ice::ObjectPtr object = new kelp::TestObj;
	kelp::QueryObj result;
	result.name = "test";
	result.object = object;
	return result;
}
