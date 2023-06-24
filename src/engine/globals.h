#pragma once
#include <bitset>
#include <cstdint>
#include "glm/vec2.hpp"

//ECS settings
constexpr uint32_t MAX_ENTITIES = 5000;
constexpr  uint8_t MAX_COMPONENTS = 32;
using signature = std::bitset<MAX_COMPONENTS>;
using entity = uint32_t;

namespace GLOBALS
{
    //game settings
    static const glm::vec2 screen_size{1280,720};
    static const float target_fps =120;

    //shaders
    static const std::string SHADER_SPRITE_PATH="assets/shaders/sprite.glsl";
    static const std::string SHADER_SPRITE_NAME="sprite.glsl";
    static const std::string SHADER_DEBUG_PATH="assets/shaders/debug.glsl";
    static const std::string SHADER_DEBUG_NAME="debug.glsl";
    
}
