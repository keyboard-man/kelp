/*************************************************************************
	> File Name: dbmodules_loader.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月28日 星期二 21时45分09秒

	数据库处理模块的加载者
 ************************************************************************/

#ifndef KELP_KCN_DBMODULES_LOADER_H_
#define KELP_KCN_DBMODULES_LOADER_H_

#include <stdexcept>
#include <dlfcn.h>
#include <iostream>
#include <vector>
#include "log4cxx/logger.h"

#include "comm/config_data.h"
#include "comm/module_info.h"

namespace kelp{
class DBModulesLoader
{
public:
	DBModulesLoader();
	DBModulesLoader(DBModules&);
	void InitModules(DBModules&);
	void InitModule(DBModule&);
	void CleanModules(DBModules&);
	void CleanModule(DBModule&);
private:
	log4cxx::LoggerPtr log_;
};
};

#endif
