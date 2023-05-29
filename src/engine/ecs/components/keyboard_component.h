#pragma once

#include "component.h"
#include "../../input_keyboard_state.h"

struct keyboard_component:component
{
    keyboard_state keyboard_state{};
};
