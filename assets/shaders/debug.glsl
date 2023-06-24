#shader vertex
#version 410 core

layout(location = 0) in vec2 in_pos;

uniform mat4 u_mvp;

void main()
{
    gl_Position= u_mvp * vec4(in_pos,0.0,1.0);
    
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 o_color;
uniform vec3 u_color;

void main()
{
    o_color = vec4(u_color,1.0);
}