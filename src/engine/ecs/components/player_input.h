#pragma once
#include <SDL_scancode.h>

struct player_input
{
    //controls
    SDL_Scancode left_key{SDL_SCANCODE_A};
    SDL_Scancode right_key{SDL_SCANCODE_D};
    SDL_Scancode down_key{SDL_SCANCODE_S};
    SDL_Scancode up_key{SDL_SCANCODE_W};
    SDL_Scancode attack_key{SDL_SCANCODE_SPACE};

    //attributes
    float speed = 500.0f;
    glm::vec3 direction{0.0f,0.0f,0.0f};
};
