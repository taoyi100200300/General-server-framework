#include<core/server.h>
#include<core/server.cpp>
#include<iostream>
class test_session :public session
{
public:
	test_session(io_service_pool& io_service):session(io_service)
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
	server<test_session> s(8888, 20);
	s.run();
	while (1);
}