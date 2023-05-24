#pragma once
#include <SDL_scancode.h>

enum key_status
{
    none,
    just_pressed,
    held,
    just_released
};

class keyboard_state
{
    friend class input_manager;
public:
    auto is_up(SDL_Scancode) const->bool; //when key is up and just released
    auto is_free(SDL_Scancode) const->bool; //when key is free, not when just released
    auto is_just_pressed(SDL_Scancode) const->bool; //when key is just pressed
    auto is_down(SDL_Scancode) const->bool; //when key is down or just pressed
    auto is_held(SDL_Scancode) const->bool; //when key is down and held
    auto is_just_released(SDL_Scancode) const->bool; //when key is just released

private :
    const uint8_t* m_current_value_;
    uint8_t m_previous_value_[SDL_NUM_SCANCODES];
    auto get_key_value(SDL_Scancode) const->bool;
    auto get_key_state(SDL_Scancode)const->key_status;
    
};