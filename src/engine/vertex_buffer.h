#pragma once
#include <vector>

class vertex_buffer
{
public:
    vertex_buffer(const void* data, unsigned int size);
    vertex_buffer(unsigned int size); // used for dynamic buffer 
    ~vertex_buffer();
    auto set_data(const void* data, const unsigned int size) const -> void;
    auto bind() const -> void;
    auto unbind() const -> void;
    auto get_id() const -> unsigned int {return m_renderer_id_;}
private:
    unsigned int m_renderer_id_{};
    unsigned int m_size_;
};
