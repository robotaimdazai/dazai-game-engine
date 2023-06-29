#include "renderer2d.h"
#include "globals.h"
#include "index_buffer.h"
#include "resource_manager.h"
#include "shader.h"
#include "vertex_array.h"
#include "ecs/components/component_camera.h"
#include "ecs/components/component_sprite.h"

struct render_state_internal
{
    vertex_array* vao;
    vertex_buffer* vbo;
    index_buffer* ibo;
    shader* shader;
};

static render_state_internal* state;


auto renderer2d::init() -> void
{
    float sprite_vertices[]=
    {
        -0.5f, -0.5f, 0, 0, 0,
         0.5f, -0.5f, 0, 1, 0,        
         0.5f,  0.5f, 0, 1, 1,   
        -0.5f,  0.5f, 0, 0, 1   
    };

    int indices[]
    {
        0,1,2,
        0,3,2
    };
    state = new render_state_internal();
    state->vao = new vertex_array();
    state->vbo = new vertex_buffer(sprite_vertices, 4*5*sizeof(float));
    vertex_buffer_layout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    state->vao->add_buffer(*state->vbo,layout);
    state->ibo =new index_buffer (indices,6);
    state->shader = &resource_manager::get_shader(GLOBALS::SHADER_SPRITE_NAME);
}

auto renderer2d::render_begin() -> void
{
    state->shader->bind();
    state->shader->set_uniform_mat4f("u_proj_view", component_camera::proj * component_camera::view);
}

auto renderer2d::render_end() -> void
{
    
}

auto renderer2d::render_sprite(const glm::vec3& position,const float rot_z ,const component_sprite& sprite) -> void

{
    float sprite_vertices[]=
    {
        -0.5f, -0.5f, 0, sprite.clip.position.x, sprite.clip.position.y,
         0.5f, -0.5f, 0, sprite.clip.size.x, sprite.clip.position.y,        
         0.5f,  0.5f, 0, sprite.clip.size.x, sprite.clip.size.y,   
        -0.5f,  0.5f, 0, sprite.clip.position.x, sprite.clip.size.y   
    };
    state->vao->bind();
    state->vbo->update(sprite_vertices);
    state->vbo->bind();
    auto model = glm::translate(glm::mat4(1.0f),position+ sprite.offset);
    model = glm::rotate(model,glm::radians(rot_z),glm::vec3(0,0,1));
    model = glm::scale(model, glm::vec3(sprite.size.x,sprite.size.y,1.0f));
    auto texture = resource_manager::get_texture(sprite.texture_id);
    texture.bind();
    state->shader->set_uniform4f("u_color",sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a);
    state->shader->set_uniform1i("u_texture",texture.get_slot());
    state->shader->set_uniform_mat4f("u_model",model);
    glDrawElements(GL_TRIANGLES,state->ibo->get_count(),GL_UNSIGNED_INT,nullptr);
}

auto renderer2d::shutdown() -> void
{
    delete state;
}
 