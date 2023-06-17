#pragma once
#include <memory>
#include "../../index_buffer.h"
#include "../../shader.h"
#include "../../vertex_array.h"
#include "../core/system.h"

class system_renderer_sprite: public system
{
public:
    system_renderer_sprite(const shader& shader);
    ~system_renderer_sprite();
    auto render()->void;

private:
    std::unique_ptr<vertex_array> m_vertex_array_;
    std::unique_ptr<vertex_buffer> m_vertex_buffer_;
    std::unique_ptr<index_buffer> m_index_buffer_;
    shader m_shader_;
};
