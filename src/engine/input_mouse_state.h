#pragma once
#include <cstdint>

#include "input_keyboard_state.h"

class mouse_state
{
    friend class input_manager;
    
public:
    auto get_mouse_x()const -> int;
    auto get_mouse_y()const -> int;
    
    auto is_up(int index)const->bool;
    auto is_free(int index)const->bool;
    auto is_just_pressed(int index)const->bool;
    auto is_down(int index)const->bool;
    auto is_held(int index)const->bool;
    auto is_just_released(int index)const->bool;

private:
    auto get_key_state(int index) const -> key_status;
    auto get_key_value(int index) const -> bool;
    
    uint32_t m_current_value_;
    uint32_t m_previous_value_;
    int m_mouse_x_;
    int m_mouse_y_;
};
