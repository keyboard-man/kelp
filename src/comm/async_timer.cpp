/*************************************************************************
	> File Name: ../Kelp/src/comm/async_timer.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年07月29日 星期三 11时22分58秒
 ************************************************************************/

#include "async_timer.h"

namespace kelp
{
AsyncTimer::AsyncTimer(boost::asio::io_service& ios,int x,boost::function<void()> func,bool loop):
	ios_(ios),f_(func),time_(x),t_(ios,boost::posix_time::seconds(x)),loop_(loop)
{
	log_ = log4cxx::Logger::getLogger("async_timer");

	t_.async_wait(bind(&AsyncTimer::CallFunc,this,boost::asio::placeholders::error));
}
void AsyncTimer::CallFunc(const boost::system::error_code & err)
{
	if(err)
	{
		return ;
	}
	else
	{
		f_();

		if(loop_)
		{
			t_.expires_at(t_.expires_at() + boost::posix_time::seconds(time_));
			t_.async_wait(boost::bind(&AsyncTimer::CallFunc,this,boost::asio::placeholders::error));
		}
	}
}

void AsyncTimer::Reload(int x,bool loop)
{
	std::ostringstream oss;
	oss << "reload time form " << time_ << " to " << x << std::endl;
	LOG4CXX_INFO(log_,oss.str());

	time_ = x;
}

void AsyncTimer::Cancel()
{
	//std::ostringstream oss;
	//oss << "The AsyncTimer is canceled!" << std::endl;
	//LOG4CXX_INFO(log_,"The AsyncTimer is canceled!");

	t_.cancel();
	//ios_.stop();
}
}
