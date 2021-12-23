#include <message/message_sender.h>

message_sender::message_sender(message_queue& message_loop, source_type src_type):
message_loop(message_loop), src_type(src_type)
{
}

void message_sender::send_msg(boost::shared_ptr<void> src_ptr,message_type msg_type, boost::shared_ptr<void> extra_message)
{
	message_loop.push_message(boost::shared_ptr<message>(new message(src_type, src_ptr, msg_type, extra_message)));
}
