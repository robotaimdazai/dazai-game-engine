#include "game_state_main.h"
#include "../engine/resource_manager.h"

auto game_state_main::set_game(game* game) -> void
{
    m_game_ = game;

}

auto game_state_main::load() -> void
{
    //load all resources
    resource_manager::load_texture("assets/textures/dazai.png","dazai",m_game_->window_renderer);
    
}

auto game_state_main::update(const uint32_t delta_time) -> void
{

}

auto game_state_main::render() -> void
{
  
}

auto game_state_main::handle_event(const input_state& input_state) -> void
{
   
}


auto game_state_main::pause() -> void
{
    
}
auto game_state_main::resume() -> void
{
    
}

auto game_state_main::clean() -> void
{
   
}




