#pragma once
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class vertex_array
{
public:
    vertex_array();
    ~vertex_array();
    auto add_buffer(vertex_buffer& vb,vertex_buffer_layout& layout)->void;
    auto bind()const ->void;
    auto unbind() const ->void;

private:
    unsigned int m_renderer_id_{};
};
