#include "timer.h"

#include <SDL_timer.h>

timer::timer():m_frame_start_(0),m_last_frame_(0),m_frame_time_(0)
{
    
}

timer::~timer()
= default;

auto timer::delta_time() -> uint32_t
{
    m_frame_start_ = SDL_GetTicks();
    const auto delta_time = m_frame_start_- m_last_frame_;
    m_last_frame_ = m_frame_start_;
    return delta_time;
}

auto timer::delay_time() -> void
{
    m_frame_time_ = SDL_GetTicks() - m_frame_start_;
    if(m_frame_time_<frame_delay)
    {
        SDL_Delay(frame_delay-m_frame_time_);
    }
}




