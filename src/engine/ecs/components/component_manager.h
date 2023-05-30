#pragma once
#include <memory>
#include "../entities/entity.h"
#include "base_component_manager.h"
template<typename T>
class component_manager final : public base_component_manager
{
public:
    component_manager() = default;
    
    auto add_component(int entity_id) ->T&
    {
        auto component = std::make_unique<T>();
        auto component_ptr = component.get();
        if(entity_id != -1)
        {
            component_ptr->set_entity_id(entity_id);
        }
        m_components_.emplace_back(std::move(component));
        return *component_ptr;
    }
    
    auto get_component_of_entity_id(uint32_t entity_id) ->T* 
    {
        for(auto& component : m_components_)
        {
            T* typed_component = static_cast<T*>(component.get());
            if(typed_component->get_entity_id() == entity_id)
            {
                return typed_component;
            }
        }
        return nullptr;
    }
    
    auto get_components() ->std::vector<T*>
    {
        std::vector<T*> components;
        for(auto& component : m_components_)
        {
            T* typed_component = static_cast<T*>(component.get());
            components.emplace_back(typed_component);
        }
        return components;
    }
private:
   std::vector<std::unique_ptr<T>> m_components_{};
};
