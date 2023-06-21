#include "system_collision_detection.h"
#include "../ecs.h"
#include "../components/component_box_collider.h"
#include "../components/component_transform.h"

extern ecs g_ecs;

auto system_collision_detection::update(float delta_time) -> void
{
    for(auto const& entity:entities)
    {
        auto& transform = g_ecs.get_component<component_transform>(entity);
        auto& collider = g_ecs.get_component<component_box_collider>(entity);
        glm::vec2 pos = {transform.position.x,transform.position.y};
        collider.position = pos + collider.offset;
    }
}

