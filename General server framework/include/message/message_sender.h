#ifndef _MESSAGE_SENDER_H_
#define _MESSAGE_SENDER_H_
#include<message/message_queue.h>
#include<boost/enable_shared_from_this.hpp>
class message_sender:public boost::enable_shared_from_this<message_sender>
{
public:
	message_sender(message_queue& message_loop, source_type src_type);
	void send_msg(boost::shared_ptr<void> src_ptr, message_type msg_type, boost::shared_ptr<void> extra_message);
private:
	source_type src_type;
	message_queue& message_loop;
};
#endif // !_MESSAGE_SENDER_H_
