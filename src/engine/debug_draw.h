#pragma once
#include "globals.h"
#include "resource_manager.h"
#include "vertex_array.h"
#include "ecs/components/component_camera.h"
#include "glm/vec2.hpp"
#include "glm/gtx/transform.hpp"

class debug_draw
{
public:
    static auto rect(glm::vec2 pos, glm::vec2 size, glm::vec3 color={1,1,1}) ->void
    {
        //attach shader
        auto debug_shader = resource_manager::get_shader(GLOBALS::SHADER_DEBUG_NAME);
        debug_shader.bind();
        debug_shader.set_uniform1i("u_use_mvp",1);
        debug_shader.set_uniform3f("u_color",color.x,color.y,color.z);
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

    static auto line(const glm::vec2 start, const glm::vec2 end, glm::vec3 color={1,1,1})->void
    {
        auto debug_shader = resource_manager::get_shader(GLOBALS::SHADER_DEBUG_NAME);
        debug_shader.bind();
        debug_shader.set_uniform1i("u_use_mvp",0);
        debug_shader.set_uniform3f("u_color",color.x,color.y,color.z);
        
        float vertices[] = {
            start.x/GLOBALS::screen_size.x, start.y/GLOBALS::screen_size.y,
            end.x/GLOBALS::screen_size.x, end.y/GLOBALS::screen_size.y,
        };

        vertex_array vao;
        vertex_buffer vbo(vertices,2* 2 * sizeof(float));
        vertex_buffer_layout layout;
        layout.push<float>(2);
        vao.add_buffer(vbo,layout);
        vao.bind();
        glDrawArrays(GL_LINE_LOOP, 0, 2);
    }

    static auto ray(const glm::vec2 origin, const glm::vec2 direction, const float length = 128, glm::vec3 color={1,1,1})->void
    {
        auto debug_shader = resource_manager::get_shader(GLOBALS::SHADER_DEBUG_NAME);
        debug_shader.bind();
        debug_shader.set_uniform1i("u_use_mvp",0);
        debug_shader.set_uniform3f("u_color",color.x,color.y,color.z);
        glm::vec2 destination= origin + glm::normalize(direction);
        destination*=length;
        
        float vertices[] = {
            origin.x/GLOBALS::screen_size.x, origin.y/GLOBALS::screen_size.y,
            destination.x/GLOBALS::screen_size.x, destination.y/GLOBALS::screen_size.y
        };

        vertex_array vao;
        vertex_buffer vbo(vertices,2* 2 * sizeof(float));
        vertex_buffer_layout layout;
        layout.push<float>(2);
        vao.add_buffer(vbo,layout);
        vao.bind();
        glDrawArrays(GL_LINE_LOOP, 0, 2);
    }

    static auto circle(const glm::vec2 pos,const float radius=128, const int segments =32, glm::vec3 color={1,1,1})->void
    {
        auto debug_shader = resource_manager::get_shader(GLOBALS::SHADER_DEBUG_NAME);
        debug_shader.bind();
        debug_shader.set_uniform1i("u_use_mvp",1);
        debug_shader.set_uniform3f("u_color",color.x,color.y,color.z);
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
            vertices.push_back(x);
            vertices.push_back(y);
        }

        vertex_array vao;
        vertex_buffer vbo(vertices.data(),vertices.size() * sizeof(float));
        vertex_buffer_layout layout;
        layout.push<float>(2);
        vao.add_buffer(vbo,layout);
        vao.bind();
        glDrawArrays(GL_LINE_LOOP, 0, vertices.size()/2);
    }
};
