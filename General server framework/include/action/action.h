#ifndef _ACTION_H_
#define _ACTION_H_
#include <message/message.h>
#include <log/log.h>

class Action
{
public:
	virtual bool action_event(boost::shared_ptr<message> msg) = 0;
protected:
	src::severity_channel_logger<SeverityLevel, std::string> logger;
};

#endif
