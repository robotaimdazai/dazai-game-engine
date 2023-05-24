#include "texture2d.h"

#include "logger.h"

texture2d::texture2d(): m_texture_(nullptr),m_width_(0),m_height_(0)
{
    //can create null texture here or maybe introduce setPixel call;
}

texture2d::~texture2d()
{
    SDL_DestroyTexture(m_texture_);
}


auto texture2d::load(const std::string& file_name, SDL_Renderer* renderer) -> bool
{
    m_surface_=IMG_Load(file_name.c_str());
    
    if(m_surface_==nullptr)
        LOG(error)<<"Surface not loaded: "<<file_name;
    else
    {
        m_texture_ = SDL_CreateTextureFromSurface(renderer,m_surface_);
        if(m_texture_==nullptr)
            LOG(error)<<"Texture not loaded: "<<file_name;
        else
        {
            m_width_ = m_surface_->w;
            m_height_ = m_surface_->h;
        }
        SDL_FreeSurface(m_surface_);
    }
    
    return m_texture_!=nullptr;
}

