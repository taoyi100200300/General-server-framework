#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
class configure
{
public:
	configure(std::string ini_path);
	template<typename T>
	T get_value(std::string node_id, std::string cfg_id,T defaule_value)
	{
		commonCfg = pt.get_child(node_id);
		return  commonCfg.get<T>(cfg_id, defaule_value);
	}
private:
	boost::property_tree::ptree pt, commonCfg;
};
#endif