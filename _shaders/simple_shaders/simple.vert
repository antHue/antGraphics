#version 410 core

layout ( location = 0 ) in vec3 attr_position;
layout ( location = 1 ) in vec4 attr_color;
layout ( location = 2 ) in vec3 attr_normal;
layout ( location = 3 ) in vec2 attr_texcoord;

uniform mat4 u_view_mat;
uniform mat4 u_proj_mat;
uniform mat4 u_model_mat;

out vec3 vs_position;
out vec4 vs_color;
out vec3 vs_normal;
out vec2 vs_texcoord;

void main( void )
{
    vs_position = vec3( u_view_mat * u_model_mat * vec4( attr_position, 1.f ) );
    vs_normal = vec3( u_view_mat * u_model_mat *vec4( attr_normal, 0.f ) );
    
    vs_color = attr_color;
    vs_texcoord = attr_texcoord;
    
    gl_Position = u_proj_mat * vec4( vs_position, 1.f );
}