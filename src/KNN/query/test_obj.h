/*************************************************************************
	> File Name: test_interface.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月25日 星期三 20时03分58秒
 ************************************************************************/

#ifndef KELP_KNN_TEST_OBJ_H_
#define KELP_KNN_TEST_OBJ_H_

#include <Ice/Ice.h>
#include <string>

#include "test.h"
#include "comm/module_info.h"

kelp::QueryObj HandlerCallback(void);

kelp::QueryInfo QueryModule = {
	HandlerCallback
};

namespace kelp
{
class TestObj : public TestInterface
{
public:
	TestObj();
	virtual std::string Foo(const Ice::Current&);
};
};

#endif
