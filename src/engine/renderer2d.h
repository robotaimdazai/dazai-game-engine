#pragma once
#include "ecs/components/component_sprite.h"

class renderer2d
{
    
public:
    static auto init()->void;
    static auto render_begin()->void;
    static auto render_end()->void;
    static auto render_sprite(const glm::vec3& position,const float rot_z ,const component_sprite& sprite)->void;
    static auto shutdown()->void;
    
};
