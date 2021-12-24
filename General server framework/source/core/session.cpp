#include <iostream>
#include <core/session.h>
using namespace std;
using boost::asio::ip::tcp;

session::session(io_service_pool& io_service, message_queue& msg_loop) :
io_service_index(io_service.get_min_count_io_index()),
socket_(io_service.get_io_service(io_service_index)),
io_pool(io_service),
message_sender(msg_loop, session_source),
state(SESSION_STATE_CLOSE)
{
    
}

session::~session()
{
    close_socket();
    io_pool.reduce_io_count(io_service_index);
}

void session::close_socket()
{
    if (state == SESSION_STATE_CONN)
    {
        boost::shared_ptr<std::string> extra_msg(new std::string("one connection is closed, remote ip:"));
        try
        {
            (*extra_msg) += socket_.remote_endpoint().address().to_string();
        }
        catch (...)
        {
            (*extra_msg) += "can not get remote ip";
        }
        state = SESSION_STATE_CLOSE;
        this->socket_.close();
        send_msg(disconnected, extra_msg);
        on_disconnected();
    }
}

void session::set_connect_state()
{
    boost::shared_ptr<std::string> extra_msg(new std::string("one connection is build, remote ip:"));
    last_commucation_time = boost::posix_time::second_clock::local_time();
    connect_time = boost::posix_time::second_clock::local_time();
    state = SESSION_STATE_CONN;
    try 
    {
        (*extra_msg) += socket_.remote_endpoint().address().to_string();
    }
    catch (...)
    {
        (*extra_msg) += "can not get remote ip";
    }
    send_msg(connected, extra_msg);
    on_connected();
}

tcp::socket& session::socket()
{
    return socket_;
}

void session::start()
{
    socket_.async_read_some(boost::asio::buffer(data_, MAX_PACKET_LEN),
        boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void session::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        this->last_commucation_time = boost::posix_time::second_clock::local_time();
        on_data_recv(data_, bytes_transferred);
        start();
    }
    else
    {
        close_socket();
    }
}

void session::handle_write(const boost::system::error_code& error)
{
    if (error)
    {
        close_socket();
    }
    else
    {
        this->last_commucation_time = boost::posix_time::second_clock::local_time();
        on_data_send();
    }
}

void session::send_data(const unsigned char* data, size_t bytes_transferred)
{
    memcpy(data_, data, bytes_transferred);
    boost::asio::async_write(this->socket(), boost::asio::buffer(data_, bytes_transferred),
        boost::bind(&session::handle_write, this, boost::asio::placeholders::error));
}