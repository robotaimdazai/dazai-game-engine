#pragma once

#include "component.h"
#include "../../vec2.h"
struct keyboard_component:component
{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool space = false;
};