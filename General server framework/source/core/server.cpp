#include <iostream>
#include<core/server.h>

using namespace std;
using boost::asio::ip::tcp;

template<class T>
server<T>::server(short port, int thread_cnt):\
io_service_pool_(thread_cnt), \
acceptor_(io_service_pool_.get_io_service(0), \
    tcp::endpoint(tcp::v4(), port))
{
    session* new_session = new T(io_service_pool_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session, boost::asio::placeholders::error));
}

template<class T>
server<T>::~server()
{
    io_service_pool_.stop();
}

template<class T>
void server<T>::handle_accept(session* new_session, const boost::system::error_code& error)
{

    if (!error)
    {
        new_session->set_connect_state();
        new_session->start();
    }
    else
    {
        delete new_session;
    }
    new_session = new T(io_service_pool_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session, boost::asio::placeholders::error));
}

template<class T>
void server<T>::run()
{
    io_service_pool_.start();
}