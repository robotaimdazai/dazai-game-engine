#pragma once
#include "../../shader.h"
#include "../core/system.h"

class system_renderer_sprite: public system
{
public:
    system_renderer_sprite();
    ~system_renderer_sprite();
    auto render() const ->void;
};
