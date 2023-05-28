#pragma once

class vec2
{
public:
    float x,y;
    vec2(float x =0.0f,float y = 0.0f):x(x),y(y)
    {
        
    }
    auto operator+(const vec2& other) const->vec2    
    {
        return vec2(x+other.x, y+other.y);
    }
    auto operator-(const vec2& other) const->vec2    
    {
        return vec2(x-other.x, y-other.y);
    }
};
