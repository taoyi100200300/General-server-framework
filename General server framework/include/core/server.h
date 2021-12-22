#ifndef _SERVER_H_
#define _SERVER_H_
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <core/io_service_pool.h>
#include <core/session.h>

class server
{
public:
	server(short port, int thread_cnt);
	~server();
	void handle_accept(session* new_session, const boost::system::error_code& error);
	void run();
private:
	io_service_pool io_service_pool_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::mutex cout_mtx;
};
#endif