#pragma once
struct component_box_collider
{
    glm::vec2 offset{-50,-50};
    glm::vec2 size{100, 100};
    bool is_trigger{false};
};
