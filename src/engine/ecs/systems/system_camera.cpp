#include "system_camera.h"
#include "../ecs.h"
#include "../components/camera.h"
#include "../components/transform.h"

extern ecs g_ecs;
auto system_camera::update() -> void
{
    for(auto const& entity:entities)
    {
        auto this_transform = g_ecs.get_component<transform>(entity);
        auto this_camera = g_ecs.get_component<camera>(entity);
        auto view =glm::lookAt(this_transform.position,this_transform.position + (this_camera.inverse_forward),this_camera.up);
        view = glm::scale(view,glm::vec3(this_camera.zoom, this_camera.zoom,1));
        camera::view = view;
        camera::proj = glm::ortho(0.0f,this_camera.size.x,0.0f,this_camera.size.y,this_camera.near,this_camera.far);
    }
}
