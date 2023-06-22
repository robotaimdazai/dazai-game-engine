#include "system_collision_detection.h"
#include "system_collider_renderer.h"
#include "../ecs.h"
#include "../../physics2d.h"


extern ecs g_ecs;

auto system_collision_detection::update(float delta_time) -> void
{
    for(auto const& entity:entities)
    {
        auto& entity_a = entity;
        
        for(auto const& entity:entities) // optimize this with spatial partitioning 
        {
            auto& entity_b = entity;
            
            if(entity_a == entity_b) //skip self
                continue;

            auto rect_a = system_collider_renderer::get_collider_rect(entity_a);
            auto rect_b = system_collider_renderer::get_collider_rect(entity_b);

            if(physics2d::rect_intersects_rect(rect_a,rect_b))
            {
                LOG(info)<<"collision";
            }
        }
    }
}

