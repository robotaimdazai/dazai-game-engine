#pragma once

class vertex_buffer
{
public:
    vertex_buffer(const void* data, unsigned int size);
    ~vertex_buffer();
    auto bind() const -> void;
    auto unbind() const -> void;
    auto get_id() const -> unsigned int {return m_renderer_id_;}
private:
    unsigned int m_renderer_id_{};
};
