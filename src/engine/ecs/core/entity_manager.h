#pragma once
#include <bitset>
#include <queue>
#include "../../globals.h"


class entity_manager
{
public:
    entity_manager();
    auto add_entity() ->entity;
    auto destroy_entity(const entity entity) ->void;
    auto set_signature(entity entity, signature signature) ->void;
    auto get_signature(entity entity) const ->signature;
    auto clean() ->void;
private:
    uint32_t m_living_entity_count_{};
    std::queue<uint32_t> m_available_entities_{};
    signature m_signature_[MAX_COMPONENTS];
};
