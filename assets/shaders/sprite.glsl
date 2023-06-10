#shader vertex
#version 410 core

layout(location =0)in vec3 in_position;
layout(location =1)in vec2 in_tex_coord;

uniform mat4 u_model;
uniform mat4 u_proj;
uniform mat4 u_view;

out vec2 v_tex_coord;

void main()
{
     //v_tex_coord  = in_tex_coord;
     mat4 mvp = u_proj * u_view * u_model;
     gl_Position = mvp * vec4(in_position , 1.0f);
}

#shader fragment
#version 410 core

layout(location =0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;
   
in vec2 v_tex_coord;

void main()
{
    vec4 tex_color = texture(u_texture, v_tex_coord);
    //color = tex_color;
    color = u_color;
}
