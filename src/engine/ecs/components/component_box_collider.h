#pragma once
#include "../../physics2d.h"
struct component_box_collider
{
    glm::vec2 position{0,0};
    glm::vec2 offset{-16,-16};
    glm::vec2 size{32,32};
    bool is_trigger{false};
};
