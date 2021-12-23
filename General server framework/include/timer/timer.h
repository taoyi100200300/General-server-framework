#ifndef _TIMER_H_
#define _TIMER_H_
#include <boost/asio.hpp>  
#include <boost/bind.hpp>    
#include <boost/function.hpp>  
#include <boost/date_time/posix_time/posix_time.hpp>

class timer
{
public:
	timer(int second);
	~timer();
	void timer_run();
	void timer_stop();
	void set_interval(int second);
	int get_interval();
protected:
	virtual void timer_tast() = 0;
private:
	void timer_enter(const boost::system::error_code& err);
	boost::asio::io_service io;
	boost::asio::deadline_timer tim;
	int interval;
};
#endif // !_TIMER_H_
