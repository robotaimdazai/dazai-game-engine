#pragma once
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"

// this is only for 2d specific right now, for general purpose camera, will need to change code
struct component_camera
{
    glm::vec3 inverse_forward{0.0f,0.0f,-1.0f}; // for camera you need to invert forward
    glm::vec3 up{0.0f,1.0f,0.0f};
    glm::vec2 size{1280,720};
    float zoom{1};
    float near{-24};
    float far{24};
    inline static glm::mat4 view {glm::mat4(1.0f)};
    inline static glm::mat4 proj {glm::mat4(1.0f)};

    static auto screen_to_world_pos(const glm::vec2 screen_pos)->glm::vec2
    {
        const auto inverse_projection_view_mat = glm::inverse(proj*view);
        const auto view_cords = inverse_projection_view_mat * glm::vec4(screen_pos.x,screen_pos.y,0.0f,1.0f);
        const glm::vec2 world_pos =glm::vec2(view_cords.x/view_cords.w,view_cords.y/view_cords.w);
        return world_pos;
    }
};
