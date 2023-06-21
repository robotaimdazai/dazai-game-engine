#include "system_camera.h"
#include "../ecs.h"
#include "../components/component_camera.h"
#include "../components/component_transform.h"
#include "glm/ext/matrix_clip_space.hpp"

extern ecs g_ecs;
auto system_camera::update() -> void
{
    for(auto const& entity:entities)
    {
        auto this_transform = g_ecs.get_component<component_transform>(entity);
        auto this_camera = g_ecs.get_component<component_camera>(entity);
        auto view =glm::lookAt(this_transform.position ,this_transform.position + (this_camera.inverse_forward),this_camera.up);
        view = glm::scale(view,glm::vec3(this_camera.zoom, this_camera.zoom,1));
        component_camera::view = view;
        component_camera::proj = glm::ortho(
            -this_camera.size.x/2,this_camera.size.x/2,
            -this_camera.size.y/2,this_camera.size.y/2,
            this_camera.near,this_camera.far);
    }
}
