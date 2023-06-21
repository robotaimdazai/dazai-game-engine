#pragma once
#include "../core/system.h"

class system_collision_detection:public system
{
public:
    auto update(float delta_time)->void;
    
};
