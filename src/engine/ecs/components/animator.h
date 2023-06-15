#pragma once
#include <map>
#include <string>

#include "animation.h"

struct animator
{
    std::map<std::string,animation> animations;
    std::string active{};
    auto change_animation(const std::string& animation)->void
    {
        if(active == animation)
            return;
        const auto active_animation = animations[active];
        if(active_animation.has_exit_time && active_animation.time < active_animation.frames-1)
            return;
        animations[active].time = 0;
        active = animation;
    }
   
};
