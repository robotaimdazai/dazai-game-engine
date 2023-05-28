﻿#include "resource_manager.h"

#include "logger.h"

std::map<std::string,texture2d> resource_manager::textures;

auto resource_manager::load_texture(const std::string& file, const std::string& name,SDL_Renderer* window_renderer) -> texture2d
{
    textures[name] = load_texture_from_file(file,window_renderer);
    return textures[name];
}

auto resource_manager::get_texture(const std::string& name) -> texture2d
{
    return textures[name];
}

auto resource_manager::clear() -> void
{
    for (auto iter: textures)
    {
        iter.second.destroy();
    }
    textures.clear();
    LOG(info)<<"Resources cleared";
}

auto resource_manager::load_texture_from_file(const std::string& file, SDL_Renderer* window_renderer) -> texture2d
{
    texture2d texture2d;
    texture2d.load(file,window_renderer);
    return texture2d;
}