#pragma once
#include <cassert>
#include <memory>
#include <unordered_map>
#include "system.h"
#include "../../globals.h"

class system_manager
{
public:
    
    template<typename T, typename ... Args>
    auto register_system(Args&&...args)->std::shared_ptr<T>  
    {
        const char* type_name = typeid(T).name();
        assert(m_systems_.find(type_name) == m_systems_.end() && "Registering system more than once.");
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        m_systems_.insert({type_name,system});
        return system;
    }
    
    template<typename T>
    auto set_signature(signature signature)->void
    {
        const char* type_name = typeid(T).name();
        assert(m_systems_.find(type_name) != m_systems_.end() && "System used before registered.");
        m_signatures_.insert({type_name,signature});
    }

    auto entity_destroyed(entity entity) -> void
    {
        for(auto const& pair : m_systems_)
        {
            auto const& system = pair.second;
            system->entities.erase(entity);
        }
    }

    auto entity_signature_changed(entity entity, signature entity_signature) -> void
    {
        for (auto const& pair : m_systems_)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& system_signature = m_signatures_[type];

            //if the entity signature matches the system signature, insert it
            if ((entity_signature & system_signature) == system_signature)
            {
                system->entities.insert(entity);
            }
            else
            {
                //if the entity signature does not match the system signature, erase it
                system->entities.erase(entity);
            }
        }
    }


private:
    //signature of every system
    std::unordered_map<const char*,signature> m_signatures_{};
    //all systems
    std::unordered_map<const char*,std::shared_ptr<class system>> m_systems_{};
};
