#include "renderer2d.h"
#include <array>
#include "globals.h"
#include "index_buffer.h"
#include "resource_manager.h"
#include "shader.h"
#include "vertex_array.h"
#include "ecs/components/component_camera.h"
#include "ecs/components/component_sprite.h"

struct quad_vertex
{
    glm::vec3 position;
    glm::vec2 tex_coord;
    glm::vec4 color;
};

struct render_state_internal
{
    static constexpr int max_quad = 10000; // max number of quads that can be batched
    static constexpr int max_vertices = 40000; // max number of vertices required to batch
    static constexpr int max_indices = 60000; // max number of indices required to batch
    
    vertex_array* vao{};
    vertex_buffer* vbo{};
    index_buffer* ibo{};
    shader* shader{};
    std::array<quad_vertex,max_vertices> quad_vertices{};
    texture2d texture{};
    unsigned int index_buffer_count =0;

    quad_vertex* vertex_start= nullptr; // points to start of vertex buffer data
    quad_vertex* vertex_ptr= nullptr;  //points to end of batch data
    
};



static render_state_internal* state;


auto renderer2d::init() -> void
{
    state = new render_state_internal();
    state->vao = new vertex_array();
    state->vbo = new vertex_buffer( render_state_internal::max_vertices * sizeof(quad_vertex));
    vertex_buffer_layout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    layout.push<float>(4);
    state->vao->add_buffer(*state->vbo,layout);
    int indices[render_state_internal::max_indices];
    int offset = 0;
    for(int i=0; i<render_state_internal::max_indices;i+=6)
    {
        indices[i + 0] =   offset  +0;
        indices[i + 1] =   offset  +1;
        indices[i + 2] =   offset  +2;
        indices[i + 3] =   offset  +2;
        indices[i + 4] =   offset  +3;
        indices[i + 5] =   offset  +0;

        offset+=4;
    }
    state->ibo =new index_buffer (indices,render_state_internal::max_indices);
    state->shader = &resource_manager::get_shader(GLOBALS::SHADER_SPRITE_NAME);
}

auto renderer2d::render_begin() -> void
{
    state->shader->bind();
    state->shader->set_uniform_mat4fv("u_proj_view", component_camera::proj * component_camera::view);
    state->vertex_start = state->quad_vertices.data();
    state->vertex_ptr = state->quad_vertices.data();
    state->index_buffer_count =0;
}

auto renderer2d::render_end() -> void
{
    state->vao->bind();
    const unsigned int vertex_buffer_size = reinterpret_cast<uint8_t*>(state->vertex_ptr) - reinterpret_cast<uint8_t*>(state->vertex_start);
    state->vbo->set_data(state->quad_vertices.data(),vertex_buffer_size);
    state->vbo->bind();
    state->shader->bind();
    state->texture.bind();
    state->shader->set_uniform1i("u_texture",state->texture.get_slot());
    flush();
}

auto renderer2d::flush() -> void
{
    glDrawElements(GL_TRIANGLES,state->index_buffer_count,GL_UNSIGNED_INT,nullptr);
}

auto renderer2d::render_sprite(const glm::vec3& position,const float rot_z ,const component_sprite& sprite) -> void
{
    auto model = glm::translate(glm::mat4(1.0f),position+ sprite.offset);
    model = glm::rotate(model,glm::radians(rot_z),glm::vec3(0,0,1));
    model = glm::scale(model, glm::vec3(sprite.size.x,sprite.size.y,1.0f));

    
    //vertex 1
    glm::vec3 pos ={-0.5f, -0.5f, 0};
    glm::vec4 transformed_vertex = model * glm::vec4(pos,1); 
    state->vertex_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertex_ptr->tex_coord={sprite.clip.position.x,    sprite.clip.position.y};
    state->vertex_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertex_ptr++;
    //vertex 2
    pos= {0.5f, -0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertex_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertex_ptr->tex_coord={sprite.clip.size.x,        sprite.clip.position.y};
    state->vertex_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertex_ptr++;
    //vertex 3
    pos ={0.5f,  0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertex_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertex_ptr->tex_coord={sprite.clip.size.x,        sprite.clip.size.y};
    state->vertex_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertex_ptr++;
    //vertex 4
    pos = {-0.5f,  0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertex_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertex_ptr->tex_coord={sprite.clip.position.x,    sprite.clip.size.y};
    state->vertex_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertex_ptr++;
    
    state->texture=resource_manager::get_texture(sprite.texture_id); //TODO:this needs to be replaced by atlas texture
    state->index_buffer_count+=6;
}

auto renderer2d::shutdown() -> void
{
    delete state;
}
 