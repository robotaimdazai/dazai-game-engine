#include "scene_main.h"
#include "imgui.h"
#include "../engine/debug_draw.h"
#include "../engine/physics2d.h"
#include "../engine/resource_manager.h"
#include "../engine/ecs/ecs.h"
#include "../engine/ecs/components/component_animator.h"
#include "../engine/ecs/components/component_box_collider.h"
#include "../engine/ecs/components/component_camera.h"
#include "../engine/ecs/components/component_player_input.h"
#include "../engine/ecs/components/component_rigidbody2d.h"
#include "../engine/ecs/components/component_sprite.h"
#include "../engine/ecs/components/component_transform.h"
#include "../engine/ecs/systems/system_renderer_sprite.h"
#include "../engine/ecs/systems/system_animation.h"
#include "../engine/ecs/systems/system_camera.h"
#include "../engine/ecs/systems/system_collider_renderer.h"
#include "../engine/ecs/systems/system_collision_box.h"
#include "../engine/ecs/systems/system_player_input.h"
#include "../engine/ecs/systems/system_rigidbody2d.h"

ecs g_ecs;
std::shared_ptr<system_camera> g_camera_system;
std::shared_ptr<system_renderer_sprite> g_sprite_system;
std::shared_ptr<system_player_input> g_player_movement;
std::shared_ptr<system_animation> g_animation_system;
std::shared_ptr<system_collision_box> g_collision_detection_system;
std::shared_ptr<system_collider_renderer> g_collider_renderer;
std::shared_ptr<system_rigidbody2d> g_rigidbody_system;


//entities/gameobjects  in scene
entity g_player;
entity g_camera;

auto scene_main::set_game(game* game) -> void
{
    m_game_ = game;
    g_ecs.init();
    
    //register components first
    g_ecs.register_component<component_sprite>();
    g_ecs.register_component<component_transform>();
    g_ecs.register_component<component_camera>();
    g_ecs.register_component<component_player_input>();
    g_ecs.register_component<component_animator>();
    g_ecs.register_component<component_box_collider>();
    g_ecs.register_component<component_rigidbody2d>();
    
    //loading shader for sprite renderer
    resource_manager::load_shader(GLOBALS::SHADER_SPRITE_PATH, GLOBALS::SHADER_SPRITE_NAME);
    resource_manager::load_shader(GLOBALS::SHADER_DEBUG_PATH, GLOBALS::SHADER_DEBUG_NAME);
    
    //registering sprite system
    g_sprite_system = g_ecs.register_system<system_renderer_sprite>();
    signature sprite_system_signature;
    sprite_system_signature.set(g_ecs.get_component_type<component_sprite>());
    sprite_system_signature.set(g_ecs.get_component_type<component_transform>());
    g_ecs.set_system_signature<system_renderer_sprite>(sprite_system_signature);
    

    //registering camera system
    g_camera_system = g_ecs.register_system<system_camera>();
    signature camera_signature;
    camera_signature.set(g_ecs.get_component_type<component_transform>());
    camera_signature.set(g_ecs.get_component_type<component_camera>());
    g_ecs.set_system_signature<system_camera>(camera_signature);

    //registering player input system
    g_player_movement = g_ecs.register_system<system_player_input>();
    signature movement_signature;
    movement_signature.set(g_ecs.get_component_type<component_transform>());
    movement_signature.set(g_ecs.get_component_type<component_player_input>());
    movement_signature.set(g_ecs.get_component_type<component_sprite>());
    movement_signature.set(g_ecs.get_component_type<component_rigidbody2d>());
    g_ecs.set_system_signature<system_player_input>(movement_signature);

    //registering animation system
    g_animation_system = g_ecs.register_system<system_animation>();
    signature animation_signature;
    animation_signature.set(g_ecs.get_component_type<component_sprite>());
    animation_signature.set(g_ecs.get_component_type<component_animator>());
    g_ecs.set_system_signature<system_animation>(animation_signature);

    //registering collider renderer system
    g_collider_renderer = g_ecs.register_system<system_collider_renderer>();
    signature signature_collider_renderer;
    signature_collider_renderer.set(g_ecs.get_component_type<component_transform>());
    signature_collider_renderer.set(g_ecs.get_component_type<component_box_collider>());
    g_ecs.set_system_signature<system_collider_renderer>(signature_collider_renderer);

    //registering collision detection system
    g_collision_detection_system = g_ecs.register_system<system_collision_box>();
    signature signature_collision_detection;
    signature_collision_detection.set(g_ecs.get_component_type<component_transform>());
    signature_collision_detection.set(g_ecs.get_component_type<component_box_collider>());
    g_ecs.set_system_signature<system_collision_box>(signature_collision_detection);

    //registering rigidbody system
    g_rigidbody_system = g_ecs.register_system<system_rigidbody2d>();
    signature signature_rigidbody;
    signature_rigidbody.set(g_ecs.get_component_type<component_transform>());
    signature_rigidbody.set(g_ecs.get_component_type<component_rigidbody2d>());
    g_ecs.set_system_signature<system_rigidbody2d>(signature_rigidbody);
    
}

