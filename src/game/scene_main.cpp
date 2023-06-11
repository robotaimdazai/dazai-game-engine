#include "scene_main.h"
#include "imgui.h"
#include "../engine/resource_manager.h"
#include "../engine/ecs/ecs.h"
#include "../engine/ecs/components/sprite.h"
#include "../engine/ecs/components/transform.h"
#include "../engine/ecs/systems/renderer_sprite.h"
#include "glm/ext/matrix_clip_space.hpp"

ecs g_ecs;
std::shared_ptr<renderer_sprite> g_sprite_system;
entity g_player;

auto scene_main::set_game(game* game) -> void
{
    
    m_game_ = game;
    g_ecs.init();
    g_ecs.register_component<sprite>();
    g_ecs.register_component<transform>();
    //loading shader
    resource_manager::load_shader(SHADER_SPRITE_PATH, SHADER_SPRITE_NAME);
    auto sprite_shader =resource_manager::get_shader(SHADER_SPRITE_NAME);
    
    //registering sprite system
    g_sprite_system = g_ecs.register_system<renderer_sprite>(sprite_shader);
    signature sprite_system_signature;
    sprite_system_signature.set(g_ecs.get_component_type<sprite>());
    sprite_system_signature.set(g_ecs.get_component_type<transform>());
    g_ecs.set_system_signature<renderer_sprite>(sprite_system_signature);

    //setting projection
    glm::mat4 proj = glm::ortho(0.0f,(float)game->window_width,0.0f,(float)game->window_height,-1.0f,1.0f);
    //setting view aka camera
    glm::mat4 view = glm::mat4(1.0f);
    //bind shader
    sprite_shader.bind();
    sprite_shader.set_uniform_mat4f("u_proj",proj);
    sprite_shader.set_uniform_mat4f("u_view",view);

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
    ImGui::SliderFloat3("Pos",&g_ecs.get_component<transform>(g_player).position.x,0.0f,1280.0f);
    
    ImGui::End();
}




