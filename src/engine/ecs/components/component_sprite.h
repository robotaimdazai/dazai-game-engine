#pragma once
#include <string>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "../../physics2d.h"

struct component_sprite
{
    std::string texture_id;
    glm::vec3 offset{0,0,0};
    glm::vec2 size{64,64};
    bool is_animated{false};
    rect clip {{0,0},{1,1}};
    glm::vec4 color={1,1,1,1};
};
