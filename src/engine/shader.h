#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct shader_program_source
{
    std::string vertex_source;
    std::string fragment_source;
};

class shader
{
public:
    shader()= default;
    shader(const std::string& path);
    ~shader();
    auto set_uniform4f(const std::string&, float f1, float f2, float f3, float f4)->void;
    auto set_uniform1i(const std::string&,int value)->void;
    auto set_uniform_mat4f(const std::string&,const glm::mat4& matrix)->void;
    auto bind() const ->void;
    auto unbind()const->void;

private:
    auto parse_shader(const std::string& file_path) const ->shader_program_source;
    auto compile_shader(unsigned int type, const std::string& source)->unsigned int;
    auto create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader) -> unsigned int;
    auto get_uniform_location(const std::string& uniform)->int;
    unsigned int m_renderer_id_{};
    std::unordered_map<std::string,int> m_cached_uniforms_;
    
};
