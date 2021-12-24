#include<message/message.h>
#include <boost/thread.hpp>
message::message(source_type src_type, boost::uuids::uuid uid, message_type msg_type, boost::shared_ptr<void> extra_message):
src_type(src_type), uid(uid), msg_type(msg_type), extra_message(extra_message)
{
	msg_time= boost::posix_time::second_clock::local_time();
}

message::~message()
{
}
