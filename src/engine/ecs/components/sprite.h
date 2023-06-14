#pragma once
#include <string>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct sprite
{
    std::string texture_id;
    glm::vec3 offset{0,0,0};
    glm::vec2 size{64,64};
    bool is_animated{false};
    std::vector<float> clip_buffer
    {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
       0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
      -0.5f,  0.5f, 0.0f, 0.0f, 1.0f        
    };
};
