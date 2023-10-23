#shader vertex
#version 410 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_tex_coord;
layout (location = 2) in vec4 in_color;

uniform mat4 u_proj_view;
out vec2 v_tex_coord;
out vec4 v_color;

void main()
{
    v_color  = in_color;
    v_tex_coord  = in_tex_coord;
    gl_Position = u_proj_view * vec4(in_position, 1.0);
} 

#shader fragment
#version 410 core

layout(location =0) out vec4 color;
uniform sampler2D u_texture;

in vec2 v_tex_coord;
in vec4 v_color;

void main()
{
    vec4 sampled = vec4(1.0,1.0,1.0,texture(u_texture,v_tex_coord).r);
    color = v_color * sampled;
}