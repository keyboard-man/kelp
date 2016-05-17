/*************************************************************************
	> File Name: dbmodules_loader.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年04月28日 星期二 21时53分25秒

	数据库处理模块的加载者
 ************************************************************************/

#include "dbmodules_loader.h"

namespace kelp{
DBModulesLoader::DBModulesLoader()
{
	//init the logger
	log_ = log4cxx::Logger::getLogger("dbmodules_loader");
}

DBModulesLoader::DBModulesLoader(DBModules& modules)
{
	log_ = log4cxx::Logger::getLogger("dbmodules_loader");
	//init the modules
	InitModules(modules);
}

void DBModulesLoader::InitModules(DBModules& modules)
{
	std::vector<DBModule>::iterator iter = modules.begin();
	void* handler;
	DBModuleInfo* module_info;

	for(;iter!=modules.end();++iter)
	{
		if(iter->enable)
		{
			(*iter).dl_handler = NULL;
			(*iter).init = NULL;
			(*iter).handler = NULL;
			(*iter).cleanup = NULL;

			LOG4CXX_DEBUG(log_,iter->path);
			handler = dlopen(iter->path.c_str(),RTLD_LAZY);

			if(!handler)
			{
				//加载模块失败
				LOG4CXX_WARN(log_,dlerror());
				continue;
			}
			dlerror();

			module_info = (DBModuleInfo *) dlsym(handler,(*iter).module_name.c_str());
			const char* dlsym_error = dlerror();
			if(dlsym_error)
			{
				//加载ModuleInfo失败
				std::string err = "Can not find ModuleInfo in " + iter->module_name;
				dlclose(handler);
				//TODO:log
				LOG4CXX_WARN(log_,err);
				continue;
			}
			
			(*iter).dl_handler = handler;
			(*iter).init = *module_info->init;
			(*iter).handler = *module_info->handler;
			(*iter).cleanup = *module_info->cleanup;

			(*iter).init((*iter).params);
		}
	}
}

void DBModulesLoader::InitModule(DBModule& module)
{
	void* handler;
	DBModuleInfo* module_info;
	
	if(module.enable)
	{
		module.dl_handler = NULL;
		module.init = NULL;
		module.handler = NULL;
		module.cleanup = NULL;

		handler = dlopen(module.path.c_str(),RTLD_LAZY);
		if(!handler)
		{
			//load failed
			std::string err = "Can not load so" + module.module_name;
			//TODO:log
			LOG4CXX_WARN(log_,err);
			return ;
		}
		dlerror();

		module_info = (DBModuleInfo *)dlsym(handler,module.module_name.c_str());
		const char* dlsym_err = dlerror();
		if(dlsym_err)
		{
			//load failed
			std::string err = "Can not find ModuleInfo in " + module.module_name;
			dlclose(handler);
			//log
			LOG4CXX_WARN(log_,err);
			return ;
		}

		module.dl_handler = handler;
		module.init = *module_info->init;
		module.handler = *module_info->handler;
		module.cleanup = *module_info->cleanup;

		module.init(module.params);

	}
}

void DBModulesLoader::CleanModules(DBModules& modules)
{
	std::vector<DBModule>::iterator iter = modules.begin();

	for(;iter!=modules.end();++iter)
	{
		if(iter->enable && iter->dl_handler)
		{
			iter->cleanup();

			dlclose(iter->dl_handler);

			iter->dl_handler = NULL;
			iter->init = NULL;
			iter->handler = NULL;
			iter->cleanup = NULL;
		}
	}
}

void DBModulesLoader::CleanModule(DBModule& module)
{
	if(module.enable && module.dl_handler)
	{
		module.cleanup();

		dlclose(module.dl_handler);

		module.dl_handler = NULL;
		module.init = NULL;
		module.handler = NULL;
		module.cleanup = NULL;
	}
}
};
