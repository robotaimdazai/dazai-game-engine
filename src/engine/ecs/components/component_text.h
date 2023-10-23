#pragma once
#include <string>
#include "glm/vec4.hpp"

struct component_text
{
    std::string font_id;
    std::string text;
    uint8_t size;
    glm::vec4 color;
};
