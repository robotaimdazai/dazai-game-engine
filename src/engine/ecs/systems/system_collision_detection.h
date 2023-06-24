#pragma once
#include "../core/system.h"

class system_collision_detection:public system
{
public:
    auto fixed_update(float fixed_delta_time)->void;
    auto debug_draw()->void;

private:
    const float m_collision_resolution_factor_= 1.01f; // this adds 1 percent more velocity just to keep the object out of the collider
};
