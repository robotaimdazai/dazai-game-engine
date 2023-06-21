#include "input_mouse_state.h"

#include <SDL_mouse.h>

#include "globals.h"

auto mouse_state::get_mouse_pos() const -> glm::vec2
{
    glm::vec2 normalized ={static_cast<float>(m_mouse_x_)/GLOBALS::screen_size.x,
        1-(static_cast<float>(m_mouse_y_)/GLOBALS::screen_size.y)};

    float ndc_x = (2*normalized.x)-1;
    float ndc_y = (2*normalized.y)-1;

    return {ndc_x,ndc_y};
}

auto mouse_state::get_key_value(int index) const -> bool
{
    return (m_current_value_ & SDL_BUTTON(index)) ==1;
}

auto mouse_state::get_key_state(int index) const -> key_status
{
    if((m_previous_value_ & SDL_BUTTON(index)) == 0)
    {
        if((m_current_value_ & SDL_BUTTON(index)) ==0)
        {
            return none;
        }
        
        return just_pressed;
    }

    if((m_current_value_ & SDL_BUTTON(index)) ==0)
    {
        return just_released;
    }

    return held;
}

auto mouse_state::is_down(int index) const -> bool
{
    return get_key_value(index);
}

auto mouse_state::is_up(int index) const -> bool
{
    return !get_key_value(index);
}

auto mouse_state::is_free(int index) const -> bool
{
    return get_key_state(index) == none;
}

auto mouse_state::is_just_pressed(int index) const -> bool
{
    return get_key_state(index) == just_pressed;
}

auto mouse_state::is_just_released(int index) const -> bool
{
    return get_key_state(index) == just_released;
}

auto mouse_state::is_held(int index) const -> bool
{
    return get_key_state(index) == held;
}


