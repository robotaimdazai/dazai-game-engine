#ifndef  LOG_H
#define  LOG_H
#include <sstream>
#include <fstream>
#define ASSERT(x) if(!(x)) __debugbreak();

#define LOG_FILE "logs.log"


enum log_level
{
    error,
    warning,
    info,
    debug
};

struct log_config
{
    log_level reporting_level = info;
    bool restart = false;
};

extern log_config log_config;

class logger
{
public:
    logger();
    virtual ~logger();
    auto get(log_level level= info)->std::ostringstream&;
    static void restart();

private:
    std::ostringstream m_os_;
    static std::ofstream m_file_;
    static auto get_label(log_level type) -> std::string;
};

// backward slash indicates line continuity
#define LOG(level)if(level>log_config.reporting_level);else logger().get(level)


#endif