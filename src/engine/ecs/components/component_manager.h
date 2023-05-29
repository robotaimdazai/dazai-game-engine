#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "component.h"

template<typename T>
class component_manager
{
public:
    component_manager() = default;
    
    auto add_component() ->T*
    {
        auto component = std::make_unique<T>();
        auto component_ptr = component.get();
        m_components_[std::type_index(typeid(T))].emplace_back(std::move(component));
        return component_ptr;
    }
    
    auto get_component_of_entity_id(uint32_t entity_id) ->T*
    {
        auto& components = m_components_[std::type_index(typeid(T))];
        for(auto& component : components)
        {
            T* typed_component = static_cast<T*>(component.get());
            if(typed_component->get_entity_id() == entity_id)
            {
                return static_cast<T*>(component.get());
            }
        }
        return nullptr;
    }
    
    auto get_components() ->std::vector<T*>
    {
        std::vector<T*> components;
        auto& components_vector = m_components_[std::type_index(typeid(T))];
        for(auto& component : components_vector)
        {
            T* typed_component = static_cast<T*>(component.get());
            components.emplace_back(typed_component);
        }
        return components;
    }
private:
    std::unordered_map<std::type_index, std:: vector<std::unique_ptr<T>>> m_components_;
};
