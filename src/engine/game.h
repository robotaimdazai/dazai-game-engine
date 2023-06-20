#ifndef GAME_H
#define GAME_H
#include <cstdint>
#include <memory>
#include <SDL_render.h>
#include <vector>
#include "input_manager.h"

class i_scene;
class game
{
    
public:
    game();
    virtual ~game();
    auto init(int screen_width, int screen_height, SDL_Renderer* renderer = nullptr)->void;
    auto load()->void;
    auto handle_inputs()->void;
    auto update(float delta_time)->void;
    auto render()->void;
    auto clean()->void;
    auto change_scene(std::unique_ptr<i_scene>)->void;
    auto push_scene(std::unique_ptr<i_scene>)->void;
    auto pop_scene()->void;
    auto on_gui()->void;
    auto on_debug_draw()->void;
    bool is_running;
    int window_width, window_height;
    SDL_Renderer* window_renderer;

private:
    std::vector<std::unique_ptr<i_scene>> m_game_scenes_;
    std::unique_ptr<input_manager> m_input_manager_;
};

#endif