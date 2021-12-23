#include <message/message_queue.h>
message_queue::message_queue(): exit_flag(false), message_loop_thread(boost::bind(&message_queue::message_loop, &(*this)))
{
}

message_queue::~message_queue()
{
	exit_flag = true;
	message_loop_thread.join();
}

void message_queue::push_message(boost::shared_ptr<message> msg)
{
	boost::mutex::scoped_lock(mutex);
	msg_queue.push(msg);
}

boost::shared_ptr<message> message_queue::pop_message()
{
	boost::shared_ptr<message> ret;
	boost::mutex::scoped_lock(mutex);
	if (msg_queue.empty())
		return nullptr;
	ret = msg_queue.front();
	msg_queue.pop();
	return ret;
}

void message_queue::message_loop()
{
	boost::shared_ptr<message> msg;
	while (!exit_flag)
	{
		msg = pop_message();
		while (msg != nullptr)
		{
			message_proc(msg);
			msg = pop_message();
		}
		boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(1));
	}
}
