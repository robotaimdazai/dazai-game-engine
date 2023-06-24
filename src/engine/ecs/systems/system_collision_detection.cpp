#include "system_collision_detection.h"
#include "system_collider_renderer.h"
#include "../ecs.h"
#include "../../physics2d.h"
#include "../components/component_box_collider.h"
#include "../components/component_rigidbody2d.h"
#include "../components/component_transform.h"
extern ecs g_ecs;

auto system_collision_detection::update(float delta_time) -> void
{
    for(auto const& entity:entities)
    {
        auto& entity_a = entity;
        auto& collider_a =g_ecs.get_component<component_box_collider>(entity);
        
        
        for(auto const& entity:entities) // optimize this with spatial partitioning 
        {
            auto& entity_b = entity;
            auto& collider_b =g_ecs.get_component<component_box_collider>(entity);
            
            if(entity_a == entity_b) //skip self
                continue;

            auto rect_a = system_collider_renderer::get_collider_rect(entity_a);
            auto rect_b = system_collider_renderer::get_collider_rect(entity_b);

            if(!collider_a.is_trigger)
            {
                // means it must have a rigidbody attached
                //resolve for rigidbody types here
                auto& rigidbody = g_ecs.get_component<component_rigidbody2d>(entity_a);
                auto& transform = g_ecs.get_component<component_transform>(entity_a);
                glm::vec2 cp{0,0};
                glm::vec2 cn{0,0};
                float t=0;
                if(physics2d::dynamic_rect_intersects_rect(rigidbody.velocity,rect_a,rect_b,cp,
                    cn,t,delta_time))
                {
                    rigidbody.velocity += glm::abs(rigidbody.velocity) * (1-t) *cn;
                    
                    const glm::vec3 velocity = {rigidbody.velocity.x,rigidbody.velocity.y,0};
                    transform.position+=velocity * delta_time;
                    //LOG(info)<<rigidbody.velocity.x;
                    LOG(info)<<cn.x<<", "<<cn.y;

                    //rigidbody.velocity = glm::vec2(0);
                } 
                
            }
            else
            {
                if(physics2d::rect_intersects_rect(rect_a,rect_b))
                {
                    //resolve for trigger types here
                }
            }
        }
    }
}


