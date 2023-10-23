#include "resource_manager.h"
#include "font.h"
#include "logger.h"


auto resource_manager::load_texture(const std::string& file, const std::string& name) -> texture2d
{
    textures.emplace(name,texture2d(file));
    return textures[name];
}

auto resource_manager::load_shader(const std::string& file,const std::string& name) -> shader
{
    shaders.emplace(name, shader(file));
    return shaders[name];
}

auto resource_manager::load_font(const std::string& file,const std::string& name) -> font
{
    fonts.emplace(name,font(file, 16));
    return fonts[name];
}

auto resource_manager::get_texture(const std::string& name) -> texture2d&
{
    try
    {
        return textures.at(name);
    }
    catch (const std::exception& e)
    {
        LOG(error)<<"Unable to get texture: "<<name<<" "<<e.what();
        return textures[name];
    }
   
}

auto resource_manager::get_font(const std::string& name) -> font&
{
    try
    {
        return fonts.at(name);
    }
    catch (const std::exception& e)
    {
        LOG(error)<<"Unable to get font: "<<name<<" "<<e.what();
        return fonts[name];
    }
   
}

auto resource_manager::get_shader(const std::string& name) -> shader&
{
    try
    {
        return shaders.at(name);
    }
    catch (const std::exception& e)
    {
        LOG(error)<<"Unable to get shader: "<<name<<" "<<e.what();
        return shaders[name];
    }
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

