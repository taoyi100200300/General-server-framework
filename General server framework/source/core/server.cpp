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
    boost::shared_ptr<T> new_session(new T(io_service_pool_));
    session_list.push_back(new_session);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session, boost::asio::placeholders::error));
}

template<class T>
server<T>::~server()
{
    io_service_pool_.stop();
}

template<class T>
void server<T>::handle_accept(boost::shared_ptr<T> new_session, const boost::system::error_code& error)
{
    if (!error)
    {
        new_session->set_connect_state();
        new_session->start();
    }
    else
    {
        session_list.remove(new_session);
    }
    boost::shared_ptr<T> prepare_session(new T(io_service_pool_));
    session_list.push_back(prepare_session);
    acceptor_.async_accept(prepare_session->socket(),
        boost::bind(&server::handle_accept, this, prepare_session, boost::asio::placeholders::error));
}

template<class T>
void server<T>::run()
{
    io_service_pool_.start();
}

template<class T>
boost::shared_ptr<T> server<T>::create_session(std::string ip, unsigned short port)
{
    boost::shared_ptr<T> ret(new T(io_service_pool_));
    try {
        boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::tcp::v4(), port);
        boost::asio::ip::address addr = boost::asio::ip::address::from_string(ip);
        end_point.address(addr);
        ret->socket().connect(end_point);
        ret->set_connect_state();
        ret->start();
        session_list.push_back(ret);
    }
    catch (...)
    {
        return nullptr;
    }
    return ret;
}
