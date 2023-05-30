#include "game_state_main.h"
#include "../engine/resource_manager.h"
#include "../engine/ecs/components/component_manager.h"
#include "../engine/ecs/entities/entity.h"
#include "../engine/ecs/entities/entity_manager.h"
#include "../engine/ecs/systems/sprite_system.h"
#include "../engine/ecs/systems/system_manager.h"
#include "../engine/ecs/components/sprite_component.h"

entity_manager* g_entity_manager;
system_manager* g_system_manager;

auto game_state_main::set_game(game* game) -> void
{
    m_game_ = game;
    g_entity_manager = new entity_manager();
    g_system_manager = new system_manager();
    g_entity_manager->add_component_manager<sprite_component>();
    g_system_manager->add_system(new sprite_system(m_game_,g_entity_manager->get_component_manager<sprite_component>()));
}

auto game_state_main::load() -> void
{
    //load all resources
    resource_manager::load_texture("assets/textures/dazai.png","dazai",m_game_->window_renderer);
    //init all systems
    g_system_manager->init();
    //creating player entity
    const auto player_entity = g_entity_manager->add_entity();
    g_entity_manager->add_component<sprite_component>(player_entity);
    g_entity_manager->get_component<sprite_component>(player_entity).texture_id = "dazai";
}

auto game_state_main::update(const uint32_t delta_time) -> void
{
    g_system_manager->update(delta_time);
}

auto game_state_main::render() -> void
{
    g_system_manager->render();
}

auto game_state_main::handle_event(const input_state& input_state) -> void
{
    g_system_manager->handle_event(input_state);
}


auto game_state_main::pause() -> void
{
    
}
auto game_state_main::resume() -> void
{
    
}

auto game_state_main::clean() -> void
{
    g_entity_manager->clean();
    g_system_manager->clean();
}




