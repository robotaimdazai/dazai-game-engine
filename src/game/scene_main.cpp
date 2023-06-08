#include "scene_main.h"

#include "imgui.h"
#include "../engine/resource_manager.h"
#include "../engine/ecs/ecs.h"
#include "../engine/ecs/components/sprite.h"
#include "../engine/ecs/systems/sprite_system.h"

ecs g_ecs;
sprite_system* g_sprite_system;

auto scene_main::set_game(game* game) -> void
{
    m_game_ = game;
    g_ecs.init();
    g_ecs.register_component<sprite>();
    g_sprite_system = g_ecs.register_system<sprite_system>().get();
    signature sprite_system_signature;
    sprite_system_signature.set(g_ecs.get_component_type<sprite>());
    g_ecs.set_system_signature<sprite_system>(sprite_system_signature);

}

auto scene_main::load() -> void
{
    //load all resources
    resource_manager::load_texture("assets/textures/dazai.png","dazai",m_game_->window_renderer);
    auto player = g_ecs.add_entity();
    g_ecs.add_component<sprite>(player);
    auto& player_sprite =g_ecs.get_component<sprite>(player);
    player_sprite.texture = resource_manager::get_texture("dazai");
    player_sprite.renderer = m_game_->window_renderer;
    
    
}

auto scene_main::update(const uint32_t delta_time) -> void
{

}

auto scene_main::render() -> void
{
    //render all entities
    g_sprite_system->render();
}

auto scene_main::handle_event(const input_state& input_state) -> void
{
   
}


auto scene_main::pause() -> void
{
    
}
auto scene_main::resume() -> void
{
    
}

auto scene_main::clean() -> void
{
   
}

auto scene_main::on_gui() -> void
{
    ImGui::Begin("Debug");
    ImGui::End();
}




