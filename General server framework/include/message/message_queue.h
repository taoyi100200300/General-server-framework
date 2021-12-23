#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_
#include <queue>
#include <message/message.h>
#include <boost/thread.hpp>

class message_queue
{
public:
	message_queue();
	~message_queue();
	void push_message(boost::shared_ptr<message> msg);

protected:
	virtual void message_proc(boost::shared_ptr<message> msg) = 0;
	std::queue<boost::shared_ptr<message>> msg_queue;
	boost::thread message_loop_thread;

private:
	boost::shared_ptr<message> pop_message();
	boost::mutex mutex;
	bool exit_flag;
	void message_loop();
};
#endif
