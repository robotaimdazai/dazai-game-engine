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
        player_transform.position += player.direction * player.speed * delta_time;
    }
}

auto system_player_movement::handle_event(const input_state& input) -> void
{
    for (auto const& entity:entities)
    {
        auto& player = g_ecs.get_component<player_movement>(entity);
        player.direction.x=0;
        player.direction.y=0;
        if(input.keyboard_state.is_down(player.left_key))
            player.direction.x=-1;
        if(input.keyboard_state.is_down(player.right_key))
            player.direction.x=1;
        if(input.keyboard_state.is_down(player.up_key))
            player.direction.y=1;
        if(input.keyboard_state.is_down(player.down_key))
            player.direction.y=-1;
        //normalize the direction
        if(player.direction != glm::vec3(0))
            player.direction = glm::normalize(player.direction);
        
    }
    
}
