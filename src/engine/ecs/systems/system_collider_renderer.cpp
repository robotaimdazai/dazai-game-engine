#include "system_collider_renderer.h"
#include "../ecs.h"
#include "../../debug_draw.h"
#include "../../globals.h"
#include "../components/component_box_collider.h"
#include "../components/component_transform.h"

extern ecs g_ecs;

auto system_collider_renderer::render() -> void
{
    for(const entity& entity :entities)
    {
        const auto& rect = get_collider_rect(entity);
        debug_draw::rect(rect.position,rect.size,{0,1,0});
    }
}

auto system_collider_renderer::get_collider_rect(const entity& entity) -> rect
{
    auto& transform = g_ecs.get_component<component_transform>(entity);
    auto& collider = g_ecs.get_component<component_box_collider>(entity);
    glm::vec2 transform_pos = {transform.position.x,transform.position.y};
    auto collider_pos = transform_pos + collider.offset;
    rect collider_rect={collider_pos,collider.size};
    return  collider_rect;
}
