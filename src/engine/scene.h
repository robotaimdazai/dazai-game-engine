#pragma once
#include "game.h"

class i_scene
{
public:
    virtual ~i_scene() = default;
    virtual auto load()->void =0;
    virtual auto clean()->void =0;
    virtual auto update(float delta_time)->void=0;
    virtual auto render()->void = 0;
    virtual auto pause()->void = 0;
    virtual auto resume()->void = 0;
    virtual auto set_game(game* game)->void=0;
    virtual auto handle_event(const input_state&)->void = 0;
    virtual auto on_gui()->void =0;
    virtual auto on_debug_draw()->void =0;
    
};
