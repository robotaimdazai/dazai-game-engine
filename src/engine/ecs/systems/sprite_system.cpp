#include "sprite_system.h"
#include "../ecs.h"
#include "../../resource_manager.h"
#include "../components/sprite.h"
extern ecs g_ecs;

auto sprite_system::render() -> void
{
    for(auto const& entity: entities)
    {
        const auto& this_sprite = g_ecs.get_component<sprite>(entity);
        this_sprite.texture.render(this_sprite.offset.x,this_sprite.offset.y,this_sprite.renderer);
    }
}