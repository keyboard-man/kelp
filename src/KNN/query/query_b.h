/*************************************************************************
	> File Name: query_b.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月30日 星期一 11时05分21秒
 ************************************************************************/

#ifndef KELP_QUERY_QUERY_B_H_
#define KELP_QUERY_QUERY_B_H_

#include <Ice/Ice.h>
#include <string>

#include "base_query_interface.h"
#include "comm/module_info.h"

kelp::QueryObj HandlerCallback(void);

kelp::QueryInfo QueryModule = {
	HandlerCallback
};

namespace kelp
{
class QueryB : public QueryInterface
{
public:
	QueryB();
	virtual BinData Foo(const std::string& str, const Ice::Current&);
};
};

#endif
