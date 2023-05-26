#ifndef WINDOW_SDL_H
#define WINDOW_SDL_H

#include "SDL.h"
#include "window.h"

extern const float screen_width;
extern const float screen_height;

struct sdl_window_destroyer
{
    auto operator()(SDL_Window* window) const ->void
    {
        SDL_DestroyWindow(window);
    }
};

class window_sdl: public iwindow
{
    
public:
    window_sdl(const std::string &title);
    ~window_sdl() override;
    auto init(int x_pos, int y_pos, int width, int height, bool is_fullscreen) -> bool override;
    auto get_renderer()-> SDL_Renderer* override;

private:
    std::unique_ptr<SDL_Window,sdl_window_destroyer> m_window_;
    const std::string& m_title_;
    SDL_Renderer* m_renderer_;
    
};

#endif