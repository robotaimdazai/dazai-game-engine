#pragma once
#include "../../input_state.h"
#include "../core/system.h"

class system_player_input : public system
{
public:
    auto handle_event(const input_state& input)->void;
    
};
