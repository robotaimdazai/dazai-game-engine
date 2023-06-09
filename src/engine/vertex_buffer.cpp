#include "vertex_buffer.h"
#include <GL/glew.h>

vertex_buffer::vertex_buffer( const void* data, const unsigned int size)
{
    glGenBuffers(1,&m_renderer_id_);
    glBindBuffer(GL_ARRAY_BUFFER,m_renderer_id_);
    glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
}

vertex_buffer::~vertex_buffer()
{
    glDeleteBuffers(1, &m_renderer_id_);
}

auto vertex_buffer::bind() const -> void
{
    glBindBuffer(GL_ARRAY_BUFFER,m_renderer_id_);
}

auto vertex_buffer::unbind() const -> void
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}


    