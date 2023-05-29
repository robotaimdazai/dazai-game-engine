#pragma once

struct input_state;

class i_system
{
public:
    virtual ~i_system() = default;
    virtual auto init() ->void = 0;
    virtual auto update(uint32_t delta_time) ->void = 0;
    virtual auto render() ->void = 0;
    virtual auto handle_event(const input_state& input_state) ->void = 0;
    virtual auto clean() ->void = 0;
};
