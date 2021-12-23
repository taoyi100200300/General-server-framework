#ifndef _DEFAULT_ON_CONNECTED_ACTION_H_
#define _DEFAULT_ON_CONNECTED_ACTION_H_
#include<action/action.h>
#include<core/server.h>

class default_on_connected_action :public Action
{
public:
	virtual bool action_event(boost::shared_ptr<message> msg)
	{
		BOOST_LOG_SEV(logger, Log_Info) << *(std::string*)(msg->extra_message.get());
		return true;
	}
};
#endif