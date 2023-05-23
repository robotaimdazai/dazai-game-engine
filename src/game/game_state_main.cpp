#include "game_state_main.h"

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
    
}








