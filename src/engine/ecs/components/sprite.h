#pragma once
#include "../../texture2d.h"

struct sprite
{
    std::string texture;
    glm::vec3 scale{1,1,1};
    glm::vec3 position{0,0,0};
    float rotation{0};
};