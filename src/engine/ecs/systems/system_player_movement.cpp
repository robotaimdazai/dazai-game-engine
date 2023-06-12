#include "system_player_movement.h"
#include "../ecs.h"
#include "../components/player_movement.h"
#include "../components/transform.h"
#include "glm/gtx/dual_quaternion.hpp"

extern ecs g_ecs;
auto system_player_movement::update(const float delta_time) -> void
{
    for (auto const& entity:entities)
    {
        auto& player = g_ecs.get_component<player_movement>(entity);
        auto& player_transform = g_ecs.get_component<transform>(entity);
        player_transform.position += m_direction_ * player.speed * delta_time;
    }
}

auto system_player_movement::handle_event(const input_state& input) -> void
{
    for (auto const& entity:entities)
    {
        const auto& player = g_ecs.get_component<player_movement>(entity);
        m_direction_.x=0;
        m_direction_.y=0;
        if(input.keyboard_state.is_down(player.left_key))
            m_direction_.x=-1;
        if(input.keyboard_state.is_down(player.right_key))
            m_direction_.x=1;
        if(input.keyboard_state.is_down(player.up_key))
            m_direction_.y=1;
        if(input.keyboard_state.is_down(player.down_key))
            m_direction_.y=-1;
        //normalize the direction
        if(m_direction_ != glm::vec3(0))
            m_direction_ = glm::normalize(m_direction_);
        
    }
    
}
