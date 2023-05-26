#pragma once
#include <SDL_render.h>
#include <string>
#include <SDL_image.h>

class texture2d
{
public:
    texture2d();
    auto load(const std::string& file_name,SDL_Renderer* renderer)->bool;
    auto get_width()const -> int;
    auto get_height()const -> int;
    auto render(int x, int y,SDL_Renderer* renderer ,SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr,
                SDL_RendererFlip flip = SDL_FLIP_NONE) const -> void;
    auto destroy()->void;

private:
    SDL_Texture* m_texture_;
    SDL_Surface* m_surface_;
    int m_width_;
    int m_height_;
    
};
