#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "system.h"

class system_manager
{
public:
    static auto register_system(i_system* system) ->void;
    static auto delete_system(const i_system* system) ->void;
    static auto init() ->void;
    static auto update(uint32_t delta_time) ->void;
    static auto handle_event(const input_state& input_state) ->void;
    static auto render() ->void;
    static auto clean() ->void;

private:
    static std::vector<std::unique_ptr<i_system>> m_systems_;
};
