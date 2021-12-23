#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include<boost/shared_ptr.hpp>
#include<boost/date_time/posix_time/ptime.hpp>
typedef enum 
{
	session_source,
	timer_source,
	user
}source_type;

typedef enum
{
	connected,
	disconnected,
	error
}message_type;

class message
{
public:
	message(source_type src_type, boost::shared_ptr<void> src_ptr, message_type msg_type, boost::shared_ptr<void> extra_message);
	~message();
	source_type src_type;
	boost::shared_ptr<void> src_ptr;
	message_type msg_type;
	boost::shared_ptr<void> extra_message;
	boost::posix_time::ptime msg_time;
};
#endif // !_MESSAGE_H_
