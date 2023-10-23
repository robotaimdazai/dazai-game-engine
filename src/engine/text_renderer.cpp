#include "text_renderer.h"
#include <array>

#include "globals.h"
#include "index_buffer.h"
#include "logger.h"
#include "resource_manager.h"
#include "shader.h"
#include "vertex_array.h"
#include "ecs/components/component_camera.h"
#include "glm/vec2.hpp"

auto text_renderer::init() -> void
{
    LOG(info)<<"Text Renderer:: Init";
}

auto text_renderer::render_begin() -> void
{
    
}

auto text_renderer::render_text(const std::string& text, const glm::vec3& position,const glm::vec3& scale, const uint8_t& size,
    const glm::vec4& color,const std::string& font_name) -> void
{
    auto vao = new vertex_array();
    auto vbo = new vertex_buffer(4*     3 * 2 * 4 * sizeof(float));
    vertex_buffer_layout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    layout.push<float>(4);
    vao->add_buffer(*vbo,layout);
    unsigned int indices[]=
    {
        0,1,2,
        2,3,0
    };
    auto ibo = new index_buffer(indices,6);
    auto shader = resource_manager::get_shader(GLOBALS::SHADER_FONT_NAME);
    shader.bind();
    shader.set_uniform_mat4fv("u_proj_view",component_camera::proj * component_camera::view);
    const auto& font = resource_manager::get_font(font_name);
    auto character = font.characters.at(text[0]);
    auto model = glm::translate(glm::mat4(1.0f),position);
    model = glm::rotate(model,0.0f,glm::vec3(0,0,1));
    model = glm::scale(model,glm::vec3(character.size.x,character.size.y,1));
    model = glm::scale(model,glm::vec3(scale.x,scale.y,1));
    glm::vec3 pos = {-0.5f,-0.5f,0};
    glm::vec4 transformed_vertex = model * glm::vec4(pos,1);
    glm::vec3 pos1 = {0.5f,-0.5f,0};
    glm::vec4 transformed_vertex1 = model * glm::vec4(pos1,1);
    glm::vec3 pos2 = {0.5f,0.5f,0};
    glm::vec4 transformed_vertex2 = model * glm::vec4(pos2,1);
    glm::vec3 pos3 = {-0.5f,0.5f,0};
    glm::vec4 transformed_vertex3 = model * glm::vec4(pos3,1);
    float vertex_data[96]=
    {
        transformed_vertex.x,transformed_vertex.y,transformed_vertex.z,         0.0f,0.0f,      1,1,1,1,
        transformed_vertex1.x,transformed_vertex1.y,transformed_vertex1.z,      1.0f,0.0f,      1,1,1,1,
        transformed_vertex2.x,transformed_vertex2.y,transformed_vertex2.z,      1.0f,1.0f,      1,1,1,1,
        transformed_vertex3.x,transformed_vertex3.y,transformed_vertex3.z,      0.0f,1.0f,      1,1,1,1,
    };
    vao->bind();
    vbo->set_data(vertex_data,4*     3 * 2 * 4 * sizeof(float));
    vbo->bind();
    ibo->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,character.texture_id);
    shader.set_uniform1i("u_texture",0);
    glDrawElements(GL_TRIANGLES,ibo->get_count(),GL_UNSIGNED_INT,nullptr);
    
}

auto text_renderer::render_end() -> void
{
}

auto text_renderer::flush() -> void
{
    
}

auto text_renderer::shutdown() -> void
{
    
}
