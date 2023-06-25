#pragma once
#include "../../physics2d.h"
#include "glm/vec2.hpp"

struct component_rigidbody2d
{
    glm::vec2 velocity;
    glm::vec2 acceleration{0,0};
    collision_resolution_type resolution_type{slide};
};
