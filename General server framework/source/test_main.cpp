#include<core/server.h>

int main()
{
	server s(8888, 20);
	s.run();
	while (1);
}