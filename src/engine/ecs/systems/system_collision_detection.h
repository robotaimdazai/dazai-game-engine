#pragma once
#include "../components/component_box_collider2d.h"
#include "../core/system.h"
#include "glm/vec2.hpp"

class system_collision_detection:public system
{
public:
    auto update(float delta_time)->void;

private:
    auto point_intersects_rect(glm::vec2 point, SDL_Rect rect) ->bool; 
    auto rect_intersects_rect(SDL_Rect rect_a, SDL_Rect rect_b) ->bool; 
    auto ray_intersects_rect(glm::vec2 origin, glm::vec2 direction, SDL_Rect rect) ->bool; 
};
