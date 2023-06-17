#pragma once
#include "glm/vec2.hpp"

struct component_animation
{
    component_animation() = default;
    component_animation(int row,glm::vec2 frame_size, int frames, float speed,bool has_exit_time = false,float time =0):
    row(row),frame_size(frame_size),frames(frames),speed(speed),time(time),has_exit_time(has_exit_time){}
    
    int row{0}; // starts from 0
    glm::vec2 frame_size{32,32};
    int frames{4};//starts from 1
    float speed{24.0f};
    float time{0};
    bool has_exit_time;
};
