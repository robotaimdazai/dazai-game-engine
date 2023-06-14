#pragma once
#include "glm/vec2.hpp"

struct animation
{
    animation() = default;
    animation(int row,glm::vec2 frame_size, int frames, float fps,float time =0):
    row(row),frame_size(frame_size),frames(frames),fps(fps),time(time){}
    
    int row{1};
    glm::vec2 frame_size{32,32};
    int frames{4};
    float fps{24.0f};
    float time{0};
    
};
