#ifndef _SERVER_H_
#define _SERVER_H_
#include <list>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <core/io_service_pool.h>
#include <core/session.h>
#include <message/message_queue.h>
#include <timer/timer.h>
#include<log/log.h>
#include<action/action_manager.h>
template<class T>
class server:public message_queue,public action_manager
{
	static_assert(std::is_base_of <session, T>{}, "server can only support the class base of session!!!");
public:
	server(short port, int thread_cnt);
	~server();
	void handle_accept(boost::shared_ptr<T> new_session, const boost::system::error_code& error);
	void run();
	boost::shared_ptr<T> create_session(std::string ip,unsigned short port);
	void delete_session(T* sess);
private:
	src::severity_channel_logger<SeverityLevel, std::string> logger;
	io_service_pool io_service_pool_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::mutex cout_mtx;
	std::list<boost::shared_ptr<T>> session_list;

protected:
	virtual void message_proc(boost::shared_ptr<message> msg);
};
#endif