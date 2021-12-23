#include<log/log.h>
#include <iostream>
using namespace std;
void g_InitLog(std::string log_path)
{
    logging::formatter formatter =
        expr::stream
        << expr::format_date_time(log_timestamp, "[%Y-%m-%d,%H:%M:%S.%f]")

        << "<" << log_severity << ">" << expr::message;

    logging::add_common_attributes();

    auto file_sink = logging::add_file_log
    (
        keywords::file_name = log_path + "/logs/%Y-%m-%d_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
    );

    file_sink->locked_backend()->set_file_collector(sinks::file::make_collector(
        keywords::target = log_path + "/logs/",
        keywords::max_size = 50 * 1024 * 1024,
        keywords::min_free_space = 100 * 1024 * 1024
    ));

    file_sink->locked_backend()->scan_for_files();

    file_sink->set_formatter(formatter);
    file_sink->locked_backend()->auto_flush(true);

    logging::core::get()->add_global_attribute("Scope", attrs::named_scope());
    logging::core::get()->add_sink(file_sink);
}