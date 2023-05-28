#pragma once
#include "component.h"
#include "../../vec2.h"

struct transform_component : component
{
    vec2 position{0,0};
    vec2 scale{1,1};
    float rotation =0.0f;

    transform_component() = default;
};
