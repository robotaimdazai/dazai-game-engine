﻿#include "system_collision_detection.h"
#include "system_collider_renderer.h"
#include "../ecs.h"
#include "../../physics2d.h"
#include "../components/component_box_collider.h"
#include "../components/component_rigidbody2d.h"
#include "../components/component_transform.h"
extern ecs g_ecs;

auto system_collision_detection::fixed_update(float fixed_delta_time) -> void
{
    for(auto const& entity:entities)
    {
        auto& selected_entity = entity;
        auto& selected_collider =g_ecs.get_component<component_box_collider>(entity);
        auto& selected_transform = g_ecs.get_component<component_transform>(selected_entity);
        auto selected_rigidbody = g_ecs.try_get_component<component_rigidbody2d>(selected_entity);
        auto selected_rect = system_collider_renderer::get_collider_rect(selected_entity);
        glm::vec2 contact_point{0,0};
        glm::vec2 contact_normal{0,0};
        float contact_time=0;
        std::vector<std::pair<::entity,float>> sorted_entities;
        
        for(auto const& entity:entities) // optimize this with spatial partitioning 
        {
            if(selected_entity == entity) //skip self
                continue;
            
            auto other_rect = system_collider_renderer::get_collider_rect(entity);
            
            if(selected_collider.is_trigger)
            {
                if(physics2d::rect_intersects_rect(selected_rect,other_rect))
                {
                    //resolve for trigger types here
                }
            }
            else
            {
                //when selected collider is not a trigger, which means it expects rigidbody
                if(selected_rigidbody!=nullptr)
                {
                    auto rigidbody =*selected_rigidbody;
                    if(physics2d::dynamic_rect_intersects_rect(rigidbody.velocity,selected_rect,other_rect,contact_point,
                        contact_normal,contact_time))
                    {
                        sorted_entities.emplace_back(entity,contact_time);
                    } 
                }
            }
        }
        //now sort all the colliders
        
        std::ranges::sort(sorted_entities,[](const std::pair<::entity,float>& a,const std::pair<::entity,float>& b)
        {
            return a.second<b.second;
        });

        for (auto const& entity:sorted_entities)
        {
            auto other_rect = system_collider_renderer::get_collider_rect(entity.first);
            if(selected_rigidbody!=nullptr)
            {
                auto rigidbody =*selected_rigidbody;
                if(physics2d::dynamic_rect_intersects_rect(rigidbody.velocity,selected_rect,other_rect,contact_point,
                    contact_normal,contact_time))
                {
                    rigidbody.velocity += m_collision_resolution_factor_ * contact_normal *
                        glm::vec2(std::abs(rigidbody.velocity.x),std::abs(rigidbody.velocity.y)) * (1-contact_time);
                    glm::vec3 velocity = {rigidbody.velocity.x,rigidbody.velocity.y,0};
                    selected_transform.position+=velocity ;
                } 
            }
        }
    }
}

auto system_collision_detection::debug_draw() -> void
{
    
}


