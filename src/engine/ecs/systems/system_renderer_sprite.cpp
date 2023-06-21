﻿#include "system_renderer_sprite.h"
#include "../ecs.h"
#include "../../resource_manager.h"
#include "../components/component_camera.h"
#include "../components/component_sprite.h"
#include "../components/component_transform.h"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"

extern ecs g_ecs;
static float default_vertex_data[]=
{
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,        
     0.5f,  0.5f, 1.0f, 1.0f,   
    -0.5f,  0.5f, 0.0f, 1.0f   
};


static unsigned int indices[]=
{
    0,1,2,
    2,3,0
};


system_renderer_sprite::system_renderer_sprite(const shader& shader):m_shader_(shader)
{
    m_vertex_array_ = std::make_unique<vertex_array>();
    m_vertex_buffer_ =  std::make_unique<vertex_buffer>(default_vertex_data,4 * 4 * sizeof(float));
    auto layout = vertex_buffer_layout();
    layout.push<float>(2);
    layout.push<float>(2);
    m_vertex_array_->add_buffer(*m_vertex_buffer_,layout);
    //index buffer
    m_index_buffer_ = std::make_unique<index_buffer>(indices,6);
}

system_renderer_sprite::~system_renderer_sprite()
{
    
}


auto system_renderer_sprite::render() -> void
{
    for(auto const& entity: entities)
    {
        auto& this_sprite = g_ecs.get_component<component_sprite>(entity);
        const auto& this_transform = g_ecs.get_component<component_transform>(entity);
        //if sprite is animated update vertex buffer
        m_vertex_buffer_->update(this_sprite.clip_buffer);
        m_shader_.bind();
        auto texture = resource_manager::get_texture(this_sprite.texture_id);
        texture.bind();
        //create translate matrix
        auto world_transform_mat = glm::translate(glm::mat4(1.0f),this_transform.position + this_sprite.offset);
        //rotate from sprite rotation in degree
        world_transform_mat = glm::rotate(world_transform_mat,glm::radians(this_transform.rotation.z),glm::vec3(0.0f,0.0f,1.0f));
        world_transform_mat = glm::scale(world_transform_mat, glm::vec3(this_sprite.size.x,this_sprite.size.y,1.0f));
        world_transform_mat = scale(world_transform_mat,this_transform.scale);
        // giving abs scale value as - scale is not yet supported
        //pack final model matrix
        auto model = world_transform_mat;
        m_shader_.set_uniform_mat4f("u_model",model);
        m_shader_.set_uniform_mat4f("u_proj",component_camera::proj);
        m_shader_.set_uniform_mat4f("u_view",component_camera::view);
        //set color, texture here
        m_shader_.set_uniform4f("u_color",1,1,1,1);
        m_shader_.set_uniform1i("u_texture",texture.get_slot());

        //bind gl
        m_vertex_array_->bind();
        m_index_buffer_->bind();
        glDrawElements(GL_TRIANGLES,m_index_buffer_->get_count(),GL_UNSIGNED_INT,nullptr);
    }
}

