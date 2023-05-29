#include "entity_manager.h"

uint32_t entity_manager::m_next_entity_id_ = 0;
std::unordered_map<uint32_t,entity> entity_manager::m_entities_;
auto entity_manager::create_entity() ->entity
{
    entity entity{};
    entity.id = m_next_entity_id_;
    m_entities_.emplace(entity.id,entity);
    m_next_entity_id_++;
    return entity;
}

auto entity_manager::get_entity(const uint32_t entity_id) ->entity
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
}