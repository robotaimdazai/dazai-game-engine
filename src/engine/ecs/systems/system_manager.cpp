#include "system_manager.h"

std::vector<std::unique_ptr<i_system>> system_manager::m_systems_;

auto system_manager::register_system(i_system* system) ->void
{
    m_systems_.emplace_back(system);
}
auto system_manager::delete_system(const i_system* system) ->void
{
    for(auto it = m_systems_.begin(); it != m_systems_.end(); ++it)
    {
        if(it->get() == system)
        {
            m_systems_.erase(it);
            break;
        }
    }
}
auto system_manager::init_all() ->void
{
    for(const auto& system : m_systems_)
    {
        system->init();
    }
}

auto system_manager::update_all(uint32_t delta_time) ->void
{
    for(auto& system : m_systems_)
    {
        system->update(delta_time);
    }
}

auto system_manager::handle_event_all(const input_state& input_state) ->void
{
    for(const auto& system : m_systems_)
    {
        system->handle_event(input_state);
    }
}

auto system_manager::render_all() ->void
{
    for(const auto& system : m_systems_)
    {
        system->render();
    }
}

auto system_manager::clean_all() ->void
{
    for(const auto& system : m_systems_)
    {
        system->clean();
    }
}