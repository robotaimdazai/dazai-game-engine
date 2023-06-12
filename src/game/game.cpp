#include "../engine/game.h"
#include "scene_main.h"
#include "../engine/scene.h"
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
    window_renderer = renderer;
    m_input_manager_ = std::make_unique<input_manager>();
}

auto game::load() -> void
{
    //change game state to starting state
    change_scene(std::make_unique<scene_main>());
}

auto game::handle_inputs() -> void
{
    m_input_manager_->prepare_for_update();
    is_running = m_input_manager_->poll_inputs();
    const input_state& input_state = m_input_manager_->get_state();
    m_game_scenes_.back()->handle_event(input_state);
}

auto game::update(float delta_time) -> void
{
    m_game_scenes_.back()->update(delta_time);
}

auto game::render() -> void
{
    m_game_scenes_.back()->render();
}

auto game::clean() -> void
{
    resource_manager::clear();
}

auto game::change_scene(std::unique_ptr<i_scene> state) -> void
{
    //clean the current state
    if(!m_game_scenes_.empty())
    {
        m_game_scenes_.back()->clean();
        m_game_scenes_.pop_back();
    }
    //store and load new state
    state->set_game(this);
    m_game_scenes_.push_back(std::move(state));
    m_game_scenes_.back()->load();
}

auto game::push_scene(std::unique_ptr<i_scene>) -> void
{
    
}
auto game::pop_scene() -> void
{
    
}

auto game::on_gui() -> void
{
    m_game_scenes_.back()->on_gui();
}



