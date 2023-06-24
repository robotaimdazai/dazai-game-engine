#pragma once
#include "../core/system.h"

class system_rigidbody2d: public system
{
public:
    auto update(float delta_time)->void;
    
};
