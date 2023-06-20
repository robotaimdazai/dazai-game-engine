#include "input_manager.h"
#include <cstring>
#include <SDL_events.h>
#include <SDL_keyboard.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"

input_manager::input_manager()
{
    init();
}

input_manager::~input_manager()
= default;

auto input_manager::init() -> void
{
    //for keyboard
    m_input_state_.keyboard_state.m_current_value_ = SDL_GetKeyboardState(nullptr);
    memset(m_input_state_.keyboard_state.m_previous_value_,0,SDL_NUM_SCANCODES);

    //for mouse
    m_input_state_.mouse_state.m_current_value_ = SDL_GetMouseState(&m_input_state_.mouse_state.m_mouse_x_,
        &m_input_state_.mouse_state.m_mouse_y_);
    m_input_state_.mouse_state.m_previous_value_=0;
}

auto input_manager::prepare_for_update() -> void
{
    memcpy(m_input_state_.keyboard_state.m_previous_value_,m_input_state_.keyboard_state.m_current_value_,SDL_NUM_SCANCODES);

    //for mouse
    m_input_state_.mouse_state.m_previous_value_ = m_input_state_.mouse_state.m_current_value_;
    m_input_state_.mouse_state.m_current_value_ = SDL_GetMouseState(&m_input_state_.mouse_state.m_mouse_x_,
        &m_input_state_.mouse_state.m_mouse_y_);
}

auto input_manager::poll_inputs() -> bool
{
    SDL_Event event;
    SDL_PollEvent(&event);
    ImGui_ImplSDL2_ProcessEvent(&event);
    bool is_running = true;
    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        default:
            break;
    }
    return is_running;
}

auto input_manager::get_state() const -> const input_state&
{
    return m_input_state_;
}





