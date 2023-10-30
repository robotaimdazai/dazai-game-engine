#include "system_renderer_text.h"
#include "../ecs.h"
#include "../../text_renderer.h"
#include "../components/component_text.h"
#include "../components/component_transform.h"

extern ecs g_ecs;
system_renderer_text::system_renderer_text()
{
    text_renderer::init();
}

system_renderer_text::~system_renderer_text()
{
    text_renderer::shutdown();
}

auto system_renderer_text::render() const -> void
{
    text_renderer::render_begin();
    //all entities will iterate here
    for(auto const& entity: entities)
    {
        auto& text = g_ecs.get_component<component_text>(entity);
        const auto& transform = g_ecs.get_component<component_transform>(entity);
        text_renderer::render_text(text.text,transform.position,transform.scale,text.color,text.font_id);
    }
    text_renderer::render_end();
}
