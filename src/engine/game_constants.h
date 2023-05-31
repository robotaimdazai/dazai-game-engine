#pragma once
#include <bitset>
#include <cstdint>

//ECS settings
constexpr uint32_t MAX_ENTITIES = 5000;
constexpr  uint8_t MAX_COMPONENTS = 32;
using signature = std::bitset<MAX_COMPONENTS>;
using entity = uint32_t;