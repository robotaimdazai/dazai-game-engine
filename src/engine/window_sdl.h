#ifndef WINDOW_SDL_H
#define WINDOW_SDL_H

#include "window.h"
#include "SDL.h"

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

private:
    std::unique_ptr<SDL_Window,sdl_window_destroyer> m_window_;
    const std::string& m_title_;
    
};


#endif