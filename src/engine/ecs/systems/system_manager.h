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
    static auto init_all() ->void;
    static auto update_all(uint32_t delta_time) ->void;
    static auto handle_event_all(const input_state& input_state) ->void;
    static auto render_all() ->void;
    static auto clean_all() ->void;

private:
    static std::vector<std::unique_ptr<i_system>> m_systems_;
};
