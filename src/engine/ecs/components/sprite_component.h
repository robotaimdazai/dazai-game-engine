#pragma once
#include <string>
#include "component.h"
#include "../../vec2.h"

struct sprite_component : component
{
    vec2 size;
    vec2 offset;
    vec2 scale;
    float rotation =0.0f;
    std::string texture_id;
};
