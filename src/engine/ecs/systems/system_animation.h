#pragma once
#include "../core/system.h"

class system_animation:public system
{
public:
    auto update(float delta_time)->void;
    
};
