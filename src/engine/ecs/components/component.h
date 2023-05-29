#pragma once
#include <cstdint>


//base class for all components
struct component
{
    component(uint32_t entity_id):m_entity_id_(entity_id){};
    
    auto set_entity_id(const uint32_t id)->void
    {
        m_entity_id_ = id;
    }
    auto get_entity_id() const->uint32_t
    {
        return m_entity_id_;
    }
protected:
    uint32_t m_entity_id_ = 0;
    
};
