#pragma once
#include "../../vec2.h"
#include "../../texture2d.h"

struct sprite
{
    texture2d texture;
    vec2 size{10,10};
    vec2 position{0,0};
    float rotation{0};
};