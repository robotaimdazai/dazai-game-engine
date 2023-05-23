#include "../engine/game.h"
#include "../engine/game_state.h"

game::game():
is_running(false),
window_width(0),
window_height(0)
{
    
}
game::~game()
= default;

auto game::init(const int screen_width, const int screen_height) -> void
{
    window_width = screen_width;
    window_height = screen_height;
    is_running = true;
}

auto game::load() -> void
{
    
}

auto game::handle_inputs() -> void
{
    
}

auto game::update(uint32_t delta_time) -> void
{
    
}

auto game::render() -> void
{
    
}

auto game::clean() -> void
{
    
}

auto game::change_state(std::unique_ptr<game_state> state) -> void
{
    
}

auto game::push_state(std::unique_ptr<game_state>) -> void
{
    
}
auto game::pop_state() -> void
{
    
}








