#shader vertex
#version 410 core

layout(location =0)in vec3 in_position;
layout(location =1)in vec2 in_tex_coord;
layout(location =2)in vec4 in_color;

uniform mat4 u_proj_view;
out vec2 v_tex_coord;
out vec4 v_color;

void main()
{
    v_tex_coord  = in_tex_coord;
    v_color  = in_color;
    mat4 mvp = u_proj_view;
    gl_Position = mvp * vec4(in_position , 1.0f);
}

#shader fragment
#version 410 core

layout(location =0) out vec4 color;
uniform sampler2D u_texture;
   
in vec2 v_tex_coord;
in vec4 v_color;

void main()
{
    vec4 tex = texture(u_texture, v_tex_coord);
    color = v_color * tex ;
}
