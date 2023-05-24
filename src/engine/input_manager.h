#pragma once

#include "input_state.h"

class input_manager
{
public:
    input_manager();
    virtual ~input_manager();
    auto prepare_for_update()->void;
    auto poll_inputs()->bool;
    auto get_state()const->const input_state&;
private:
    auto init()->void;
    input_state m_input_state_;
};
