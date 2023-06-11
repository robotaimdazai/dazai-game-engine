#pragma once
#include <string>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct sprite
{
    std::string texture;
    glm::vec3 offset{0,0,0};
};
