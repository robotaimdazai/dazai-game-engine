#include "game_state_main.h"
#include "../engine/resource_manager.h"
#include "../engine/ecs/components/component_manager.h"
#include "../engine/ecs/entities/entity.h"
#include "../engine/ecs/entities/entity_manager.h"
#include "../engine/ecs/systems/sprite_system.h"
#include "../engine/ecs/systems/system_manager.h"
#include "../engine/ecs/components/sprite_component.h"

component_manager<sprite_component>* g_sprite_component_manager;

auto game_state_main::set_game(game* game) -> void
{
    m_game_ = game;
    //init component managers here
    g_sprite_component_manager = new component_manager<sprite_component>();
    //create and register systems here
    system_manager::register_system(new sprite_system(m_game_->window_renderer, g_sprite_component_manager));
}

auto game_state_main::load() -> void
{
    //load all resources
    resource_manager::load_texture("assets/textures/dazai.png","dazai",m_game_->window_renderer);
    //init all systems
    system_manager::init();
    //creating player entity
    const auto player_entity =entity_manager::create_entity();
    g_sprite_component_manager->add_component(player_entity.id)->texture_id = "dazai";
}
auto game_state_main::clean() -> void
{
    entity_manager::clean();
    system_manager::clean();
}
auto game_state_main::pause() -> void
{
    
}
auto game_state_main::resume() -> void
{
    
}

auto game_state_main::update(const uint32_t delta_time) -> void
{
    system_manager::update(delta_time);
}

auto game_state_main::render() -> void
{
    system_manager::render();
}

auto game_state_main::handle_event(const input_state& input_state) -> void
{
    system_manager::handle_event(input_state);
}





