/*************************************************************************
	> File Name: load_modules.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年03月27日 星期五 17时23分50秒

	模块加载者，用于加载用户自行编写的轮询数据收集模块
 ************************************************************************/

#ifndef KELP_KNN_MODULES_LOADER_H_
#define KELP_KNN_MODULES_LOADER_H_

#include <stdexcept>
#include <dlfcn.h>

#include "log4cxx/logger.h"

#include "comm/config_data.h"
#include "comm/module_info.h"

namespace kelp{
class ModulesLoader
{
public:
	ModulesLoader();
	ModulesLoader(Modules&);
	void InitModules(Modules&);
	void InitModule(Module&);
	void CleanModules(Modules&);
	void CleanModule(Module&);

private:
	log4cxx::LoggerPtr log_;
};
};

#endif
