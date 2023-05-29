#include "sprite_system.h"
#include "../../resource_manager.h"

sprite_system::sprite_system(SDL_Renderer* renderer,component_manager<sprite_component>* sprite_component_manager):
    m_sprite_component_manager_(sprite_component_manager), m_renderer_(renderer) {}
 
auto sprite_system::init() ->void
{
    
}

auto sprite_system::render() ->void
{
  for(auto sprite: m_sprite_component_manager_->get_components())
  {
      resource_manager::get_texture(sprite->texture_id).render(sprite->offset.x,sprite->offset.y,m_renderer_);
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
