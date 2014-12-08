#version 410 core

in vec3 vs_position;
in vec3 vs_texcoord;

uniform samplerCube u_texture;

out vec4 fs_color;

void main( void )
{
    vec4 texel = texture( u_texture, vs_texcoord );
    fs_color = texel;
}