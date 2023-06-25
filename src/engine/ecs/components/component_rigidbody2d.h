#pragma once
#include "../../physics2d.h"
struct component_rigidbody2d
{
    glm::vec2 velocity;
    collision_resolution_type resolution_type{slide};
};
