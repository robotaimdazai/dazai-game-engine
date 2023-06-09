#include "vertex_array.h"

vertex_array::vertex_array()
{
    glGenVertexArrays(1,&m_renderer_id_);
}
vertex_array::~vertex_array()
{
    glDeleteVertexArrays(1,&m_renderer_id_);
}

auto vertex_array::add_buffer(vertex_buffer& vb, vertex_buffer_layout& layout) -> void
{
    bind();
    vb.bind();
    const auto elements = layout.get_elements();
    unsigned int offset = 0;
    for(int index =0; index<elements.size();index++)
    {
        const auto element = elements[index];
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,element.count,element.type,element.normalized,layout.get_stride(),(const void*) offset);
        offset+=element.count * element.size;
            
    }
}


auto vertex_array::bind() const -> void
{
    glBindVertexArray(m_renderer_id_);
}

auto vertex_array::unbind() const -> void
{
    glBindVertexArray(0);
}




