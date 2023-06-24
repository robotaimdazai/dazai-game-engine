#include "system_player_input.h"
#include "../ecs.h"
#include "../components/component_animator.h"
#include "../components/component_player_input.h"
#include "../components/component_rigidbody2d.h"
#include "../components/component_transform.h"
#include "glm/gtx/dual_quaternion.hpp"

extern ecs g_ecs;
auto system_player_input::fixed_update(const float fixed_delta_time) -> void
{
    for (auto const& entity:entities)
    {
        auto& player = g_ecs.get_component<component_player_input>(entity);
        auto& player_transform = g_ecs.get_component<component_transform>(entity);
        auto& rigidbody = g_ecs.get_component<component_rigidbody2d>(entity);
        
        if(m_is_moving_)
        {
            if(rigidbody.velocity.x<0)
                player_transform.scale.x = -1;
            else
                player_transform.scale.x = 1;

            rigidbody.velocity *= player.speed  * fixed_delta_time;
        }
        
    }
}
auto system_player_input::handle_event(const input_state& input) -> void
{
    for (auto const& entity:entities)
    {
        auto& player = g_ecs.get_component<component_player_input>(entity);
        auto& animator = g_ecs.get_component<::component_animator>(entity);
        auto& rigidbody = g_ecs.get_component<::component_rigidbody2d>(entity);
        
        //player is not moving by default
        m_is_moving_ = false;
        rigidbody.velocity ={0,0};
        if(input.keyboard_state.is_down(player.left_key))
        {
            rigidbody.velocity.x =-1;
            m_is_moving_ =true;
        }
        if(input.keyboard_state.is_down(player.right_key))
        {
            rigidbody.velocity.x=1;
            m_is_moving_ =true;
        }
            
        if(input.keyboard_state.is_down(player.up_key))
        {
            rigidbody.velocity.y=1;
            m_is_moving_ =true;
        }
           
        if(input.keyboard_state.is_down(player.down_key))
        {
            rigidbody.velocity.y =-1;
            m_is_moving_ =true;
        }
        //normalize the direction
        if(rigidbody.velocity != glm::vec2(0))
        {
            rigidbody.velocity = glm::normalize(rigidbody.velocity);
            
        }
        if(m_is_moving_)
        {
            animator.change_animation("run");
        }
        else
        {
            animator.change_animation("idle");
        }
        if(input.keyboard_state.is_just_pressed(player.attack_key))
        {
            animator.change_animation("attack");
        }
        
    }
    
}
