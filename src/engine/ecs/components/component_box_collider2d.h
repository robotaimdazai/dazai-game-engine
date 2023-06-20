#pragma once
#include <SDL_rect.h>

struct component_box_collider2d
{
    SDL_Rect rect{-32,-32,64,64};
    bool is_trigger{false};
};
