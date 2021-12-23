#include<configure/configure.h>

configure::configure(std::string ini_path)
{
	boost::property_tree::ini_parser::read_ini(ini_path, pt);
}
