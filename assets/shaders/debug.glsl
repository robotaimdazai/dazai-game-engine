#shader vertex
#version 410 core

layout(location = 0) in vec2 in_pos;

uniform mat4 u_mvp;
uniform int u_use_mvp;

void main()
{
    if(u_use_mvp == 1)
    {
        gl_Position= u_mvp * vec4(in_pos,0.0,1.0);
    }
    else
    {
        gl_Position= vec4(in_pos,0.0,1.0);
    }
    
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 o_color;
uniform vec3 u_color;

void main()
{
    o_color = vec4(u_color,1.0);
}