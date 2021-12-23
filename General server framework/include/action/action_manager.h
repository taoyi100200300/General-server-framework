#ifndef _ACTION_MANAGER_H
#define _ACTION_MANAGER_H
#include<list>
#include<action/action.h>
class action_manager
{
public:
	action_manager();
	void add_on_connect_action(boost::shared_ptr<Action> act);
	void add_on_disconnect_action(boost::shared_ptr<Action> act);
	void add_on_error_action(boost::shared_ptr<Action> act);
	void add_on_user_define_action(boost::shared_ptr<Action> act);
protected:
	void on_connect_action_loop(boost::shared_ptr<message> msg);
	void on_disconnect_action_loop(boost::shared_ptr<message> msg);
	void on_error_action_loop(boost::shared_ptr<message> msg);
	void on_user_define_action_loop(boost::shared_ptr<message> msg);
private:
	std::list<boost::shared_ptr<Action>> on_connect_action_list;
	std::list<boost::shared_ptr<Action>> on_disconnect_action_list;
	std::list<boost::shared_ptr<Action>> on_error_action_list;
	std::list<boost::shared_ptr<Action>> on_user_define_action_list;
};
#endif