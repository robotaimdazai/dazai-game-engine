#pragma once
#include <SDL_render.h>
#include <string>
#include <SDL_image.h>

class texture2d
{
public:
    texture2d();
    ~texture2d();
    auto load(const std::string& file_name,SDL_Renderer* renderer)->bool;
    auto get_width()->int;
    auto get_height()->int;

private:
    SDL_Texture* m_texture_;
    SDL_Surface* m_surface_;
    int m_width_;
    int m_height_;
    
};
