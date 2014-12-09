#version 410 core

in vec3 vs_position;
in vec3 vs_normal;
in vec2 vs_texcoord;
in vec4 vs_color;

uniform mat4 u_view_mat;
uniform mat4 u_model_mat;

uniform vec3 u_light_pos;

uniform vec4 u_la;
uniform vec4 u_ls;
uniform vec4 u_ld;

uniform vec4 u_ks;
uniform vec4 u_kd;
uniform vec4 u_ka;

uniform float u_specular_power;

out vec4 fs_color;

void main( void )
{
    vec3 dir_to_pos = normalize( vs_position );
    vec3 normal = normalize( vs_normal );
    vec3 reflected = reflect( dir_to_pos, normal );
    
    reflected = vec3( inverse(u_view_mat * u_model_mat ) * vec4( reflected, 0.f ) );
//
    // point light position in view space
    vec3 point_light_view_pos = vec3( u_view_mat * u_model_mat * vec4(u_light_pos, 1.f) );
    // distance to light
    vec3 dist_to_light = point_light_view_pos - vs_position;
    //direction to light
    vec3 dir_to_light = normalize( dist_to_light );
    // dot prod of normal and light direction
    float dot_prod_diffuse = dot( dir_to_light, vs_normal );
    dot_prod_diffuse = max( dot_prod_diffuse, 0.f );

    vec4 id = u_ld * u_kd * dot_prod_diffuse;

    vec3 reflection_view = reflect( -dir_to_light, vs_normal );
    vec3 surface_to_camera = normalize( -vs_position );
    float dot_prod_specular = dot( reflection_view, surface_to_camera );
    dot_prod_specular = max( dot_prod_specular, 0.f );
    float specular_factor = pow(dot_prod_specular, u_specular_power );
    
    vec4 is = u_ls * u_ks * specular_factor;
//
    vec4 ia = u_la * u_ka;

    fs_color = ia + id + is;
}