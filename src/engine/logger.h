#ifndef  LOG_H
#define  LOG_H
#include <sstream>
#include <fstream>

#define LOG_FILE "logs.log"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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