#include <action/action_manager.h>
#include<action/default_on_connected_action.h>
#include<action/default_on_disconnect_action.h>
#include<action/default_on_error_action.h>

action_manager::action_manager()
{
	add_on_connect_action(boost::shared_ptr<Action>(new default_on_connected_action()));
	add_on_disconnect_action(boost::shared_ptr<Action>(new default_on_disconnect_action()));
	add_on_error_action(boost::shared_ptr<Action>(new default_on_error_action()));
}

void action_manager::add_on_connect_action(boost::shared_ptr<Action> act)
{
	on_connect_action_list.push_back(act);
}

void action_manager::add_on_disconnect_action(boost::shared_ptr<Action> act)
{
	on_disconnect_action_list.push_back(act);
}

void action_manager::add_on_error_action(boost::shared_ptr<Action> act)
{
	on_error_action_list.push_back(act);
}

void action_manager::add_on_user_define_action(boost::shared_ptr<Action> act)
{
	on_user_define_action_list.push_back(act);
}

void action_manager::on_connect_action_loop(boost::shared_ptr<message> msg)
{
	std::list<boost::shared_ptr<Action>>::iterator it = on_connect_action_list.begin();
	while (it != on_connect_action_list.end() && (*it)->action_event(msg) != true)
		it++;
}

void action_manager::on_disconnect_action_loop(boost::shared_ptr<message> msg)
{
	std::list<boost::shared_ptr<Action>>::iterator it = on_disconnect_action_list.begin();
	while (it != on_disconnect_action_list.end() && (*it)->action_event(msg) != true)
		it++;
}

void action_manager::on_error_action_loop(boost::shared_ptr<message> msg)
{
	std::list<boost::shared_ptr<Action>>::iterator it = on_error_action_list.begin();
	while (it != on_error_action_list.end() && (*it)->action_event(msg) != true)
		it++;
}

void action_manager::on_user_define_action_loop(boost::shared_ptr<message> msg)
{
	std::list<boost::shared_ptr<Action>>::iterator it = on_user_define_action_list.begin();
	while (it != on_user_define_action_list.end() && (*it)->action_event(msg) != true)
		it++;
}
