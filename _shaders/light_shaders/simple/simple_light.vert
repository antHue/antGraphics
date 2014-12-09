#version 410 core

layout ( location = 0 ) in vec3 attr_position;

uniform mat4 u_view_mat;
uniform mat4 u_proj_mat;
uniform mat4 u_model_mat;

void main( void )
{
    vec3 vs_position = vec3( u_view_mat * u_model_mat * vec4( attr_position, 1.f ) );
    
    gl_Position = u_proj_mat * vec4( vs_position, 1.f );
}