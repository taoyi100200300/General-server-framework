#include <core/io_service_pool.h>
using namespace std;
using boost::asio::ip::tcp;
io_service_pool::io_service_pool(std::size_t pool_size)
{
    for (std::size_t i = 0; i < pool_size; ++i)
    {
        io_service_sptr io_service(new boost::asio::io_service);
        work_sptr work(new boost::asio::io_service::work(*io_service));
        io_services_.push_back(io_service);
        work_.push_back(work);
        io_session_count.push_back(0);
    }
}

void io_service_pool::start()
{
    for (std::size_t i = 0; i < io_services_.size(); ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(boost::bind(&boost::asio::io_service::run, io_services_[i])));
        threads_.push_back(thread);
    }
}

void io_service_pool::join()
{
    for (std::size_t i = 0; i < threads_.size(); ++i)
        threads_[i]->join();
}

void io_service_pool::stop()
{
    for (std::size_t i = 0; i < io_services_.size(); ++i)
        io_services_[i]->stop();
}

boost::asio::io_service& io_service_pool::get_io_service(int index)
{
    boost::mutex::scoped_lock lock(mtx);
    io_session_count[index]++;
    return *io_services_[index];
}

int io_service_pool::get_min_count_io_index()
{
    int ret = 0;
    for (std::size_t i = 0; i < io_session_count.size(); ++i)
        if (io_session_count[i] < io_session_count[ret])
            ret = i;
    return ret;
}

void io_service_pool::reduce_io_count(int index)
{
    boost::mutex::scoped_lock lock(mtx);
    io_session_count[index]--;
}

