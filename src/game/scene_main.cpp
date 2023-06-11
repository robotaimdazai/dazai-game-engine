#include "scene_main.h"
#include "imgui.h"
#include "../engine/resource_manager.h"
#include "../engine/ecs/ecs.h"
#include "../engine/ecs/components/camera.h"
#include "../engine/ecs/components/sprite.h"
#include "../engine/ecs/components/transform.h"
#include "../engine/ecs/systems/renderer_sprite.h"
#include "../engine/ecs/systems/system_camera.h"

ecs g_ecs;
std::shared_ptr<system_camera> g_camera_system;
std::shared_ptr<renderer_sprite> g_sprite_system;


//entities/gameobjects  in scene
entity g_player;
entity g_camera;

auto scene_main::set_game(game* game) -> void
{
    m_game_ = game;
    g_ecs.init();
    
    //register components first
    g_ecs.register_component<sprite>();
    g_ecs.register_component<transform>();
    g_ecs.register_component<camera>();
    //loading shader for sprite renderer
    resource_manager::load_shader(SHADER_SPRITE_PATH, SHADER_SPRITE_NAME);
    auto sprite_shader =resource_manager::get_shader(SHADER_SPRITE_NAME);
    //registering sprite system
    g_sprite_system = g_ecs.register_system<renderer_sprite>(sprite_shader);
    signature sprite_system_signature;
    sprite_system_signature.set(g_ecs.get_component_type<sprite>());
    sprite_system_signature.set(g_ecs.get_component_type<transform>());
    g_ecs.set_system_signature<renderer_sprite>(sprite_system_signature);
    

    //registering camera system
    g_camera_system = g_ecs.register_system<system_camera>();
    signature camera_signature;
    camera_signature.set(g_ecs.get_component_type<transform>());
    camera_signature.set(g_ecs.get_component_type<camera>());
    g_ecs.set_system_signature<system_camera>(camera_signature);
    

}

auto scene_main::load() -> void
{
    //load all resources
    resource_manager::load_texture("assets/textures/dazai.png","dazai");
    g_player = g_ecs.add_entity();
    g_ecs.add_component<transform>(g_player);
    g_ecs.add_component<sprite>(g_player);
    auto& player_sprite =g_ecs.get_component<sprite>(g_player);
    player_sprite.texture = "dazai";

    //create camera
    g_camera = g_ecs.add_entity();
    g_ecs.add_component<transform>(g_camera);
    g_ecs.add_component<camera>(g_camera);
    
    
}

auto scene_main::update(const uint32_t delta_time) -> void
{
    g_camera_system->update();
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
    
    ImGui::SliderFloat3("camera",&g_ecs.get_component<transform>(g_camera).position.x,-1280.0f,1280.0f);
    
    ImGui::End();
}




