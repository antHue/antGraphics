#version 410 core

in vec3 vs_position;
in vec4 vs_color;
in vec3 vs_normal;
in vec2 vs_texcoord;

/* color : output color sent to the screen */
out vec4 color;

void main( void )
{
    color = vs_color;
}