#include "texture2d.h"
#include "logger.h"
#include "stb_image.h"
#include "GL/glew.h"


texture2d::texture2d(const std::string& path):m_width_(0),m_height_(0),m_slot_(-1),m_renderer_id_(0),m_channels_count_(0),m_path_(path)
{
    //flip vertically on load
    stbi_set_flip_vertically_on_load(1);
    m_raw_data_ = stbi_load(path.c_str(),&m_width_,&m_height_,&m_channels_count_,4);
    if(!m_raw_data_)
        LOG(error)<<"Could not load texture at: "<<path;
    //can warn here if texture is not in power 2 dimension, if notice any memory issues

    //gen texture buffer
    glGenTextures(1,&m_renderer_id_);
    //bind
    glBindTexture(GL_TEXTURE_2D,m_renderer_id_);
    //set params
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    //specify texture type
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m_width_,m_height_,0,GL_RGBA,GL_UNSIGNED_BYTE,m_raw_data_);
    //unbind
    unbind();
    //free stbi buffer
    stbi_image_free(m_raw_data_);
}

auto texture2d::bind(unsigned int slot) -> void
{
    m_slot_ = slot;
    glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D,m_renderer_id_);
}

auto texture2d::get_slot() const -> int
{
    return m_slot_;
}

auto texture2d::unbind() -> void
{
    glBindTexture(GL_TEXTURE_2D,0);
}

auto texture2d::destroy() const -> void
{
    glDeleteTextures(1,&m_renderer_id_);
}

auto texture2d::get_size() const -> glm::vec2
{
    return glm::vec2(m_width_,m_height_);
}

auto texture2d::get_path() const -> const std::string&
{
    return m_path_;
}

