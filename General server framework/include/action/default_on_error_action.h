#ifndef _DEFAULT_ON_ERROR_ACTION_H_
#define _DEFAULT_ON_ERROR_ACTION_H_
#include<action/action.h>
#include<core/server.h>

class default_on_error_action :public Action
{
public:
	virtual bool action_event(boost::shared_ptr<message> msg)
	{
		BOOST_LOG_SEV(logger, Log_Error) << *(std::string*)(msg->extra_message.get());
		return true;
	}
};
#endif