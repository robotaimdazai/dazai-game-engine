#pragma once
#include <map>
#include <string>
#include <freetype/freetype.h>
#include <cstdint>
#include "glm/vec2.hpp"

struct character
{
    uint32_t texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    uint32_t advance;
};

class font
{
public:
    font()= default;
    font(const std::string& path, uint8_t size = 48);
    ~font();
    std::map<char, character> characters;
};
