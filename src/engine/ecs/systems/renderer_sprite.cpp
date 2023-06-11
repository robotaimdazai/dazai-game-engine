﻿#include "renderer_sprite.h"
#include "../ecs.h"
#include "../../resource_manager.h"
#include "../components/camera.h"
#include "../components/sprite.h"
#include "../components/transform.h"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"

extern ecs g_ecs;
static float vertex_data[]=
{
    -0.5f, -0.5f, 0.0f,     0.0f,0.0f,  
     0.5f, -0.5f, 0.0f,     1.0f,0.0f,      //left: vertices(NDC)  Right: texCoords
     0.5f,  0.5f, 0.0f,     1.0f,1.0f,
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f
};

static unsigned int indices[]=
{
    0,1,2,
    2,3,0
};


renderer_sprite::renderer_sprite(const shader& shader):m_shader_(shader)
{
    m_vertex_array_ = std::make_unique<vertex_array>();
    m_vertex_buffer_ = std::make_unique<vertex_buffer>(vertex_data,4 * 5 * sizeof(float));
    m_vertex_buffer_layout_ = std::make_unique<vertex_buffer_layout>();
    //vertex pos
    m_vertex_buffer_layout_->push<float>(3);
    //texCoord
    m_vertex_buffer_layout_->push<float>(2);
    m_vertex_array_->add_buffer(*m_vertex_buffer_,*m_vertex_buffer_layout_);
    //index buffer
    m_index_buffer_ = std::make_unique<index_buffer>(indices,6);
    
}

renderer_sprite::~renderer_sprite()
{
    
}

auto renderer_sprite::render() -> void
{
    for(auto const& entity: entities)
    {
        const auto& this_sprite = g_ecs.get_component<sprite>(entity);
        const auto& this_transform = g_ecs.get_component<transform>(entity);
        m_shader_.bind();
        auto texture = resource_manager::get_texture(this_sprite.texture);
        texture.bind();
        //create translate matrix
        auto world_transform_mat = glm::translate(glm::mat4(1.0f),this_transform.position + this_sprite.offset);
        //rotate from sprite rotation in degree
        world_transform_mat *= glm::rotate(glm::mat4(1.0f),glm::radians(this_transform.rotation.z),glm::vec3(0.0f,0.0f,1.0f));
        //create default scale matrix based on texture dimension
        world_transform_mat *= scale(glm::mat4(1.0f), glm::vec3(texture.get_size().x,texture.get_size().y,1.0f));
        //apply transform scale
        world_transform_mat *= scale(glm::mat4(1.0f),this_transform.scale);
        //pack final model matrix
        auto model = world_transform_mat;
        m_shader_.set_uniform_mat4f("u_model",model);
        m_shader_.set_uniform_mat4f("u_proj",camera::proj);
        m_shader_.set_uniform_mat4f("u_view",camera::view);
        //set color, texture here
        m_shader_.set_uniform4f("u_color",1,1,1,1);
        m_shader_.set_uniform1i("u_texture",texture.get_slot());

        //bind gl
        m_vertex_array_->bind();
        m_index_buffer_->bind();
        m_vertex_buffer_->bind();
        glDrawElements(GL_TRIANGLES,m_index_buffer_->get_count(),GL_UNSIGNED_INT,nullptr);
    }
}
