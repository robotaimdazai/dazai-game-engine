#include "sprite_system.h"
#include "../../resource_manager.h"
#include "../entities/entity_manager.h"

sprite_system::sprite_system(SDL_Renderer* renderer):
    m_renderer_(renderer) {}
 
auto sprite_system::init() ->void
{
    m_sprite_component_manager_ = entity_manager::get_component_manager<sprite_component>();
    if(m_sprite_component_manager_ == nullptr)
    {
        LOG(error) << "Sprite system can't init sprite component manager is null";
    }
}

auto sprite_system::render() ->void
{
    if(m_sprite_component_manager_ == nullptr)
    {
        return;
    }
    for (const auto& sprite: m_sprite_component_manager_->get_components())
    {
        resource_manager::get_texture(sprite->texture_id).render(sprite->offset.x, sprite->offset.y, m_renderer_);
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
