#include "system_rigidbody2d.h"

#include "../ecs.h"
#include "../components/component_rigidbody2d.h"
#include "../components/component_transform.h"

extern ecs g_ecs;
auto system_rigidbody2d::fixed_update(float fixed_delta_time) -> void
{
    for (auto& entity:entities)
    {
        auto& rigidbody = g_ecs.get_component<component_rigidbody2d>(entity);
        auto& transform = g_ecs.get_component<component_transform>(entity);
        //move
        const glm::vec3 velocity = {rigidbody.velocity.x,rigidbody.velocity.y,0};
        transform.position+=velocity ;
    }
}
