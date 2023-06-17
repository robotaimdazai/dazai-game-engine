#include "system_player_input.h"
#include "../ecs.h"
#include "../components/component_animator.h"
#include "../components/component_player_input.h"
#include "../components/component_transform.h"
#include "glm/gtx/dual_quaternion.hpp"

extern ecs g_ecs;
auto system_player_input::update(const float delta_time) -> void
{
    for (auto const& entity:entities)
    {
        auto& player = g_ecs.get_component<component_player_input>(entity);
        auto& player_transform = g_ecs.get_component<component_transform>(entity);
        
        if(m_is_moving_)
        {
            player_transform.position += player.direction * player.speed * delta_time;
            if(player.direction.x<0)
                player_transform.scale.x = -1;
            else
                player_transform.scale.x = 1;
        }
        
    }
}
auto system_player_input::handle_event(const input_state& input) -> void
{
    for (auto const& entity:entities)
    {
        auto& player = g_ecs.get_component<component_player_input>(entity);
        auto& animator = g_ecs.get_component<::component_animator>(entity);
        
        //player is not moving by default
        m_is_moving_ = false;
        player.direction.x =0;
        player.direction.y=0;
        if(input.keyboard_state.is_down(player.left_key))
        {
            player.direction.x=-1;
            m_is_moving_ =true;
        }
        if(input.keyboard_state.is_down(player.right_key))
        {
            player.direction.x=1;
            m_is_moving_ =true;
        }
            
        if(input.keyboard_state.is_down(player.up_key))
        {
            player.direction.y=1;
            m_is_moving_ =true;
        }
           
        if(input.keyboard_state.is_down(player.down_key))
        {
            player.direction.y=-1;
            m_is_moving_ =true;
        }
        //normalize the direction
        if(player.direction != glm::vec3(0))
        {
            player.direction = glm::normalize(player.direction);
            
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
