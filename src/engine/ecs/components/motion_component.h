#pragma once

#include "component.h"
#include"../../vec2.h"

struct motion_component:component
{
    vec2 velocity{0,0};
    vec2 acceleration{0,0};
};