/*************************************************************************
	> File Name: ../Kelp/src/comm/async_timer.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月29日 星期三 14时29分24秒
 ************************************************************************/

#ifndef KELP_COMM_ASYNC_TIMER
#define KELP_COMM_ASYNC_TIMER

#include <sstream>

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <log4cxx/logger.h>

#include "config_data.h"

namespace kelp
{
class AsyncTimer
{
public:
	AsyncTimer(boost::asio::io_service& ios,int x,boost::function<void()> func,bool loop=true);
	void CallFunc(const boost::system::error_code &);
	void Reload(int x,bool loop=true);
	void Cancel();

private:
	boost::function<void()> f_;
	boost::asio::deadline_timer t_;
	boost::asio::io_service& ios_;
	int time_;
	log4cxx::LoggerPtr log_;
	bool loop_;
};
}

#endif
