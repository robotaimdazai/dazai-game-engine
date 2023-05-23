#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "game.h"

class game_state
{
public:
    virtual ~game_state() = default;
    virtual auto load()->void =0;
    virtual auto clean()->void =0;
    virtual auto update(uint32_t delta_time)->void=0;
    virtual auto draw()->void = 0;
    virtual auto pause()->void = 0;
    virtual auto resume()->void = 0;
    virtual auto set_game(game* game)->void=0;
};
#endif