#include "entity_manager.h"

entity_manager::entity_manager()
{
    m_next_entity_id_ = 0;
}
auto entity_manager::add_entity() ->entity
{
    entity entity{};
    entity.id = m_next_entity_id_;
    m_entities_.emplace(entity.id,entity);
    m_next_entity_id_++;
    return entity;
}

auto entity_manager::get_entity(const uint32_t entity_id) const ->entity
{
    return m_entities_.at(entity_id);
}

auto entity_manager::destroy_entity(const uint32_t entity_id) ->void
{
    m_entities_.erase(entity_id);
}

auto entity_manager::clean() ->void
{
    m_next_entity_id_ = 0;
    m_entities_.clear();
    m_component_managers_.clear();
}