#pragma once
#include "../../globals.h"
#include "../../physics2d.h"
#include "../core/system.h"

class system_collider_renderer: public system
{
public:
    auto render()->void;
    static auto get_collider_rect(const entity& entity)->rect;
    
    
};
