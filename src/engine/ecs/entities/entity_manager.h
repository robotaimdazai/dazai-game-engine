#pragma once
#include <map>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "entity.h"
#include "../../logger.h"
#include "../components/base_component_manager.h"
#include "../components/component_manager.h"

class entity_manager
{
public:
    entity_manager();
    auto add_entity() ->entity;
    auto get_entity(uint32_t entity_id) const ->entity;
    auto destroy_entity(uint32_t entity_id) ->void;

    template<typename T>
    auto get_component(entity entity) -> T&
    {
        auto component_manager = get_component_manager<T>();
        if(component_manager==nullptr)
        {
            LOG(error)<<"Unable to get component, component manager is null: "<<std::type_index(typeid(T)).name();
        }
        auto& component =component_manager->get_component_of_entity_id(entity);
        return component;
    }
    
    template<typename T>
    auto add_component(entity entity) ->T&
    {
        auto component_manager = get_component_manager<T>();
        if(component_manager==nullptr)
        {
            LOG(warning)<<"Component manager was missing, registering component manager: "<<std::type_index(typeid(T)).name();
            add_component_manager<T>();
            component_manager = get_component_manager<T>();
        }
        return component_manager->add_component(entity.id);
    }

    //template functions
    template<typename T>
    auto get_component_manager() ->component_manager<T>*
    {
        const auto iter = m_component_managers_.find( std::type_index(typeid(T)) );
        if(iter==m_component_managers_.end())
        {
            return nullptr;
        }
        auto this_manager = static_cast<component_manager<T>*>(iter->second.get());
        return this_manager;
    }
    template<typename T>
    auto add_component_manager() ->void
    {
        m_component_managers_.emplace(std::type_index(typeid(T)), new component_manager<T>());
    }
    
    auto clean() ->void;
private:
    uint32_t m_next_entity_id_;
    std::unordered_map<uint32_t,entity> m_entities_;
    std::unordered_map<std::type_index, std::unique_ptr<base_component_manager>> m_component_managers_;
};
