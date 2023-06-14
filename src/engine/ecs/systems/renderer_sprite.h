#pragma once
#include <memory>
#include "../../index_buffer.h"
#include "../../shader.h"
#include "../../vertex_array.h"
#include "../core/system.h"

class renderer_sprite: public system
{
public:
    renderer_sprite(const shader& shader);
    ~renderer_sprite();
    auto update_vertex_buffer(const std::vector<float>& data) const ->void;
    auto render()->void;

private:
    std::unique_ptr<vertex_array> m_vertex_array_;
    std::unique_ptr<vertex_buffer> m_vertex_buffer_;
    std::unique_ptr<index_buffer> m_index_buffer_;
    shader m_shader_;
};
