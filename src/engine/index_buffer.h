#pragma once

class index_buffer
{
public:
    index_buffer(const void* data, unsigned int count);
    ~index_buffer();
    auto bind() const -> void;
    auto unbind() const -> void;
    auto get_id() const -> unsigned int {return m_renderer_id_;}
    auto get_count() const -> unsigned int {return m_count_;}
    
private:
    unsigned m_renderer_id_{};
    unsigned int m_count_{};
};
