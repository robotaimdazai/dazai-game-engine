#pragma once
#include "glm/vec2.hpp"

struct rect
{
    glm::vec2 position;
    glm::vec2 size;
};

class physics2d
{
public:
    static auto point_intersects_rect(const glm::vec2& point, const rect& rect) -> bool
    {
        if(point.x>= rect.position.x && point.x<=rect.position.x+rect.size.x && point.y>=rect.position.y && point.y<=rect.position.y + rect.size.y)
            return true;
    
        return false;
    }

    static auto rect_intersects_rect(const rect& rect_a, const rect& rect_b) -> bool
    {
        if(rect_a.position.x > rect_b.position.x + rect_b.size.x || rect_a.position.x + rect_a.size.x < rect_b.position.x ||
            rect_a.position.y > rect_b.position.y+rect_b.size.y || rect_a.position.y + rect_a.size.y< rect_b.position.y)
            return false;
    
        return true;
    }

    static auto ray_intersects_rect(const glm::vec2& origin, const glm::vec2& direction, const rect& rect) -> bool
    {
        return false;
    }

};
