#version 410 core

layout (location = 0) in vec3 attr_position;     // vertex position
layout (location = 1) in vec4 attr_color;   // vertex color
layout (location = 2) in vec3 attr_normal;  // vertex normal
layout (location = 3) in vec2 attr_texcoord;     //  vertex tex

uniform mat4 u_view_mat;
uniform mat4 u_proj_mat;
uniform mat4 u_model_mat;

out vec3 vs_position;    // vertex position in view space
out vec4 vs_color;  // vertex color
out vec3 vs_normal; // vertex normal in view space
out vec2 vs_texcoord;    //  vertex tex

/*  vertex shader transforms vertex positions into clip space */
void main( void )
{
    vs_position = vec3( u_view_mat * u_model_mat * vec4( attr_position, 1.f ) );
    vs_normal = vec3( u_view_mat * u_model_mat *vec4( attr_normal, 0.f ) );
    
    vs_color = attr_color;
    vs_texcoord = attr_texcoord;
    
    gl_Position = u_proj_mat * vec4( vs_position, 1.f );
}