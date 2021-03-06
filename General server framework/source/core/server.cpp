#include <iostream>
#include<core/server.h>

using namespace std;
using boost::asio::ip::tcp;

template<class T>
server<T>::server(short port, int thread_cnt):
io_service_pool_(thread_cnt), 
acceptor_(io_service_pool_.get_io_service(0), 
    tcp::endpoint(tcp::v4(), port))
{
    boost::shared_ptr<T> new_session(new T(io_service_pool_,*this));
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
    boost::shared_ptr<T> prepare_session(new T(io_service_pool_, *this));
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
    boost::shared_ptr<T> ret(new T(io_service_pool_, *this));
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

template<class T>
boost::shared_ptr<T> server<T>::get_session_by_uid(boost::uuids::uuid uid)
{
    auto it = session_list.begin();
    while (it != session_list.end())
    {
        if ((*it)->uid == uid)
        {
            return (*it);
        }
        it++;
    }
    return nullptr;
}

template<class T>
void server<T>::delete_session(boost::uuids::uuid uid)
{
    auto it = session_list.begin();
    while (it != session_list.end())
    {
        if ((*it)->uid == uid)
        {
            (*it)->close_socket();
            session_list.erase(it);
            return;
        }
        it++;
    }
}

template<class T>
void server<T>::message_proc(boost::shared_ptr<message> msg)
{
    switch (msg->msg_type)
    {
    case connected:
    {
        on_connect_action_chain(msg);
        break;
    }
    case disconnected:
    {
        on_disconnect_action_chain(msg);
        if (msg->src_type == session_source)
        {
            delete_session(msg->uid);
        }
        break;
    }
    case error:
    {
        on_error_action_chain(msg);
        break;
    }
    case user_define:
    {
        on_user_define_action_chain(msg);
        break;
    }
    }
}
