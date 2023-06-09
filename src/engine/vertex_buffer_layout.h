#pragma once
#include <vector>
#include <GL/glew.h>
#include "logger.h"


struct buffer_element_layout
{
    unsigned int count;
    unsigned int type;
    char normalized;
    unsigned int size;
}; 

class vertex_buffer_layout
{
public:
    template<typename T>
    auto push(unsigned int count)->void
    {
        ASSERT(false);
    }

    //supported types
    template<>
    auto push<float>(const unsigned int count)->void
    {
        m_element_layouts_.push_back({count,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT)});
        m_stride_+=sizeof(GL_FLOAT)* count;
    }

    template<>
    auto push<unsigned int>(const unsigned int count)->void
    {
        m_element_layouts_.push_back({count,GL_UNSIGNED_INT,GL_FALSE,sizeof(GL_UNSIGNED_INT)});
        m_stride_+=sizeof(GL_UNSIGNED_INT) * count;
    }

    template<>
    auto push<char>(const unsigned int count)->void
    {
        m_element_layouts_.push_back({count,GL_BYTE,GL_TRUE,sizeof(GL_BYTE)});
        m_stride_+=sizeof(GL_BYTE)* count;
    }
    
    auto get_elements()->const std::vector<buffer_element_layout>&
    {
        return m_element_layouts_;
    }

    auto get_stride()const->unsigned int
    {
        return m_stride_;
    }

private:
    std::vector<buffer_element_layout> m_element_layouts_{};
    unsigned int m_stride_{};
};
