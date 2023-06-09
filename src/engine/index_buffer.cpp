#include "index_buffer.h"
#include <GL/glew.h>


index_buffer::index_buffer( const void* data, const unsigned int count):
m_count_(count)
{
    glGenBuffers(1,&m_renderer_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_renderer_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) *count,data,GL_STATIC_DRAW);
}

index_buffer::~index_buffer()
{
    glDeleteBuffers(1, &m_renderer_id_);
}

auto index_buffer::bind() const -> void
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_renderer_id_);
}

auto index_buffer::unbind() const -> void
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}


    