#ifndef GAME_H
#define GAME_H
#include <cstdint>
#include <memory>
#include <vector>

#include "input_manager.h"

class game_state;

class game
{
    
public:
    game();
    virtual ~game();
    auto init(int screen_width, int screen_height)->void;
    auto load()->void;
    auto handle_inputs()->void;
    auto update(uint32_t delta_time)->void;
    auto render()->void;
    auto clean()->void;
    auto change_state(std::unique_ptr<game_state>)->void;
    auto push_state(std::unique_ptr<game_state>)->void;
    auto pop_state()->void;
    bool is_running;
    int window_width, window_height;

private:
    std::vector<std::unique_ptr<game_state>> m_game_states_;
    std::unique_ptr<input_manager> m_input_manager_;
};

#endif