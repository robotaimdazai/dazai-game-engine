#pragma once
#include <stdexcept>
#include <typeindex>

#include "../entities/entity.h"
#include "base_component_manager.h"
#include "../../logger.h"

template<typename T>
class component_manager final : public base_component_manager
{
public:
    component_manager() = default;
    
    auto add_component(int entity_id) ->T&
    {
        m_components_.emplace_back(T{});
        auto& component = m_components_.back();
        if(entity_id != -1)
        {
            component.set_entity_id(entity_id);
        }
        return component;
    }
    
    auto get_component_of_entity_id(entity entity) ->T&
    {
        for(auto& component : m_components_)
        {
            if(component.get_entity_id() == entity.id)
            {
                return component;
            }
        }
        LOG(error)<<"Component not found: "<<std::type_index(typeid(T)).name();
        throw std::runtime_error("Component not found Exception");
    }
    
    auto get_components() ->std::vector<T>&
    {
        return m_components_;
    }
    
private:
   std::vector<T> m_components_{};
};
