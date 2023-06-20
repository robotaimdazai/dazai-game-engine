#include "system_collision_detection.h"

auto system_collision_detection::update(float delta_time) -> void
{
    for(auto const& entity:entities)
    {
        
    }
}

auto system_collision_detection::point_intersects_rect(glm::vec2 point, SDL_Rect rect) -> bool
{
    if(point.x>= rect.x && point.x<=rect.x+rect.w && point.y>=rect.y && point.y<=rect.y + rect.h)
        return true;
    
    return false;
}

auto system_collision_detection::rect_intersects_rect(SDL_Rect rect_a, SDL_Rect rect_b) -> bool
{
    //left-a< right-b, right-a< left-b, bot-a> top-b, top-a< bot-b
    if(rect_a.x > rect_b.x + rect_b.w || rect_a.x + rect_a.w < rect_b.x || rect_a.y > rect_b.y+rect_b.h || rect_a.y + rect_a.h< rect_b.y)
            return false;
    
    return true;
}

auto system_collision_detection::ray_intersects_rect(glm::vec2 origin, glm::vec2 direction, SDL_Rect rect) -> bool
{
    return false;
}
