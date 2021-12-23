#ifndef _DEFAULT_ON_DISCONNECT_ACTION_H_
#define _DEFAULT_ON_DISCONNECT_ACTION_H_
#include<core/server.h>
#include<action/action.h>

class default_on_disconnect_action :public Action
{
public:
	virtual bool action_event(boost::shared_ptr<message> msg)
	{
		BOOST_LOG_SEV(logger, Log_Info) << *(std::string*)(msg->extra_message.get());
		return true;
	}
};
#endif