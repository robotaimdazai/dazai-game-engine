#include "game_state_main.h"
#include "../engine/logger.h"
#include "../engine/resource_manager.h"
#include "../engine/ecs/components/sprite_component.h"
#include "../engine/ecs/entities/entity.h"
#include "../engine/ecs/components/component_manager.h"

auto game_state_main::set_game(game* game) -> void
{
    m_game_ = game;
}

auto game_state_main::load() -> void
{
    m_component_manager_ = new component_manager();
    resource_manager::load_texture("assets/textures/dazai.png","dazai",m_game_->window_renderer);
    
    //creating player entity
    constexpr entity player_entity{1};
    const auto player_sprite =m_component_manager_->create_component<sprite_component>();
    player_sprite->texture_id = "dazai";
    player_sprite->set_entity_id(player_entity.id);
    
    m_left_key_ = SDL_SCANCODE_A;
    m_right_key_ = SDL_SCANCODE_D;
    m_up_key_ = SDL_SCANCODE_W;
    m_down_key_ = SDL_SCANCODE_S;
    
}
auto game_state_main::clean() -> void
{
    //delete m_component_manager_;
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
    //replace this with system, sprite render system
    for (const auto sprite: m_component_manager_->get_all_components<sprite_component>())
    {
       resource_manager::get_texture(sprite->texture_id).render(sprite->offset.x,sprite->offset.y,m_game_->window_renderer);
    }
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









