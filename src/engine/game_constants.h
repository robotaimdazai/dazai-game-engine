#pragma once
#include <bitset>
#include <cstdint>

//ECS settings
constexpr uint32_t MAX_ENTITIES = 5000;
constexpr  uint8_t MAX_COMPONENTS = 32;
using signature = std::bitset<MAX_COMPONENTS>;
using entity = uint32_t;

//shaders
static const std::string SHADER_SPRITE_PATH="assets/shaders/sprite.glsl";
static const std::string SHADER_SPRITE_NAME="sprite.glsl";
static const std::string SHADER_DEBUG_PATH="assets/shaders/debug.glsl";
static const std::string SHADER_DEBUG_NAME="debug.glsl";