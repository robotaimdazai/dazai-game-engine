#include "../engine/game.h"

#include "game_state_main.h"
#include "../engine/game_state.h"
#include "../engine/resource_manager.h"

game::game():
is_running(false),
window_width(0),
window_height(0)
{
    
}
game::~game()
= default;

auto game::init(const int screen_width, const int screen_height, SDL_Renderer* renderer) -> void
{
    window_width = screen_width;
    window_height = screen_height;
    is_running = true;
    m_input_manager_ = std::make_unique<input_manager>();
    window_renderer = renderer;
}

auto game::load() -> void
{
    //change game state to starting state
    change_state(std::make_unique<game_state_main>());
}

auto game::handle_inputs() -> void
{
    m_input_manager_->prepare_for_update();
    is_running = m_input_manager_->poll_inputs();
    const input_state& input_state = m_input_manager_->get_state();
    m_game_states_.back()->handle_event(input_state);
}

auto game::update(uint32_t delta_time) -> void
{
    m_game_states_.back()->update(delta_time);
}

auto game::render() -> void
{
    m_game_states_.back()->draw();
}

auto game::clean() -> void
{
    resource_manager::clear();
}

auto game::change_state(std::unique_ptr<i_game_state> state) -> void
{
    //clean the current state
    if(!m_game_states_.empty())
    {
        m_game_states_.back()->clean();
        m_game_states_.pop_back();
    }
    //store and load new state
    state->set_game(this);
    m_game_states_.push_back(std::move(state));
    m_game_states_.back()->load();
}

auto game::push_state(std::unique_ptr<i_game_state>) -> void
{
    
}
auto game::pop_state() -> void
{
    
}








