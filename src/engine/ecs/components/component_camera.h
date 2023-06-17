#pragma once
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

// this is only for 2d specific right now, for general purpose camera, will need to change code
struct component_camera
{
    glm::vec3 inverse_forward{0.0f,0.0f,-1.0f}; // for camera you need to invert forward
    glm::vec3 up{0.0f,1.0f,0.0f};
    glm::vec2 size{1280,720};
    float zoom{1};
    float near{-1};
    float far{1};
    inline static glm::mat4 view {glm::mat4(1.0f)};
    inline static glm::mat4 proj {glm::mat4(1.0f)};
};
