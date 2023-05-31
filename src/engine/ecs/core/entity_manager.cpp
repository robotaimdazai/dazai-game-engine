#include "entity_manager.h"
#include <assert.h>

entity_manager::entity_manager()
{
    for(uint32_t entity = 0; entity < MAX_ENTITIES; entity++)
    {
        m_available_entities_.push(entity);
    }
}
auto entity_manager::add_entity() ->entity
{
    assert(m_living_entity_count_< MAX_ENTITIES && "Too many entities in existence.");
    const entity entity{m_available_entities_.front()};
    m_available_entities_.pop();
    ++m_living_entity_count_;
    return entity;
}

auto entity_manager::destroy_entity(const entity entity) ->void
{
    assert(entity<MAX_ENTITIES && "Entity out of range.");
    m_signature_[entity].reset();
    m_available_entities_.push(entity);
    --m_living_entity_count_;
}

auto entity_manager::set_signature(const entity entity, const signature signature) ->void
{
    assert(entity<MAX_ENTITIES && "Entity out of range.");
    m_signature_[entity] = signature;
}

auto entity_manager::get_signature(const entity entity) const ->signature
{
    assert(entity<MAX_ENTITIES && "Entity out of range.");
    return m_signature_[entity];
}

auto entity_manager::clean() ->void
{
    
}