#pragma once
#include "../core/system.h"

class system_collision_box:public system
{
public:
    auto fixed_update(float fixed_delta_time)->void;
    auto debug_draw()->void;
};
