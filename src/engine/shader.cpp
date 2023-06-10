#include "shader.h"
#include <GL/glew.h>
#include <sstream>
#include <fstream>
#include <iostream>

shader::shader(const std::string& path)
{
    m_renderer_id_ = glCreateProgram();
    const auto [vertex_source, fragment_source] = parse_shader(path);
    create_shader_program(vertex_source,fragment_source);
}

auto shader::parse_shader(const std::string& file_path) const -> shader_program_source
{
    std::ifstream stream(file_path);
    std::string line;
    std::stringstream ss[2];
    enum class shader_type
    {
        none = -1, vertex = 0, fragment = 1
    };
    shader_type type = shader_type::none;
    while(getline(stream,line))
    {
        if(line.find("#shader")!=std::string::npos)
        {
            if(line.find("vertex")!=std::string::npos)
            {
                type = shader_type::vertex;
            }
            else if(line.find("fragment")!=std::string::npos)
            {
                type = shader_type::fragment;
            }
        }
        else
        {
            ss[static_cast<int>(type)]<<line<<"\n";
        }
    }
    return {ss[0].str(),ss[1].str()};
}

auto shader::compile_shader(unsigned type, const std::string& source) -> unsigned
{
    const unsigned int id= glCreateShader(type);
    const char* src=source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    //error handling goes here
    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if(result  == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = static_cast<char*>(alloca(length* sizeof(char)));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout<<"Shader compilation failed for: "<<(type==GL_VERTEX_SHADER?"Vertex ":"Fragment ")<<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }
        
    return id;
}

auto shader::create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader) -> unsigned
{
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
    glAttachShader(m_renderer_id_,vs);
    glAttachShader(m_renderer_id_,fs);
    glLinkProgram(m_renderer_id_);
    glValidateProgram(m_renderer_id_);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return m_renderer_id_;
}

auto shader::get_uniform_location(const std::string& uniform) -> int
{
    if(m_cached_uniforms_.find(uniform)!=m_cached_uniforms_.end())
        return m_cached_uniforms_[uniform];
    
    int location = glGetUniformLocation(m_renderer_id_,uniform.c_str());
    //give warning log here if location is -1
    m_cached_uniforms_[uniform] = location;
    return location;
}

auto shader::set_uniform4f(const std::string& uniform,float f1, float f2, float f3, float f4) -> void
{
    glUniform4f(get_uniform_location(uniform),f1,f2,f3,f4);
}

auto shader::set_uniform1i(const std::string& uniform, int value) -> void
{
    glUniform1i(get_uniform_location(uniform),value);
}

auto shader::set_uniform1f(const std::string& uniform, float value) -> void
{
    glUniform1f(get_uniform_location(uniform),value);
}

auto shader::set_uniform_mat4f(const std::string& uniform, const glm::mat4& matrix) -> void
{
    glUniformMatrix4fv(get_uniform_location(uniform),1,GL_FALSE,&matrix[0][0]);
}

auto shader::bind() const -> void
{
    glUseProgram(m_renderer_id_);
}

auto shader::unbind() const -> void
{
    glUseProgram(0);
}

auto shader::destroy() -> void
{
    glDeleteProgram(m_renderer_id_);
}
