#pragma once
#include "../../input_state.h"
#include "../core/system.h"
#include "glm/vec3.hpp"

class system_player_movement : public system
{
public:
    auto update(const float delta_time) ->void;
    auto handle_event(const input_state& input)->void;

private:
    glm::vec3 m_direction_{0.0f,0.0f,0.0f};
};
