#include "resource_manager.h"
#include "logger.h"

std::map<std::string,texture2d> resource_manager::textures;
std::map<std::string,shader> resource_manager::shaders;

auto resource_manager::load_texture(const std::string& file, const std::string& name,SDL_Renderer* window_renderer) -> texture2d
{
    textures[name] = load_texture_from_file(file,window_renderer);
    return textures[name];
}

auto resource_manager::load_shader(const std::string& file,const std::string& name) -> shader
{
    shaders.emplace(name, shader(file));
    return shaders[name];
}

auto resource_manager::get_texture(const std::string& name) -> texture2d&
{
    return textures.at(name);
}

auto resource_manager::clear() -> void
{
    for (auto iter: textures)
    {
        iter.second.destroy();
    }
    for (auto iter: shaders)
    {
        iter.second.destroy();
    }
    textures.clear();
    shaders.clear();
    LOG(info)<<"Resources cleared";
}

auto resource_manager::load_texture_from_file(const std::string& file, SDL_Renderer* window_renderer) -> texture2d
{
    texture2d texture2d;
    texture2d.load(file,window_renderer);
    return texture2d;
}


auto resource_manager::get_shader(const std::string& name) -> shader&
{
    return shaders.at(name);
}
