/*************************************************************************
	> File Name: query_service.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年11月27日 星期五 15时29分44秒
 ************************************************************************/

#ifndef KELP_KNN_QUERY_SERVICE_H_
#define KELP_KNN_QUERY_SERVICE_H_

#include <string>
#include <ostream>
#include <list>
#include <log4cxx/logger.h>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <dlfcn.h>
#include <node.h>

#include "comm/module_info.h"

namespace kelp
{
class QueryService
{
public:
	QueryService(ENM::Node&,const std::string&);
private:
	void GetFile();
	void AddService();

	ENM::Node& node_;
	log4cxx::LoggerPtr log_;
	std::list<std::string> file_list_;
	boost::filesystem::path path_;

};
}

#endif
