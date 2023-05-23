#ifndef GAME_STATE_MAIN_H
#define GAME_STATE_MAIN_H

#include "../engine/game_state.h"

class game_state_main:public game_state
{
public:
    game_state_main();
    virtual ~game_state_main();

    auto load() -> void;
    auto clean() -> void;
    auto pause() -> void;
    auto resume() -> void;
    auto update(uint32_t delta_time) -> void;
    auto draw() -> void;
    auto set_game(game* game) -> void;

private:
    game* m_game_{};
    uint32_t m_counter_{};
};

#endif