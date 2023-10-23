#pragma once
#include "../core/system.h"

class system_renderer_text:public system
{
public:
    system_renderer_text();
    ~system_renderer_text();
    auto render()const ->void;
};
