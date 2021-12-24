#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include<boost/shared_ptr.hpp>
#include<boost/date_time/posix_time/ptime.hpp>
#include<boost/uuid/uuid.hpp>
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
	error,
	user_define
}message_type;

class message
{
public:
	message(source_type src_type, boost::uuids::uuid uid, message_type msg_type, boost::shared_ptr<void> extra_message);
	~message();
	source_type src_type;
	boost::uuids::uuid uid;
	message_type msg_type;
	boost::shared_ptr<void> extra_message;
	boost::posix_time::ptime msg_time;
};
#endif // !_MESSAGE_H_
