#include "system_manager.h"

auto system_manager::add_system(i_system* system) ->void
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
auto system_manager::init() const ->void
{
    for(const auto& system : m_systems_)
    {
        system->init();
    }
}

auto system_manager::update(uint32_t delta_time) const ->void
{
    for(auto& system : m_systems_)
    {
        system->update(delta_time);
    }
}

auto system_manager::handle_event(const input_state& input_state) const ->void
{
    for(const auto& system : m_systems_)
    {
        system->handle_event(input_state);
    }
}

auto system_manager::render() const ->void
{
    for(const auto& system : m_systems_)
    {
        system->render();
    }
}

auto system_manager::clean() const ->void
{
    for(const auto& system : m_systems_)
    {
        system->clean();
    }
}