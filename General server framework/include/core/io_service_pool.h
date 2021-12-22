#ifndef _IO_SERVICE_POOL_H_
#define _IO_SERVICE_POOL_H_
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

class io_service_pool :public boost::noncopyable
{
public:
    explicit io_service_pool(std::size_t pool_size);
    void start();
    void join();
    void stop();
    boost::asio::io_service& get_io_service(int index);
    int get_min_count_io_index();
    void reduce_io_count(int index);
private:
    typedef boost::shared_ptr<boost::asio::io_service> io_service_sptr;
    typedef boost::shared_ptr<boost::asio::io_service::work> work_sptr;
    typedef boost::shared_ptr<boost::thread> thread_sptr;

    boost::mutex mtx;

    std::vector<io_service_sptr> io_services_;
    std::vector<work_sptr> work_;
    std::vector<thread_sptr> threads_;
    std::vector<int> io_session_count;
};
#endif
