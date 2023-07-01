﻿#include "system_renderer_sprite.h"
#include "../ecs.h"
#include "../../renderer2d.h"
#include "../../resource_manager.h"
#include "../components/component_sprite.h"
#include "../components/component_transform.h"
#include "glm/gtx/quaternion.hpp"

extern ecs g_ecs;

system_renderer_sprite::system_renderer_sprite()
{
    renderer2d::init();
}

system_renderer_sprite::~system_renderer_sprite()
{
    renderer2d::shutdown();
}

auto system_renderer_sprite::render() const -> void
{
    renderer2d::render_begin();
    for(auto const& entity: entities)
    {
        auto& sprite = g_ecs.get_component<component_sprite>(entity);
        const auto& transform = g_ecs.get_component<component_transform>(entity);
        
        for (int i =0;i<10000;i++)
        {
            glm::vec3 pos = {rand()%500,rand()%500,0};
            renderer2d::render_sprite(pos,transform.rotation.z,sprite);
            
        }
    }
    renderer2d::render_end();
    
}


