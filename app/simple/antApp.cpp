//
//  antApp.cpp
//  ant_graphics
//
//  Created by anthonycouret on 07/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antApp.h"

int main(int argc, const char * argv[])
{
    antAppShPtr ant_app_shptr = antApp::create( 800, 600, "🐜" );
    return 0;
}


antAppShPtr antApp::create
( int window_width, int window_height, const std::string & window_title )
{
    antAppShPtr antApp_sh_ptr
        ( new antApp( window_width, window_height, window_title ) );    
    antApp_sh_ptr->m_weak_ptr = antApp_sh_ptr;
    return antApp_sh_ptr;
}

antApp::antApp
( int window_width, int window_height, const std::string & window_title ) :
antAbstractApp( window_width, window_height, window_title )
{
    this->run();
}

antApp::~antApp()
{
    m_weak_ptr.reset();
}

//------------------------------------------------------------------------------
//------------------ START -----------------------------------------------------
//------------------------------------------------------------------------------

void antApp::start()
{
    m_background_color = antRGBA( 1.f, 0.5f, 0.2f, 1.f );
    
    m_plane_type = false;
    m_plane_position = antVec3( 0.f, 0.f, 0.f );
    m_plane_tw_rotation = antQuat_to_TwQuat( quat_from_axis_rad( 1.f, 0.f, 0.f, 0.f ) );
    
    m_camera_type = false;
    m_camera_position = antVec3( 0.f, 0.f, 1.f );
    m_camera_tw_rotation = antQuat_to_TwQuat( quat_from_axis_rad( 1.f, 0.f, 0.f, 0.f ) );
    
    m_mesh_type = false;
    m_mesh_position = antVec3( 0.f, 0.f, 0.f );
    m_mesh_tw_rotation = antQuat_to_TwQuat( quat_from_axis_rad( 1.f, 0.f, 0.f, 0.f ) );

    m_light_position = antVec3( 0.f, 0.f, 0.f );
    
    m_plane_shptr = antPlane::create( 1.f, 1.f, 10, 10, 2, true, false , false );
    
    m_axis_shptr = antAxis::create( 2, true );
    
    m_camera_shptr = antCamera::create();
    
    m_mesh_shptr = antMesh::createFromObjFile
    ( "/Users/anthonycouret/Developer/antGraphics/_models/roc.obj" );
    m_mesh_shptr->setScale( 0.01f );
    
    m_skybox_shptr = antSkybox::create( "/Users/anthonycouret/Developer/antGraphics/_textures/tree/" );
    m_skybox_shptr->setScale( 40.f );
    
    m_light_shptr = antPointLight::create( m_light_position );
    m_light_sphere_shptr = antSphere::create();
    m_light_sphere_shptr->setPosition( m_light_position );
    m_light_sphere_shptr->setScale( 0.01f );

    
    m_gui_shptr = antGui::create( m_window_shptr );
//    int bar_id = m_gui_shptr->addBar( "planeconfig" );
//    m_gui_shptr->addQuatVarRW( bar_id, "rotation", &m_plane_tw_rotation );
//    m_gui_shptr->addVec3VarRW( bar_id, "position", &m_plane_position );
//    m_gui_shptr->addToggleRW( bar_id, "type", &m_plane_type );
    
    int bar_id2 = m_gui_shptr->addBar( "cameraconfig" );
    m_gui_shptr->addQuatVarRW( bar_id2, "rotation", &m_camera_tw_rotation );
    m_gui_shptr->addVec3VarRW( bar_id2, "position", &m_camera_position );
    m_gui_shptr->addToggleRW( bar_id2, "type", &m_camera_type );
    
    int bar_id3 = m_gui_shptr->addBar( "meshconfig" );
    m_gui_shptr->addQuatVarRW( bar_id3, "rotation", &m_mesh_tw_rotation );
    m_gui_shptr->addVec3VarRW( bar_id3, "position", &m_mesh_position );
    m_gui_shptr->addToggleRW( bar_id3, "type", &m_mesh_type );
    
    int bar_id4 = m_gui_shptr->addBar( "lightconfig" );
    m_gui_shptr->addVec3VarRW( bar_id4, "position", &m_light_position );
    
    std::string light_vs =
    "/Users/anthonycouret/Developer/ant_graphics/ant_graphics/_shaders/simple_shaders/simple.vert";
    std::string light_fs =
    "/Users/anthonycouret/Developer/ant_graphics/ant_graphics/_shaders/simple_shaders/simple.frag";
    m_light_shader = antShader::createShaderProgram( light_vs, light_fs );
    
    std::string simple_vs =
    "/Users/anthonycouret/Developer/ant_graphics/ant_graphics/_shaders/phong_shaders/phong.vert";
    std::string simple_geom =
    "/Users/anthonycouret/Developer/ant_graphics/ant_graphics/_shaders/phong_shaders/phong.geom";
    std::string simple_fs =
    "/Users/anthonycouret/Developer/ant_graphics/ant_graphics/_shaders/phong_shaders/phong.frag";
    m_simple_shader = antShader::createShaderProgram( simple_vs, simple_fs );
    
    std::string skybox_vs =
    "/Users/anthonycouret/Developer/ant_graphics/ant_graphics/_shaders/skybox_shaders/skybox.vert";
    std::string skybox_fs =
    "/Users/anthonycouret/Developer/ant_graphics/ant_graphics/_shaders/skybox_shaders/skybox.frag";
    m_skybox_shader = antShader::createShaderProgram( skybox_vs, skybox_fs );
}


