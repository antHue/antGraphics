#version 410 core

in vec3 vs_position;   // vertex position in eye space
in vec3 vs_normal;     // vertex normal in eye space
in vec4 vs_color;
in vec2 vs_texcoord;

uniform vec3 u_light_pos;  // light position in eye space
uniform mat4 u_view_mat;    // transform world space to eye space
uniform mat4 u_model_mat;    // transform world space to eye space

uniform vec4 u_la;
uniform vec4 u_ls;
uniform vec4 u_ld;

uniform vec4 u_ks;
uniform vec4 u_kd;
uniform vec4 u_ka;

uniform float u_specular_power; // specular shininess

out vec4 fs_color;  // fragment color

void main ()
{
    /** incident light direction in eye space */
    vec3 incident_light_direction = normalize( vec3( u_view_mat * u_model_mat * vec4( u_light_pos, 1.f ) ) );
    /** position direction in eye space */
    vec3 position_direction = normalize( vs_position );
    /** normal direction in eye space */
    vec3 normal_direction = normalize( vs_normal );
    /** reflected light direction in eye space */
    vec3 reflected_light_direction = reflect( -incident_light_direction, normal_direction );
    
    /** ambient irradiance */
    vec4 ia = u_ka * u_la;
    
    /** diffuse irradiance kd = vs_color */
    vec4 id = u_kd * max( 0.f, dot( normal_direction, incident_light_direction ) );
//
//    /** specular irradiance */
    vec4 is = u_ks * pow( max( 0.f, dot( reflected_light_direction, position_direction ) ),
                       u_specular_power );
    
    fs_color = ia + id + is;
}