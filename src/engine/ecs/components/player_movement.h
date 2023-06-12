#pragma once
#include <SDL_scancode.h>

struct player_movement
{
    //controls
    SDL_Scancode left_key{SDL_SCANCODE_A};
    SDL_Scancode right_key{SDL_SCANCODE_D};
    SDL_Scancode down_key{SDL_SCANCODE_S};
    SDL_Scancode up_key{SDL_SCANCODE_W};

    //attributes
    float speed = 500.0f;
};
