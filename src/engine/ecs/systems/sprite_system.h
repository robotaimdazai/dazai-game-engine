
#include <cstdint>
#include "system.h"
#include "../../game.h"
#include "../components/component_manager.h"
#include "../components/sprite_component.h"

class sprite_system: public i_system
{
public:
    sprite_system(SDL_Renderer*, component_manager<sprite_component>*);
    auto init() ->void override;
    auto update(uint32_t delta_time) ->void override;
    auto handle_event(const input_state& input_state) ->void override;
    auto render() ->void override;
    auto clean() ->void override;

private:
    component_manager<sprite_component>* m_sprite_component_manager_;
    SDL_Renderer* m_renderer_;
};
