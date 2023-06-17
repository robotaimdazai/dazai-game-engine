#pragma once
#include <map>
#include <string>

#include "component_animation.h"

struct component_animator
{
    std::map<std::string,component_animation> animations;
    std::string active{};
    
    auto change_animation(const std::string& animation)->void
    {
        const auto active_animation = animations[active];
        if(active == animation)
        {
            if(active_animation.has_exit_time && active_animation.time == active_animation.frames-1)
            {
                // when active animation has already ended and its called again, then dont return
            }
            else
            {
                return;
            }
        }
        
        if(active_animation.has_exit_time && active_animation.time < active_animation.frames-1)
            return;
        animations[active].time = 0;
        active = animation;
    }
   
};
