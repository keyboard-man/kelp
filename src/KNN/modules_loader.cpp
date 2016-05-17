/*************************************************************************
	> File Name: load_modules.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年03月27日 星期五 17时35分47秒

	模块加载者，用于加载用户自行编写的轮询数据收集模块
 ************************************************************************/

#include <sstream>
#include "modules_loader.h"

namespace kelp{
ModulesLoader::ModulesLoader()
{
	//init the log
	log_ = log4cxx::Logger::getLogger("modules_loader");
}

ModulesLoader::ModulesLoader(Modules& modules)
{
	//init the modules
	ModulesLoader::InitModules(modules);
}

void ModulesLoader::InitModules(Modules& modules)
{
	//load so & init
	log_ = log4cxx::Logger::getLogger("modules_loader");
	std::vector<Module>::iterator iter = modules.begin();
	void* handler;
	ModuleInfo* module_info;

	for(;iter!=modules.end();++iter)
	{
		if((*iter).enable)
		{
			(*iter).dl_handler = NULL;
			(*iter).init = NULL;
			(*iter).handler = NULL;
			(*iter).cleanup = NULL;
			
			LOG4CXX_DEBUG(log_,(*iter).path);
			handler = dlopen((*iter).path.c_str(),RTLD_LAZY);

			if(!handler)
			{
				//加载模块失败
				std::string err = "Can not load so: " + iter->name;
				LOG4CXX_WARN(log_,err);
				continue;
			}
			dlerror();

			module_info = (ModuleInfo *) dlsym(handler,(*iter).name.c_str());
			const char* dlsym_error = dlerror();
			if(dlsym_error)
			{
				//加载ModuleInfo失败
				std::string err = "Can not find ModuleInfo in " + iter->name;
				dlclose(handler);
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

void ModulesLoader::InitModule(Module& module)
{
	void* handler;
	ModuleInfo* module_info;

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
			std::string err = "Can not load so: " + module.name;
			//log
			LOG4CXX_WARN(log_,err);
			return ;
		}
		dlerror();

		module_info = (ModuleInfo *)dlsym(handler,module.name.c_str());
		const char* dlsym_err = dlerror();
		if(dlsym_err)
		{
			//load failed
			std::string err = "Can not find ModuleInfo in " + module.name;
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

void ModulesLoader::CleanModules(Modules& modules)
{
	std::vector<Module>::iterator iter = modules.begin();

	for(;iter!=modules.end();++iter)
	{
		if((*iter).enable && (*iter).dl_handler)
		{
			std::ostringstream oss;
			oss << "clean " << iter->name << " module" << std::endl;
			LOG4CXX_DEBUG(log_,oss.str());

			iter->cleanup();
			dlclose((*iter).dl_handler);

			(*iter).dl_handler = NULL;
			(*iter).init = NULL;
			(*iter).handler = NULL;
			(*iter).cleanup = NULL;
		}
	}
}

void ModulesLoader::CleanModule(Module& module)
{
	if(module.enable && module.dl_handler)
	{
		std::ostringstream oss;
		oss << "clean " << module.name << " module" << std::endl;
		LOG4CXX_DEBUG(log_,oss.str());

		module.cleanup();
		dlclose(module.dl_handler);

		module.dl_handler = NULL;
		module.init = NULL;
		module.handler = NULL;
		module.cleanup = NULL;
	}
}
};
