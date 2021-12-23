#include<core/server.h>
#include<core/server.cpp>
#include<iostream>
#include<configure/configure.h>
#include<log/log.h>
class test_session :public session
{
public:
	test_session(io_service_pool& io_service, message_queue& msg_loop):session(io_service, msg_loop)
	{

	}
	virtual void on_connected()
	{
		std::cout << "connected!!!" << std::endl;
	}
	virtual void on_data_recv(unsigned char* buff, std::size_t bytes_transferred)
	{
		std::cout << "bytes_transferred:" << bytes_transferred<<"        " << buff << std::endl;
	}
	virtual void on_disconnected()
	{
		std::cout << "disconnected!!!" << std::endl;
	}
};

int main()
{
	//configure cfg("./server.ini");
	//std::cout << "host:"<< cfg.get_value<std::string>("command","host","192.168.112.242") << std::endl;
	//std::cout << "port:" << cfg.get_value<unsigned short>("command", "port", 8888) << std::endl;
	//std::cout << "io_poor_size:" << cfg.get_value<int>("command", "io_poor_size", 20) << std::endl;
	//g_InitLog("./");
	//src::severity_channel_logger<SeverityLevel, std::string> logger;
	//BOOST_LOG_SEV(logger, Log_Info) << "test";
	server<test_session> s(8888, 20);
	s.run();
	//boost::shared_ptr<test_session> sess=s.create_session("127.0.0.1", 6666);
	while (1);
}