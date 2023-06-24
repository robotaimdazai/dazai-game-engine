#pragma once
#include "../core/system.h"

class system_rigidbody2d: public system
{
public:
    auto fixed_update(float fixed_delta_time)->void;
    
};
