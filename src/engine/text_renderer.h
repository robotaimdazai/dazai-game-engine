#pragma once
#include <string>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class text_renderer
{
public:
    static auto init()->void;
    static auto render_begin()->void;
    static auto render_text(const std::string& text, const glm::vec3& position ,const glm::vec3& scale,
        const glm::vec4& color, const std::string& font_name)->void;
    static auto render_end()->void;
    static auto flush()->void;
    static auto shutdown()->void;
};
