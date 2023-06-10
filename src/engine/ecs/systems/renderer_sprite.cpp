#include "renderer_sprite.h"
#include "../ecs.h"
#include "../components/sprite.h"

extern ecs g_ecs;
static float vertex_data[]=
{
    -0.5f, -0.5f, 0.0f,     0.0f,0.0f,  
     0.5f, -0.5f, 0.0f,     1.0f,0.0f,      //left: vertices(NDC)  Right: texCoords
     0.5f,  0.5f, 0.0f,     1.0f,1.0f,
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f
};

static unsigned int indices[]=
{
    0,1,2,
    2,3,0
};


renderer_sprite::renderer_sprite()
{
    m_vertex_array_ = std::make_unique<vertex_array>();
    m_vertex_buffer_ = std::make_unique<vertex_buffer>(vertex_data,4 * 5 * sizeof(float));
    m_vertex_buffer_layout_ = std::make_unique<vertex_buffer_layout>();
    //vertex pos
    m_vertex_buffer_layout_->push<float>(3);
    //texCoord
    m_vertex_buffer_layout_->push<float>(2);
    m_vertex_array_->add_buffer(*m_vertex_buffer_,*m_vertex_buffer_layout_);
    //index buffer
    m_index_buffer_ = std::make_unique<index_buffer>(indices,6);
    
}

renderer_sprite::~renderer_sprite()
{
    
}

auto renderer_sprite::render() -> void
{
    for(auto const& entity: entities)
    {
        const auto& this_sprite = g_ecs.get_component<sprite>(entity);
    }
}
