#pragma once
#include <freetype/freetype.h>
#include "font.h"
#include "texture2d.h" 
#include "map" 
#include "shader.h"

class resource_manager
{
public:
    //storage
    inline static std::map<std::string,texture2d> textures;
    inline static std::map<std::string, shader> shaders;
    inline static std::map<std::string, font> fonts;
    static auto load_texture(const std::string& file, const std::string& name)->texture2d;
    static auto load_shader(const std::string& file,const std::string& name)-> shader;
    static auto load_font(const std::string& file,const std::string& name)-> font;
    static auto get_texture(const std::string& name)->texture2d&;
    static auto get_shader(const std::string& name)->shader&;
    static auto get_font(const std::string& name)->font&;
    static auto clear()->void;

private:
    resource_manager() = default;
};
