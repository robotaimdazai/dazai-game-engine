#include "logger.h"
#include <fstream>
#include <iostream>

logger::logger()
{
    m_file_.open(LOG_FILE,std::fstream::app);
}

logger::~logger()
{
    m_os_<<std::endl;
    m_file_<< m_os_.str();
    std::cout<<m_os_.str();
    m_os_.clear();
    m_file_.close();
}
std::ofstream logger::m_file_;

auto logger::restart()->void
{
    m_file_.open(LOG_FILE,std::fstream::trunc);
    m_file_.close();
}

auto logger::get(log_level level) -> std::ostringstream&
{
    if(!m_file_)
        return m_os_;

    //log 
    time_t now;
    tm time_info;
    char date[19];
    time(&now);
    localtime_s(&time_info,&now);
    strftime(date,19,"%y-%m-%d %H:%M:%S",&time_info);
    m_os_<<date<<" "<<get_label(level)<<": \t";
    return m_os_;
}



auto logger::get_label(const log_level type) -> std::string
{
    std::string label;
    switch (type)
    {
    case debug:
        label ="DEBUG";
        break;
    case error:
        label ="ERROR";
        break;
    case info:
        label ="INFO";
        break;
    case warning:
        label ="WARN";
        break;
    }
    return label;
}







