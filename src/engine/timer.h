#pragma once
#include <cstdint>

class timer
{
public:
    timer();
    virtual ~timer();
    auto delta_time() -> uint32_t;
    auto delay_time()->void;

private:
    constexpr static int fps = 60;
    constexpr static int frame_delay = 1000/fps;
    uint32_t m_frame_start_;
    uint32_t m_last_frame_;
    uint32_t m_frame_time_;
    
    
};
