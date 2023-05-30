﻿#include "sprite_system.h"
#include "../../resource_manager.h"

sprite_system::sprite_system(const game *game, component_manager<sprite_component> *sprite_component_manager):
    m_renderer_(game->window_renderer), m_sprite_component_manager_(sprite_component_manager) {}
 
auto sprite_system::init() ->void
{
    if(m_sprite_component_manager_==nullptr)
    {
        LOG(warning)<< "sprite system component manager was null at init";
    }
}

auto sprite_system::render() ->void
{
    if(m_sprite_component_manager_==nullptr)
    {
        return;
    }
    for (const auto sprite: m_sprite_component_manager_->get_components())
    {
        resource_manager::get_texture(sprite.texture_id).render(sprite.offset.x, sprite.offset.y, m_renderer_);
    }
}

auto sprite_system::update(uint32_t delta_time) ->void
{
   
}
auto sprite_system::handle_event(const input_state& input_state) ->void
{
    
}

auto sprite_system::clean() ->void
{
}