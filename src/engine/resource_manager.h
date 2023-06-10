#pragma once

#include "texture2d.h" 
#include "map" 
#include "shader.h"

class resource_manager
{
public:
    //storage
    static std::map<std::string,texture2d> textures;
    static std::map<std::string, shader> shaders;
    static auto load_texture(const std::string& file, const std::string& name, SDL_Renderer* window_renderer)->texture2d;
    static auto load_shader(const std::string& file,const std::string& name)-> shader;
    static auto get_texture(const std::string& name)->texture2d&;
    static auto get_shader(const std::string& name)->shader&;
    static auto clear()->void;

private:
    resource_manager() = default;
    static auto load_texture_from_file(const std:: string& file, SDL_Renderer* window_renderer)->texture2d;
    static auto load_shader_from_file(const std:: string& file)->shader;
};
