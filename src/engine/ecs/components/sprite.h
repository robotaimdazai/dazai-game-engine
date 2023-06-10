#pragma once
#include "../../vec2.h"
#include "../../texture2d.h"

struct sprite
{
    texture2d texture;
    glm::vec3 size{1,1,1};
    glm::vec3 position{0,0,0};
    float rotation{0};
};