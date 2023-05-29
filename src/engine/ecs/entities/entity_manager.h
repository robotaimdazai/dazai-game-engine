#pragma once
#include <map>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "entity.h"

class entity_manager
{
public:
    entity_manager() = delete;
    static auto create_entity() ->entity;
    static auto get_entity(uint32_t entity_id) ->entity;
    static auto destroy_entity(uint32_t entity_id) ->void;
    static auto clean() ->void;
private:
    static uint32_t m_next_entity_id_;
    static std::unordered_map<uint32_t,entity> m_entities_;
};
