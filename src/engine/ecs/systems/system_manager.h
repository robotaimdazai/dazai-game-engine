#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "system.h"

class system_manager
{
public:
    auto add_system(i_system* system) ->void;
    auto delete_system(const i_system* system) ->void;
    auto init() const ->void;
    auto update(uint32_t delta_time) const ->void;
    auto handle_event(const input_state& input_state) const ->void;
    auto render() const ->void;
    auto clean() const ->void;

private:
    std::vector<std::unique_ptr<i_system>> m_systems_;
};
