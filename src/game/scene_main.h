#ifndef GAME_STATE_MAIN_H
#define GAME_STATE_MAIN_H

#include "../engine/scene.h"

class scene_main:public i_scene
{
public:
    scene_main() = default;
    ~scene_main() override = default;

    auto load() -> void override;
    auto clean() -> void override;
    auto pause() -> void override;
    auto resume() -> void override;
    auto update(uint32_t delta_time) -> void override;
    auto render() -> void override;
    auto set_game(game* game) -> void override;
    auto handle_event(const input_state&) -> void override;
    auto on_gui() -> void override;

private:
    game* m_game_{};
};

#endif