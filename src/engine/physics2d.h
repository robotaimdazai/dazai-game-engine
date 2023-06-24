#pragma once
#include "debug_draw.h"
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

    static auto ray_intersects_rect(const glm::vec2& origin, const glm::vec2& direction, const rect& rect,
        glm::vec2& contact_point, glm::vec2& contact_normal, float& contact_time) -> bool
    {
        
        glm::vec2 t_near = (rect.position-origin)/direction;
        glm::vec2 t_far = (rect.position+rect.size - origin)/direction;

        //check if divide by zero occured then return no collision(when direction/velocity is zero)
        if(std::isnan(t_near.x) || std::isnan(t_near.y)) return false;
        if(std::isnan(t_far.x) || std::isnan(t_far.y)) return false;

        if(t_near.x> t_far.x) std::swap(t_near.x,t_far.x);
        if(t_near.y> t_far.y) std::swap(t_near.y,t_far.y);
        
        if(t_near.x> t_far.y || t_near.y> t_far.x) return false;

        contact_time = std::max(t_near.x,t_near.y);
        float t_far_hit = std::min(t_far.x,t_far.y);

        if(t_far_hit<0) return false;
        
        contact_point = origin + contact_time * direction;
        
        if(t_near.x > t_near.y)
        {
            if(direction.x<0)
            {
                contact_normal = {1,0};
            }
            else
            {
                contact_normal ={-1,0};
            }
        }
        else if(t_near.x<t_near.y)
        {
            if(direction.y<0)
            {
                contact_normal = {0,1};
            }
            else
            {
                contact_normal ={0,-1};
            }
        }
        
        return true;
    }

    static auto dynamic_rect_intersects_rect(const glm::vec2& rect_a_velocity, const rect& rect_a,  const rect& rect_b,
                                             glm::vec2& contact_point, glm::vec2& contact_normal, float& contact_time,
                                             const float& delta_time =1)->bool
    {
        if(rect_a_velocity == glm::vec2(0)) return false;

        rect expanded_target{};
        auto size_a= glm::vec2(rect_a.size.x/2, rect_a.size.y/2);
        expanded_target.position = rect_b.position - size_a;
        expanded_target.size = rect_b.size + rect_a.size;
   
        const glm::vec2 ray_origin = rect_a.position + size_a;
        if(ray_intersects_rect(ray_origin,rect_a_velocity * delta_time, expanded_target,contact_point,
            contact_normal,contact_time))
        {
            if(contact_time<=1.0f)return true;
        }
        
        return false;
    }

};
