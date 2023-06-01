#pragma once
#include <memory>
#include "core/component_manager.h"
#include "core/entity_manager.h"
#include "core/system_manager.h"

class ecs
{
public:
    auto init()->void
    {
        m_component_manager_ = std::make_unique<component_manager>();
        m_entity_manager_ = std::make_unique<entity_manager>();
        m_system_manager_ = std::make_unique<system_manager>();
    }

    // entity-------------------------------
    auto add_entity()->entity
    {
        return m_entity_manager_->add_entity();
    }

    auto destroy_entity(entity entity)->void
    {
        m_entity_manager_->destroy_entity(entity);
        m_component_manager_->entity_destroyed(entity);
        m_system_manager_->entity_destroyed(entity);
    }

    //component-----------------------------
    template<typename T>
    auto register_component()->void
    {
        m_component_manager_->register_component<T>();
    }

    template<typename T>
    auto add_component(entity entity)->void
    {
        m_component_manager_->add_component<T>(entity);
        auto signature = m_entity_manager_->get_signature(entity);
        signature.set(m_component_manager_->get_component_type<T>(), true);
        m_entity_manager_->set_signature(entity, signature);
        m_system_manager_->entity_signature_changed(entity, signature);
    }

    template<typename T>
    auto remove_component(entity entity)->void
    {
        m_component_manager_->remove_component<T>(entity);
        auto signature = m_entity_manager_->get_signature(entity);
        signature.set(m_component_manager_->get_component_type<T>(), false);
        m_entity_manager_->set_signature(entity, signature);
        m_system_manager_->entity_signature_changed(entity, signature);
    }

    template<typename T>
    auto get_component(entity entity)->T&
    {
        return m_component_manager_->get_component<T>(entity);
    }

    template<typename T>
    auto get_component_type()->uint8_t
    {
        return m_component_manager_->get_component_type<T>();
    }

    //system--------------------------------

    template<typename T>
    auto register_system()->std::shared_ptr<T>
    {
        return m_system_manager_->register_system<T>();
    }

    template<typename T>
    auto set_system_signature(signature signature)->void
    {
        m_system_manager_->set_signature<T>(signature);
    }
    
private:
    std::unique_ptr<component_manager> m_component_manager_;
    std::unique_ptr<entity_manager> m_entity_manager_;
    std::unique_ptr<system_manager> m_system_manager_;
};
