#pragma once
#include <map>
#include <string>
#include <cstdint>
#include "glm/vec2.hpp"

struct uv_rect
{
    glm::vec2 position;
    glm::vec2 size;
};
struct character
{
    uint32_t texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    uint32_t advance;
    uv_rect uv;
};

class font
{
public:
    font()= default;
    font(const std::string& path, uint8_t size = 16);
    ~font();
    std::map<char, character> characters;

private:
    static const glm::ivec2 texture_size;
};
