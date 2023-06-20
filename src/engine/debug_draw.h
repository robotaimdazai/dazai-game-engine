#pragma once
#include "game_constants.h"
#include "resource_manager.h"
#include "vertex_array.h"
#include "ecs/components/component_camera.h"
#include "glm/vec2.hpp"
#include "glm/gtx/transform.hpp"

class debug_draw
{
public:
    static auto rect(glm::vec2 pos, glm::vec2 size) ->void
    {
        //attach shader
        auto debug_shader = resource_manager::get_shader(SHADER_DEBUG_NAME);
        debug_shader.bind();
        debug_shader.set_uniform1i("u_use_mvp",1);
        debug_shader.set_uniform3f("u_color",m_color_.x,m_color_.y,m_color_.z);
        auto model = glm::translate(glm::mat4(1),glm::vec3(pos.x,pos.y,0));
        model = glm::scale(model,glm::vec3(size.x,size.y,0));
        auto mvp = component_camera::proj * component_camera::view * model;
        debug_shader.set_uniform_mat4f("u_mvp",mvp);
    
        float vertices[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f 
        };
        vertex_array vao;
        vertex_buffer vbo(vertices,4* 2 * sizeof(float));
        vertex_buffer_layout layout;
        layout.push<float>(2);
        vao.add_buffer(vbo,layout);
        vao.bind();
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

    static auto line(const glm::vec2 start, const glm::vec2 end)->void
    {
        auto debug_shader = resource_manager::get_shader(SHADER_DEBUG_NAME);
        debug_shader.bind();
        debug_shader.set_uniform1i("u_use_mvp",0);
        debug_shader.set_uniform3f("u_color",m_color_.x,m_color_.y,m_color_.z);
        
        float vertices[] = {
            start.x/1280, start.y/720,
            end.x/1280, end.y/720,
        };

        vertex_array vao;
        vertex_buffer vbo(vertices,2* 2 * sizeof(float));
        vertex_buffer_layout layout;
        layout.push<float>(2);
        vao.add_buffer(vbo,layout);
        vao.bind();
        glDrawArrays(GL_LINE_LOOP, 0, 2);
    }

    static auto ray(const glm::vec2 origin, const glm::vec2 direction, const float length = 128)->void
    {
        auto debug_shader = resource_manager::get_shader(SHADER_DEBUG_NAME);
        debug_shader.bind();
        debug_shader.set_uniform1i("u_use_mvp",0);
        debug_shader.set_uniform3f("u_color",m_color_.x,m_color_.y,m_color_.z);
        glm::vec2 destination= origin + glm::normalize(direction);
        destination*=length;
        
        float vertices[] = {
            origin.x/1280, origin.y/720,
            destination.x/1280, destination.y/720
        };

        vertex_array vao;
        vertex_buffer vbo(vertices,2* 2 * sizeof(float));
        vertex_buffer_layout layout;
        layout.push<float>(2);
        vao.add_buffer(vbo,layout);
        vao.bind();
        glDrawArrays(GL_LINE_LOOP, 0, 2);
    }

    static auto circle(const glm::vec2 pos,const float radius=128, const int segments =32)->void
    {
        auto debug_shader = resource_manager::get_shader(SHADER_DEBUG_NAME);
        debug_shader.bind();
        debug_shader.set_uniform1i("u_use_mvp",1);
        debug_shader.set_uniform3f("u_color",m_color_.x,m_color_.y,m_color_.z);
        auto model = glm::translate(glm::mat4(1),glm::vec3(pos.x,pos.y,0));
        model = glm::scale(model,glm::vec3(1,1,0));
        auto mvp = component_camera::proj * component_camera::view * model;
        debug_shader.set_uniform_mat4f("u_mvp",mvp);
        
        std::vector<float> vertices;
        vertices.reserve((segments+1)*2);
        
        for (int i = 0; i <= segments; i++) {
            float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            vertices.push_back(pos.x + x);
            vertices.push_back(pos.y + y);
        }

        vertex_array vao;
        vertex_buffer vbo(vertices.data(),vertices.size() * sizeof(float));
        vertex_buffer_layout layout;
        layout.push<float>(2);
        vao.add_buffer(vbo,layout);
        vao.bind();
        glDrawArrays(GL_LINE_LOOP, 0, vertices.size()/2);
        
    }

    static auto set_color(const glm::vec3 color)->void
    {
        m_color_ = color;
    }

private:
    inline static glm::vec3 m_color_{1,1,1};
};
