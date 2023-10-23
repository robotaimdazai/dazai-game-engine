#include "renderer2d.h"

#include <algorithm>
#include <array>
#include "globals.h"
#include "index_buffer.h"
#include "resource_manager.h"
#include "shader.h"
#include "util.h"
#include "vertex_array.h"
#include "ecs/components/component_camera.h"
#include "ecs/components/component_sprite.h"

struct vertex_cpu
{
    glm::vec3 position;   
    glm::vec2 tex_coord;  
    glm::vec4 color;      
    texture2d texture2d;
    uint32_t id; // this is a packed integer [Transparency|RenderId] 1 byte each
};

struct vertex_gpu
{
    glm::vec3 position;     //12 bytes
    glm::vec2 tex_coord;    //8 bytes
    glm::vec4 color;        //16 bytes
};

struct batch
{
    vertex_cpu* vertex_start= nullptr;
    vertex_cpu* vertex_ptr= nullptr;
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
    
    std::array<vertex_cpu,max_vertices> cpu_vertices{};
    std::array<vertex_gpu,max_vertices> gpu_vertices{};
    
    vertex_cpu* vertices_start= nullptr; // points to start of vertex buffer data
    vertex_cpu* vertices_ptr= nullptr;  //points to end of vertex data
    int* indices_start=nullptr;

    int index_buffer_count =0;
    
};



static render_state_internal* state;


auto renderer2d::init() -> void
{
    state = new render_state_internal();
    state->vao = new vertex_array();
    state->vbo = new vertex_buffer( render_state_internal::max_vertices * sizeof(vertex_gpu));
    vertex_buffer_layout layout;
    layout.push<float>(3);          // pos
    layout.push<float>(2);          // uv
    layout.push<float>(4);          //color
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
    state->vertices_start = state->cpu_vertices.data();
    state->vertices_ptr = state->cpu_vertices.data();
    state->index_buffer_count =0;
}
auto renderer2d::render_end() -> void
{
    if(state->vertices_start == state->vertices_ptr)return;
    const unsigned int vbo_count =state->vertices_ptr - state->vertices_start;
    const unsigned int vbo_size_bytes =
        reinterpret_cast<uint8_t*>(state->vertices_ptr) -
        reinterpret_cast<uint8_t*>(state->vertices_start);
    
    //sort array for batches, use radix sort for efficient batching and also store id as 32 bit int for different properties
    //TODO: move to radix sort
    std::sort(state->vertices_start,state->vertices_ptr,[](const vertex_cpu& v1,const vertex_cpu& v2) 
    {
        return v1.id<v2.id;
    });
    //sorting make sures all the opaque renderers are at the start
    
    //copy cpu vertex data to gpu, only relevant data is copied
    for(int i=0; i<vbo_count; i++)
    {
        state->gpu_vertices[i].position = state->cpu_vertices[i].position;
        state->gpu_vertices[i].color = state->cpu_vertices[i].color;
        state->gpu_vertices[i].tex_coord = state->cpu_vertices[i].tex_coord;
    }
    
    state->vao->bind();
    state->vbo->set_data(state->gpu_vertices.data(),vbo_count * sizeof(vertex_gpu));
    state->vbo->bind();
   
    
    state->batch.index_offset= 0;
    state->batch.index_count =0;
    state->batch.vertex_start = state->vertices_start;
    state->batch.vertex_ptr = state->vertices_start;
    
    glDisable(GL_BLEND); // render opaque at start
    for(int i=0; i<vbo_count; i++)
    {
        if(util::extract_from_32_bit_integer(state->batch.vertex_ptr->id,1)!=util::extract_from_32_bit_integer(state->batch.vertex_start->id,1) )
        {
            //set blend mode
            //set texture
            //flush
            //update index offset and vertex start
            
            if(util::extract_from_32_bit_integer(state->vertices_ptr->id,2) == transparent)
                glEnable(GL_BLEND);
            
            auto texture2d = state->batch.vertex_start->texture2d;
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
    //set texture and blend mode and flush
    if(util::extract_from_32_bit_integer(state->batch.vertex_ptr->id,2) == transparent)
        glEnable(GL_BLEND);
    
    auto texture2d = state->batch.vertex_start->texture2d;
    texture2d.bind();
    state->shader->set_uniform1i("u_texture",texture2d.get_slot());
    glEnable(GL_BLEND);
    flush(state->batch.index_count,state->batch.index_offset);
    
}

auto renderer2d::flush(const int indices, const int offset) -> void
{
    if(indices==0)
        glDrawElements(GL_TRIANGLES,state->index_buffer_count,GL_UNSIGNED_INT,nullptr);
    else
        glDrawElements(GL_TRIANGLES,indices,GL_UNSIGNED_INT,(void*)(offset * sizeof(int)));
}

auto renderer2d::render_sprite(const glm::vec3& position, const float rot_z,const glm::vec3& scale ,const component_sprite& sprite) -> void
{
    auto model = glm::translate(glm::mat4(1.0f),position+ sprite.offset);
    model = glm::rotate(model,glm::radians(rot_z),glm::vec3(0,0,1));
    model = glm::scale(model, glm::vec3(sprite.size.x,sprite.size.y,1.0f));
    model = glm::scale(model, glm::vec3(scale.x,scale.y,scale.z));
    const auto& texture = resource_manager::get_texture(sprite.texture_id);
    
    //vertex 1
    glm::vec3 pos ={-0.5f, -0.5f, 0};
    glm::vec4 transformed_vertex = model * glm::vec4(pos,1); 
    state->vertices_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertices_ptr->tex_coord={sprite.clip.position.x,    sprite.clip.position.y};
    state->vertices_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertices_ptr->texture2d =texture;
    state->vertices_ptr->id = util::pack_into_32_bit_integer(texture.get_renderer_id(),sprite.blend_mode);
    state->vertices_ptr++;
    //vertex 2
    pos= {0.5f, -0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertices_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertices_ptr->tex_coord={sprite.clip.size.x, sprite.clip.position.y};
    state->vertices_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertices_ptr->texture2d =texture;
    state->vertices_ptr->id = util::pack_into_32_bit_integer(texture.get_renderer_id(),sprite.blend_mode);
    state->vertices_ptr++;
    //vertex 3
    pos ={0.5f,  0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertices_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertices_ptr->tex_coord={sprite.clip.size.x,        sprite.clip.size.y};
    state->vertices_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertices_ptr->texture2d =texture;
    state->vertices_ptr->id = util::pack_into_32_bit_integer(texture.get_renderer_id(),sprite.blend_mode);
    state->vertices_ptr++;
    //vertex 4
    pos = {-0.5f,  0.5f, 0};
    transformed_vertex = model * glm::vec4(pos,1); 
    state->vertices_ptr->position={transformed_vertex.x,transformed_vertex.y,transformed_vertex.z};
    state->vertices_ptr->tex_coord={sprite.clip.position.x,    sprite.clip.size.y};
    state->vertices_ptr->color={sprite.color.r,sprite.color.g,sprite.color.b,sprite.color.a};
    state->vertices_ptr->texture2d =texture;
    state->vertices_ptr->id = util::pack_into_32_bit_integer(texture.get_renderer_id(),sprite.blend_mode);
    state->vertices_ptr++;
    
    state->index_buffer_count+=6;
}

auto renderer2d::shutdown() -> void
{
    delete state;
}
 