#include <message/message_sender.h>
#include<boost/uuid/uuid_generators.hpp>
message_sender::message_sender(message_queue& message_loop, source_type src_type):
message_loop(message_loop), src_type(src_type)
{
	boost::uuids::string_generator sgen;
	uid = sgen("0123456789abcdef0123456789abcdef");
}

void message_sender::send_msg(message_type msg_type, boost::shared_ptr<void> extra_message)
{
	message_loop.push_message(boost::shared_ptr<message>(new message(src_type, uid, msg_type, extra_message)));
}
