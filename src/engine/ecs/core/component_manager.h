#pragma once
#include <cassert>
#include <memory>
#include <unordered_map>
#include "i_component_array.h"
#include "component_array.h"

class component_manager
{
public:
    template<typename T>
    auto register_component() ->void
    {
        const char* type_name = typeid(T).name();
        assert(m_component_types_.find(type_name) == m_component_types_.end() && "Registering component type more than once.");
        m_component_types_.insert({type_name,m_next_component_type_});
        m_component_arrays_.insert({type_name,std::make_shared<component_array<T>>()});
        ++m_next_component_type_;
    }
    template<typename T>
    auto get_component_type()->uint8_t
    {
        const char* type_name = typeid(T).name();
        assert(m_component_types_.find(type_name) != m_component_types_.end() && "Component not registered before use.");
        return m_component_types_[type_name];
    }
    template<typename T>
    auto add_component(entity entity) ->void
    {
        get_component_array<T>()->set_data(entity);
    }

    template <typename T>
    auto remove_component(entity entity) ->void
    {
        get_component_array<T>()->remove_component(entity);
    }

    template<typename T>
    auto get_component(entity entity) ->T&
    {
        return get_component_array<T>()->get_data(entity);
    }

    template<typename T>
    auto try_get_component(const entity& entity)->T*
    {
        return get_component_array<T>()->try_get_data(entity);
    }

    auto entity_destroyed(entity entity) ->void
    {
        for(auto const& pair : m_component_arrays_)
        {
            auto const& component = pair.second;
            component->entity_destroyed(entity);
        }
    }

private:
    //string to int type mapping, this type name is returned by typeid(T).name()
    std::unordered_map<const char*, uint8_t> m_component_types_{};
    //string to component array
    std::unordered_map<const char*, std::shared_ptr<i_component_array>> m_component_arrays_{};
    uint8_t m_next_component_type_{};

    template<typename T>
    auto get_component_array() ->std::shared_ptr<component_array<T>>
    {
        const char* type_name = typeid(T).name();
        assert(m_component_types_.find(type_name) != m_component_types_.end() && "Component not registered before use.");
        return std::static_pointer_cast<component_array<T>>(m_component_arrays_[type_name]);
    }
};
