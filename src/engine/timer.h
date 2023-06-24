#pragma once
#include <cstdint>

#include "globals.h"

class timer
{
    
public:
    timer();
    virtual ~timer();
    auto delta_time() -> float;
    auto delay_time()->void;

private:
    constexpr static int frame_delay = 1000/GLOBALS::target_fps;
    uint32_t m_frame_start_;
    uint32_t m_last_frame_;
    uint32_t m_frame_time_;
    
    
};
