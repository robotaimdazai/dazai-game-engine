#include "resource_manager.h"

std::map<std::string,texture2d> resource_manager::textures;

auto resource_manager::load_texture(const std::string& file, const std::string& name) -> texture2d
{
    textures[name] = load_texture_from_file(file);
    return textures[name];
}

auto resource_manager::get_texture(const std::string& name) -> texture2d
{
    return textures[name];
}

auto resource_manager::clear() -> void
{
    textures.clear();
}

auto resource_manager::load_texture_from_file(const std::string& file) -> texture2d
{
    texture2d texture2d;
    texture2d.load(file,nullptr); //TODO need to replace renderer with window renderer? maybe create singleton for window or any pattern??
    return texture2d;
}