//------------------------------------------------------------------------------
//------------------ RENDER LOOP -----------------------------------------------
//------------------------------------------------------------------------------

void antApp::update()
{
    m_plane_shptr->setPosition( m_plane_position );
    m_plane_shptr->setRotation( TwQuat_to_antQuat( m_plane_tw_rotation ) );
    m_plane_shptr->setConfigType( m_plane_type );
    
    m_camera_shptr->setPosition( m_camera_position );
    m_camera_shptr->setRotation( TwQuat_to_antQuat( m_camera_tw_rotation ) );
    m_camera_shptr->setConfigType( m_camera_type );
    
    m_mesh_shptr->setPosition( m_mesh_position );
    m_mesh_shptr->setRotation( TwQuat_to_antQuat( m_mesh_tw_rotation ) );
    m_mesh_shptr->setConfigType( m_mesh_type );
    
    m_light_shptr->setPosition( m_light_position );
    m_light_sphere_shptr->setPosition( m_light_position );
}

void antApp::draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearBufferfv( GL_COLOR, 0, m_background_color.v );
    
    glActiveTexture( GL_TEXTURE0 );
    
    
    glUseProgram( m_light_shader );
    
    glUniformMatrix4fv( glGetUniformLocation( m_light_shader, "u_view_mat" ),
                       1, GL_FALSE, m_camera_shptr->getViewMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_light_shader, "u_proj_mat" ),
                       1, GL_FALSE, m_camera_shptr->getProjMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_light_shader, "u_model_mat" ),
                       1, GL_FALSE, m_light_sphere_shptr->getModelMatrix().m );
    

    m_light_sphere_shptr->draw( GL_TRIANGLES );
    
    glUseProgram( m_simple_shader );
    
//    glUniformMatrix4fv( glGetUniformLocation( m_simple_shader, "u_model_mat" ),
//                       1, GL_FALSE, m_plane_shptr->getModelMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_simple_shader, "u_view_mat" ),
                       1, GL_FALSE, m_camera_shptr->getViewMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_simple_shader, "u_proj_mat" ),
                       1, GL_FALSE, m_camera_shptr->getProjMatrix().m );
    
    //m_plane_shptr->draw();
    
    
    glUniformMatrix4fv( glGetUniformLocation( m_simple_shader, "u_model_mat" ),
                       1, GL_FALSE, m_mesh_shptr->getModelMatrix().m );
    
    glUniform3fv( glGetUniformLocation( m_simple_shader, "u_point_light_pos"), 1,
                 m_light_shptr->getPosition().v );
    
    glUniform4fv( glGetUniformLocation( m_simple_shader, "u_ls"), 1,
                 m_light_shptr->getSpecularColor().v );
    
    glUniform1i ( glGetUniformLocation( m_simple_shader, "u_env_tex" ), 0);

    
    glUniform1f( glGetUniformLocation( m_simple_shader, "u_specular_power"), 5.f );
    
//    glUniform1f( glGetUniformLocation( m_simple_shader, "u_rot" ), cosf(getCurrentTime()) );
//    glUniform1f( glGetUniformLocation( m_simple_shader, "u_x_axis" ), -cosf(getCurrentTime()) );
//    glUniform1f( glGetUniformLocation( m_simple_shader, "u_y_axis" ), -sinf(getCurrentTime()) );
//    glUniform1f( glGetUniformLocation( m_simple_shader, "u_z_axis" ), sinf(getCurrentTime()) );
//    
//    glUniform1f( glGetUniformLocation( m_simple_shader, "u_z_axis" ), sinf(getCurrentTime()) );

    
    m_mesh_shptr->draw( GL_TRIANGLES );
    //m_axis_shptr->draw();
    
    glUseProgram( m_skybox_shader );
    
    glUniform1i ( glGetUniformLocation( m_skybox_shader, "u_texture" ), 0);
    
    glUniformMatrix4fv( glGetUniformLocation( m_skybox_shader, "u_model_mat" ),
                       1, GL_FALSE, m_skybox_shptr->getModelMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_skybox_shader, "u_view_mat" ),
                       1, GL_FALSE, m_camera_shptr->getViewMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_skybox_shader, "u_proj_mat" ),
                       1, GL_FALSE, m_camera_shptr->getProjMatrix().m );
    
    m_skybox_shptr->draw();
    
    
    m_gui_shptr->draw();
}

//------------------------------------------------------------------------------
//------------------ SHUTDOWN --------------------------------------------------
//------------------------------------------------------------------------------

void antApp::shutdown() {}
