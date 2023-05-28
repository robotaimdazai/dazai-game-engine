#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "component.h"


//templates for components
class component_manager
{
public:
    
    template<typename T, typename... Args>
    auto create_component(Args&&... args) ->T*
    {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        auto component_ptr = component.get();
        m_components_[std::type_index(typeid(T))].emplace_back(std::move(component));
        return component_ptr;
    }

    template<typename T>
     auto get_component(uint32_t entity_id) ->T*
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

    template<typename T>
    auto get_all_components() ->std::vector<T*>
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
    std::unordered_map<std::type_index, std:: vector<std::unique_ptr<component>>> m_components_;
};
