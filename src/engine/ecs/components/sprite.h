#pragma once
#include "../../vec2.h"
struct sprite {
    sprite() = default;
    sprite(const texture2d texture2d, int width, int height, vec2 offset) : texture(texture2d), width(width), height(height), offset(offset) {}
    texture2d texture{};
    int width{};
    int height{};
    vec2 offset{};
    SDL_Renderer* renderer{};
};