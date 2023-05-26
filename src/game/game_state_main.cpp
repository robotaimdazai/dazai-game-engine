#include "game_state_main.h"
#include "../engine/logger.h"
#include "../engine/resource_manager.h"

game_state_main::game_state_main()= default;

game_state_main::~game_state_main()
{
    clean();
}
auto game_state_main::set_game(game* game) -> void
{
    m_game_ = game;
}

auto game_state_main::load() -> void
{
    m_left_key_ = SDL_SCANCODE_A;
    m_right_key_ = SDL_SCANCODE_D;
    m_up_key_ = SDL_SCANCODE_W;
    m_down_key_ = SDL_SCANCODE_S;
    resource_manager::load_texture("assets/textures/dazai.png","dazai",m_game_->window_renderer);
}
auto game_state_main::clean() -> void
{
    
}
auto game_state_main::pause() -> void
{
    
}
auto game_state_main::resume() -> void
{
    
}
auto game_state_main::update(const uint32_t delta_time) -> void
{
    m_counter_+=delta_time;
}

auto game_state_main::draw() -> void
{
    resource_manager::get_texture("dazai").render(0,0,m_game_->window_renderer);
}
auto game_state_main::handle_event(const input_state& input_state) -> void
{
    if(input_state.keyboard_state.is_just_pressed(SDL_Scancode(m_left_key_)))
    {
        LOG(info)<<"left key pressed";
    }
    if(input_state.keyboard_state.is_just_pressed(SDL_Scancode(m_right_key_)))
    {
        LOG(info)<<"right key pressed";
    }
    if(input_state.keyboard_state.is_just_pressed(SDL_Scancode(m_down_key_)))
    {
        LOG(info)<<"down key pressed";
    }
    if(input_state.keyboard_state.is_just_pressed(SDL_Scancode(m_up_key_)))
    {
        LOG(info)<<"up key pressed";
    }
}