auto scene_main::load() -> void
{
    //load all resources
    resource_manager::load_texture("assets/textures/dazai-sheet.png","dazai");
    
    //player
    g_player = g_ecs.add_entity();
    g_ecs.add_component<component_transform>(g_player);
    auto& player_transform =g_ecs.get_component<component_transform>(g_player);
    player_transform.position={0,0,0};
    g_ecs.add_component<component_sprite>(g_player);
    g_ecs.add_component<component_player_input>(g_player);
    auto& player_sprite =g_ecs.get_component<component_sprite>(g_player);
    player_sprite.texture_id ="dazai";
    player_sprite.size ={128,128};
    g_ecs.add_component<component_animator>(g_player);
    player_sprite.is_animated = true;
    auto& player_animator = g_ecs.get_component<component_animator>(g_player);
    player_animator.animations.emplace("idle",component_animation(0,{32,31},13,8));
    player_animator.animations.emplace("run",component_animation(1,{32,32},8,20));
    player_animator.animations.emplace("attack",component_animation(4,{32,32},10,30,true));
    player_animator.change_animation("idle");
    //add collider to player
    g_ecs.add_component<component_box_collider>(g_player);
    auto& collider = g_ecs.get_component<component_box_collider>(g_player);
    collider.size ={64,96};
    collider.offset = {-32,-48};
    collider.is_trigger =false;
    //add rigidbody to player
    g_ecs.add_component<component_rigidbody2d>(g_player);

    //create a block for collision detection
    auto g_block = g_ecs.add_entity();
    g_ecs.add_component<component_transform>(g_block);
    g_ecs.add_component<component_box_collider>(g_block);
    auto& block_transform = g_ecs.get_component<component_transform>(g_block);
    block_transform.position ={150,60,0};

    auto g_block2 = g_ecs.add_entity();
    g_ecs.add_component<component_transform>(g_block2);
    g_ecs.add_component<component_box_collider>(g_block2);
    auto& block2_transform = g_ecs.get_component<component_transform>(g_block2);
    block2_transform.position ={250,60,0};

    auto g_block3 = g_ecs.add_entity();
    auto& block3_transform = g_ecs.add_component<component_transform>(g_block3);
    g_ecs.add_component<component_box_collider>(g_block3);
    block3_transform.position ={350,60,0};
    
    //create camera
    g_camera = g_ecs.add_entity();
    g_ecs.add_component<component_transform>(g_camera);
    g_ecs.add_component<component_camera>(g_camera);
    
}

auto scene_main::update(const float delta_time) -> void
{
    g_camera_system->update();
    g_animation_system->update(delta_time);
}

auto scene_main::fixed_update(float fixed_delta_time) -> void
{
    g_rigidbody_system->fixed_update(fixed_delta_time);
    g_collision_detection_system->fixed_update(fixed_delta_time);
}

auto scene_main::render() -> void
{
    //render all entities
    g_sprite_system->render();
}
glm::vec2 mouse_pos;
auto scene_main::handle_event(const input_state& input_state) -> void
{
    g_player_movement->handle_event(input_state);
    mouse_pos = component_camera::screen_to_world_pos(input_state.mouse_state.get_mouse_pos());
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
    ImGui::Text("Camera");
    ImGui::SliderFloat3("position",&g_ecs.get_component<component_transform>(g_camera).position.x,-1280.0f,1280.0f);
    ImGui::SliderFloat("zoom",&g_ecs.get_component<component_camera>(g_camera).zoom,0,10.0f);
    ImGui::End();
}

auto scene_main::on_debug_draw() -> void
{
    g_collider_renderer->render();
    g_collision_detection_system->debug_draw();
   
}




