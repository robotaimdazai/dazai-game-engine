#include "input_keyboard_state.h"

auto keyboard_state::get_key_value(SDL_Scancode key_code) const->bool
{
    return m_current_value_[key_code] == 1;
}

auto keyboard_state::get_key_state(SDL_Scancode key_code) const -> key_status
{
    if(m_previous_value_[key_code]==0)
    {
        if(m_current_value_[key_code]==0)
        {
            return none;
        }
        
        return just_pressed;
    }

    // when wasn't pressed previously
    if(m_current_value_[key_code]==0)
    {
        return just_released;
    }
    
    return held;
}

auto keyboard_state::is_down(SDL_Scancode key_code) const -> bool
{
    return get_key_value(key_code);
}

auto keyboard_state::is_up(SDL_Scancode key_code) const -> bool
{
    return !get_key_value(key_code);
}

auto keyboard_state::is_free(SDL_Scancode key_code) const -> bool
{
    return get_key_state(key_code) == none;
}

auto keyboard_state::is_just_pressed(SDL_Scancode key_code) const -> bool
{
    return get_key_state(key_code) == just_pressed;
}

auto keyboard_state::is_just_released(SDL_Scancode key_code) const -> bool
{
    return get_key_state(key_code) == just_released;
}

auto keyboard_state::is_held(SDL_Scancode key_code) const -> bool
{
    return get_key_state(key_code) == held;
}



