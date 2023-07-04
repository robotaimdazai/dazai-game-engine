#include "renderer2d.h"

#include <algorithm>
#include <array>
#include "globals.h"
#include "index_buffer.h"
#include "resource_manager.h"
#include "shader.h"
#include "vertex_array.h"
#include "ecs/components/component_camera.h"
#include "ecs/components/component_sprite.h"

struct vertex
{
    glm::vec3 position;
    glm::vec2 tex_coord;
    glm::vec4 color;
    float tex_id;
};

struct batch
{
    vertex* vertex_start= nullptr;
    vertex* vertex_ptr= nullptr;
    int index_offset =0;
    int index_count=0;
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
    batch batch{};
    
    std::array<vertex,max_vertices> quad_vertices{};
    std::unordered_map<uint32_t,texture2d>renderer_id_to_texture;// remove it from here
    
    vertex* vertices_start= nullptr; // points to start of vertex buffer data
    vertex* vertices_ptr= nullptr;  //points to end of vertex data
    int* indices_start=nullptr;

    int index_buffer_count =0;
    
};



static render_state_internal* state;


auto renderer2d::init() -> void
{
    state = new render_state_internal();
    state->vao = new vertex_array();
    state->vbo = new vertex_buffer( render_state_internal::max_vertices * sizeof(vertex));
    vertex_buffer_layout layout;
    layout.push<float>(3);          // pos
    layout.push<float>(2);          // uv
    layout.push<float>(4);          //color
    layout.push<float>(1);          //texture id
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
    state->indices_start = indices;
    state->shader = &resource_manager::get_shader(GLOBALS::SHADER_SPRITE_NAME);
}

auto renderer2d::render_begin() -> void
{
    state->shader->bind();
    state->shader->set_uniform_mat4fv("u_proj_view", component_camera::proj * component_camera::view);
    state->vertices_start = state->quad_vertices.data();
    state->vertices_ptr = state->quad_vertices.data();
    state->index_buffer_count =0;
}
auto renderer2d::render_end() -> void
{
    if(state->vertices_start == state->vertices_ptr)return;
    const unsigned int vbo_size_bytes = reinterpret_cast<uint8_t*>(state->vertices_ptr) - reinterpret_cast<uint8_t*>(state->vertices_start);
    const unsigned int vbo_count =state->vertices_ptr - state->vertices_start;
    
    //sort array for batches, use radix sort for efficient batching and also store id as 32 bit int for different properties
    std::sort(state->vertices_start,state->vertices_ptr-1,[](const vertex& v1,const vertex& v2) 
    {
        return v1.tex_id<v2.tex_id;
    });
    
    state->vao->bind();
    state->vbo->set_data(state->quad_vertices.data(),vbo_size_bytes);
    state->vbo->bind();
   
    
    state->batch.index_offset= 0;
    state->batch.index_count =0;
    state->batch.vertex_start = state->vertices_start;
    state->batch.vertex_ptr = state->vertices_start;
    

    for(int i=0; i<vbo_count; i++)
    {
        if(state->batch.vertex_ptr->tex_id!=state->batch.vertex_start->tex_id)
        {
            //set texture
            //flush
            //update index offset and vertex start
            auto texture2d = state->renderer_id_to_texture[state->batch.vertex_start->tex_id];
            texture2d.bind();
            state->shader->set_uniform1i("u_texture",texture2d.get_slot());
            
            flush(state->batch.index_count,state->batch.index_offset);
            
            state->batch.index_offset = state->batch.index_count;
            state->batch.vertex_start =state->batch.vertex_ptr;
        }
        
        state->batch.vertex_ptr++;
        if((i+1)%4==0)
        {
            state->batch.index_count+=6;
        }
    }
    //set texture and flush
    auto texture2d = state->renderer_id_to_texture[state->batch.vertex_start->tex_id];
    texture2d.bind();
    state->shader->set_uniform1i("u_texture",texture2d.get_slot());
    
    flush(state->batch.index_count,state->batch.index_offset);
    
}

auto renderer2d::flush(const int indices, int offset) -> void
{
    if(indices==0)
        glDrawElements(GL_TRIANGLES,state->index_buffer_count,GL_UNSIGNED_INT,nullptr);
    else
        glDrawElements(GL_TRIANGLES,indices,GL_UNSIGNED_INT,(void*)(offset * sizeof(int)));
}

auto renderer2d::render_sprite(const glm::vec3& position,const float rot_z ,const component_sprite& sprite) -> void
{
    auto model = glm::translate(glm::mat4(1.0f),position+ sprite.offset);
    model = glm::rotate(model,glm::radians(rot_z),glm::vec3(0,0,1));
    model = glm::scale(model, glm::vec3(sprite.size.x,sprite.size.y,1.0f));
    auto& texture = resource_manager::get_texture(sprite.texture_id);
    state->renderer_id_to_texture[texture.get_renderer_id()] = texture;
    
    //vertex 1
    glm::vec3 pos ={-0.5f, -0.5f, 0};
    glm::vec4 transformed_vertex = model * glm::vec4(pos,1); 
    state->vertices_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertices_ptr->tex_coord={sprite.clip.position.x,    sprite.clip.position.y};
    state->vertices_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertices_ptr->tex_id ={(float)texture.get_renderer_id()};
    state->vertices_ptr++;
    //vertex 2
    pos= {0.5f, -0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertices_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertices_ptr->tex_coord={sprite.clip.size.x,        sprite.clip.position.y};
    state->vertices_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertices_ptr->tex_id ={(float)texture.get_renderer_id()};
    state->vertices_ptr++;
    //vertex 3
    pos ={0.5f,  0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertices_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertices_ptr->tex_coord={sprite.clip.size.x,        sprite.clip.size.y};
    state->vertices_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertices_ptr->tex_id ={(float)texture.get_renderer_id()};
    state->vertices_ptr++;
    //vertex 4
    pos = {-0.5f,  0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertices_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertices_ptr->tex_coord={sprite.clip.position.x,    sprite.clip.size.y};
    state->vertices_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertices_ptr->tex_id ={(float)texture.get_renderer_id()};
    state->vertices_ptr++;
    
    state->index_buffer_count+=6;
}

auto renderer2d::shutdown() -> void
{
    delete state;
}
 