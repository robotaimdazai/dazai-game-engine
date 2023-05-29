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
    entity_manager() = delete;
    static auto create_entity() ->entity;
    static auto get_entity(uint32_t entity_id) ->entity;
    static auto destroy_entity(uint32_t entity_id) ->void;

    template<typename T>
    static auto get_component(uint32_t entity_id) -> T*
    {
        auto component_manager = get_component_manager<T>();
        if(component_manager == nullptr)
        {
            LOG(warning)<<"Can't get component, manager not found: "<<std::type_index(typeid(T)).name();   
            return nullptr;
        }
        return component_manager->get_component_of_entity_id(entity_id);
    }
    
    template<typename T>
    static auto add_component(uint32_t entity_id) ->T*
    {
        auto component_manager = get_component_manager<T>();
        if(component_manager == nullptr)
        {
            LOG(warning)<<"Can't add component, manager not found: "<<std::type_index(typeid(T)).name();   
            return nullptr;
        }
        return component_manager->add_component(entity_id);
    }

    //template functions
    template<typename T>
    static auto get_component_manager() ->component_manager<T>*
    {
        const auto iter = m_component_managers_.find( std::type_index(typeid(T)) );
        if(iter == m_component_managers_.end()) 
        {
            LOG(warning)<<"Component manager not found: "<<std::type_index(typeid(T)).name();   
            return nullptr;
        }   
        auto this_manager =m_component_managers_.at(std::type_index(typeid(T))).get();
        if(this_manager == nullptr)
        {
            LOG(warning)<<"Component manager not found: "<<std::type_index(typeid(T)).name();   
            return nullptr;
        }
        return static_cast<component_manager<T>*>(this_manager);
    }
    template<typename T>
    static auto register_component_manager(base_component_manager* component_manager) ->void
    {
        m_component_managers_.emplace(std::type_index(typeid(T)),std::move(component_manager));
    }
    static auto clean() ->void;
private:
    static uint32_t m_next_entity_id_;
    static std::unordered_map<uint32_t,entity> m_entities_;
    static std::unordered_map<std::type_index, std::unique_ptr<base_component_manager>> m_component_managers_;
};
