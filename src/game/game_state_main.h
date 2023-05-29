#ifndef GAME_STATE_MAIN_H
#define GAME_STATE_MAIN_H

#include "../engine/game_state.h"

class game_state_main:public i_game_state
{
public:
    game_state_main() = default;
    virtual ~game_state_main() = default;

    auto load() -> void;
    auto clean() -> void;
    auto pause() -> void;
    auto resume() -> void;
    auto update(uint32_t delta_time) -> void;
    auto render() -> void;
    auto set_game(game* game) -> void;
    auto handle_event(const input_state&) -> void;

private:
    game* m_game_{};
};

#endif