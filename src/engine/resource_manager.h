#pragma once

#include "texture2d.h" 
#include "map" 
class resource_manager
{
public:
    //storage
    static std::map<std::string,texture2d> textures;
    static auto load_texture(const std::string& file, const std::string& name, SDL_Renderer* window_renderer)->texture2d;
    static auto get_texture(const std::string& name)->texture2d&;
    static auto clear()->void;

private:
    resource_manager() = default;
    static auto load_texture_from_file(const std:: string& file, SDL_Renderer* window_renderer)->texture2d;
};
