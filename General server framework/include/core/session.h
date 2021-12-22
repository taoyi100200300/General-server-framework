#ifndef _SESSION_H_
#define _SESSION_H_
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <core/io_service_pool.h>
#define MAX_PACKET_LEN 10240

#define SESSION_STATE_CLOSE 0
#define SESSION_STATE_CONN	1

class session
{
public:

	session(io_service_pool& io_service);
	virtual ~session();
	boost::asio::ip::tcp::socket& socket();
	void start();
	void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);
	void handle_write(const boost::system::error_code& error);
	void send_data(const unsigned char* data, size_t bytes_transferred);
	void close_socket();
	void set_connect_state();

private:
	boost::posix_time::ptime last_commucation_time;
	boost::posix_time::ptime connect_time;
	boost::asio::ip::tcp::socket socket_;
	unsigned char data_[MAX_PACKET_LEN];
	int io_service_index;
	io_service_pool& io_pool;
	int state;
};
#endif