/*************************************************************************
	> File Name: query_a.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月30日 星期一 10时40分46秒
 ************************************************************************/

#ifndef KELP_QUERY_QUERY_A_H_
#define KELP_QUERY_QUERY_A_H_

#include <Ice/Ice.h>
#include <mongo/bson/bson.h>
#include <string>

#include "base_query_interface.h"
#include "comm/module_info.h"

kelp::QueryObj HandlerCallback(void);

kelp::QueryInfo QueryModule = {
	HandlerCallback
};

namespace kelp
{
class QueryA : public QueryInterface
{
public:
	QueryA();
	virtual BinData Foo(const std::string& str, const Ice::Current&);
};
};

#endif
