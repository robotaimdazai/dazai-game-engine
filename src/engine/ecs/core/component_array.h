#pragma once
#include <assert.h>
#include <typeindex>
#include <unordered_map>
#include "i_component_array.h"
#include "../../globals.h"
#include "../../logger.h"

template<typename T>
class component_array final : public i_component_array
{
public:
    component_array():m_size_(0)
    {
        LOG(info)<<"Component manager created: "<<std::type_index(typeid(T)).name();
    }
    
    auto set_data(entity entity) ->T&
    {
        assert(m_entity_to_index_.find(entity) == m_entity_to_index_.end() && "Component added to same entity more than once.");
        const size_t new_index = m_size_;
        m_entity_to_index_[entity] = new_index;
        m_index_to_entity_[new_index] = entity;
        m_component_array_[new_index] = T{};
        ++m_size_;
        return m_component_array_[new_index];
    }

    auto remove_component(entity entity) ->void
    {
        assert(m_entity_to_index_.find(entity) != m_entity_to_index_.end() && "Removing non-existent component.");
        //move last entity to the removed entity's location
        const size_t index_of_removed_entity = m_entity_to_index_[entity];
        const size_t index_of_last_element = m_size_ - 1;
        m_component_array_[index_of_removed_entity] = m_component_array_[index_of_last_element];
        //now update map
        const uint32_t entity_of_last_element = {m_index_to_entity_[index_of_last_element]};
        m_entity_to_index_[entity_of_last_element] = index_of_removed_entity;
        m_index_to_entity_[index_of_removed_entity] = entity_of_last_element;
        m_entity_to_index_.erase(entity);
        m_index_to_entity_.erase(index_of_last_element);
        --m_size_;
    }
    auto get_data(const entity entity) ->T&
    {
        assert (m_entity_to_index_.find(entity) != m_entity_to_index_.end() && "Component does not exist.");
        return m_component_array_[m_entity_to_index_[entity]];
    }

    auto try_get_data(const entity& entity)->T*
    {
        if(m_entity_to_index_.find(entity) == m_entity_to_index_.end())
        {
            return nullptr;
        }
        return &m_component_array_[m_entity_to_index_[entity]];
    }
    auto entity_destroyed(const entity entity) ->void override
    {
        if(m_entity_to_index_.find(entity) != m_entity_to_index_.end())
        {
           remove_component(entity);
        }
    }
private:
    T m_component_array_[MAX_ENTITIES];
    std::unordered_map<uint32_t,size_t> m_entity_to_index_;
    std::unordered_map<size_t,uint32_t> m_index_to_entity_;
    size_t m_size_;
};
