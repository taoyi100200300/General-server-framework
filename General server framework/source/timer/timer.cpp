#include <timer/timer.h>

timer::timer(int second):
	interval(second),
	tim(io, boost::posix_time::seconds(interval))
{
}

timer::~timer()
{
	timer_stop();
}

void timer::timer_run()
{
	tim.expires_from_now(boost::posix_time::seconds(interval));
	tim.async_wait(boost::bind(&timer::timer_enter, this, boost::asio::placeholders::error));
	io.run();
}

void timer::timer_stop()
{
	tim.cancel();
	io.stop();
}

void timer::set_interval(int second)
{
	timer_stop();
	interval = second;
	timer_run();
}

int timer::get_interval()
{
	return interval;
}

void timer::timer_enter(const boost::system::error_code& err)
{
	if (!err)
	{
		timer_tast();
		timer_run();
	}
}
