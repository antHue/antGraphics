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
    m_background_color = antRGBA( 0.18f, 0.42f, 0.655f, 1.f );
    
    //-- SPHERE ----------------------------------------------------------------
    m_sphere_shptr = antSphere::create();
    m_sphere_shptr->makeMapableConfiguration();
    m_sphere_material = antMapableMaterial::create
        ( JADE_SPECULAR, JADE_DIFFUSE, JADE_AMBIENT, JADE_SHININESS );
    
    //-- CAMERA ----------------------------------------------------------------
    m_camera_shptr = antCamera::create();
    
    m_camera_shptr->makeMapableConfiguration();
    m_camera_shptr->setPosition( antVec3( 0.f, 0.f, 10.f ) );
    m_camera_shptr->setRotation( quat_from_axis_rad( 1.f, 0.f, 0.f, 0.f ) );
    m_camera_shptr->setConfigType( false );

    //-- LIGHT -----------------------------------------------------------------
    m_light_sphere_shptr = antSphere::create();
    
    m_light_sphere_shptr->makeMapableConfiguration();
    m_light_sphere_shptr->setPosition( antVec3( 0.f, 0.f, 5.f ) );
    m_light_sphere_shptr->setRotation( quat_from_axis_rad( 1.f, 0.f, 0.f, 0.f ) );
    m_light_sphere_shptr->setConfigType( false );

    m_light_material =
    antMapableMaterial::create( LIGHT_SPECULAR, LIGHT_DIFFUSE, m_background_color, LIGHT_SHININESS );
    
    //-- SHADER  ------------------------------------------------------------------
    std::string phong_vs =
    "/Users/anthonycouret/Developer/antGraphics/_shaders/superbible_shaders/phong/phong.vert";
    std::string phong_fs =
    "/Users/anthonycouret/Developer/antGraphics/_shaders/superbible_shaders/phong/phong.frag";
    m_phong_shader = antShader::createShaderProgram( phong_vs, phong_fs );
    
    std::string light_vs =
    "/Users/anthonycouret/Developer/antGraphics/_shaders/light_shaders/simple/simple_light.vert";
    std::string light_fs =
    "/Users/anthonycouret/Developer/antGraphics/_shaders/light_shaders/simple/simple_light.frag";
    m_light_shader = antShader::createShaderProgram( light_vs, light_fs );
    
    makeGui();
}


//------------------------------------------------------------------------------
//------------------ RENDER LOOP -----------------------------------------------
//------------------------------------------------------------------------------

void antApp::update()
{
    antVec4 l = m_light_sphere_shptr->getModelMatrix() * antVec4(0.f, 0.f, 0.f, 1.f);
    m_light_pos = antVec3( l.v[0], l.v[1], l.v[2] );
    
    m_camera_shptr->getMapablePosition()->v[0] = sinf( getCurrentTime() );
}

void antApp::draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearBufferfv( GL_COLOR, 0, m_background_color.v );
    
    //-- LIGHT -----------------------------------------------------------------
    glUseProgram( m_light_shader );
    
    glUniformMatrix4fv( glGetUniformLocation( m_light_shader, "u_view_mat" ),
                       1, GL_FALSE, m_camera_shptr->getViewMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_light_shader, "u_proj_mat" ),
                       1, GL_FALSE, m_camera_shptr->getProjMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_light_shader, "u_model_mat" ),
                       1, GL_FALSE, m_light_sphere_shptr->getModelMatrix().m );
    

    m_light_sphere_shptr->draw( GL_TRIANGLES );
    
    
    //-- SPHERES ---------------------------------------------------------------
    glUseProgram( m_phong_shader );
    
    glUniformMatrix4fv( glGetUniformLocation( m_phong_shader, "u_view_mat" ),
                       1, GL_FALSE, m_camera_shptr->getViewMatrix().m );
    
    glUniformMatrix4fv( glGetUniformLocation( m_phong_shader, "u_proj_mat" ),
                       1, GL_FALSE, m_camera_shptr->getProjMatrix().m );
    


    glUniform3fv( glGetUniformLocation( m_phong_shader, "u_light_pos" ), 1,
                 m_light_pos.v );
    
    glUniform4fv( glGetUniformLocation( m_phong_shader, "u_la" ), 1,
                 m_light_material->getAmbientReflectance()->v );
    
    glUniform4fv( glGetUniformLocation( m_phong_shader, "u_ls" ), 1,
                 m_light_material->getSpecularReflectance()->v );
    
    glUniform4fv( glGetUniformLocation( m_phong_shader, "u_ld" ), 1,
                 m_light_material->getDiffuseReflectance()->v );
    
    glUniform4fv( glGetUniformLocation( m_phong_shader, "u_ks" ), 1,
                 /*m_ks.v*/
                 m_sphere_material->getSpecularReflectance()->v );
    
    glUniform4fv( glGetUniformLocation( m_phong_shader, "u_ka" ), 1,
                 m_sphere_material->getAmbientReflectance()->v  );
    
    glUniform4fv( glGetUniformLocation( m_phong_shader, "u_kd" ), 1,
                 m_sphere_material->getDiffuseReflectance()->v  );
    
    glUniform1f( glGetUniformLocation( m_phong_shader, "u_specular_power" ),
                *(m_sphere_material->getSpecularPower().get()) );
    
    for ( int i = -2 ; i <= 2; i ++)
    {
        for ( int j = -2; j <= 2; j ++)
        {
            m_sphere_shptr->setPosition( antVec3( i * 2, j * 2, 0.f ) );
            glUniformMatrix4fv( glGetUniformLocation( m_phong_shader, "u_model_mat" ),
                               1, GL_FALSE, m_sphere_shptr->getModelMatrix().m );
            m_sphere_shptr->draw( GL_TRIANGLES );
            
        }
    }
    
    m_gui_shptr->draw();
}

//------------------------------------------------------------------------------
//------------------ SHUTDOWN --------------------------------------------------
//------------------------------------------------------------------------------

void antApp::shutdown() {}




void antApp::makeGui()
{
    //-- GUI  ------------------------------------------------------------------
    m_gui_shptr = antGui::create( m_window_shptr );
    
    int bar_id1 = m_gui_shptr->addBar( "spheresconfig" );
    m_gui_shptr->addRGBAVarRW( bar_id1, "specular", m_sphere_material->getSpecularReflectance().get() );
    m_gui_shptr->addRGBAVarRW( bar_id1, "diffuse", m_sphere_material->getDiffuseReflectance().get() );
    m_gui_shptr->addRGBAVarRW( bar_id1, "ambient", m_sphere_material->getAmbientReflectance().get() );
    m_gui_shptr->addFloatVarRW( bar_id1, "specpower", m_sphere_material->getSpecularPower().get() );
    m_gui_shptr->addVec3VarRW( bar_id1, "position", m_sphere_shptr->getMapablePosition().get() );
    m_gui_shptr->addQuatVarRW( bar_id1, "rotation", m_sphere_shptr->getMapableTwRotation().get() );
    m_gui_shptr->addFloatVarRW( bar_id1, "scale", m_sphere_shptr->getMapableScale().get() );

    
    int bar_id2 = m_gui_shptr->addBar( "cameraconfig" );
    m_gui_shptr->addVec3VarRW( bar_id2, "position", m_camera_shptr->getMapablePosition().get() );
    m_gui_shptr->addQuatVarRW( bar_id2, "rotation", m_camera_shptr->getMapableTwRotation().get() );
    //m_gui_shptr->addRotTypeRW( bar_id2, "type", m_camera_shptr->getMapableRotType().get() );
    //m_gui_shptr->addFloatVarRW( bar_id2, "scale", m_camera_shptr->getMapableScale().get() );

    
    int bar_id4 = m_gui_shptr->addBar( "lightconfig" );
    m_gui_shptr->addVec3VarRW( bar_id4, "position", m_light_sphere_shptr->getMapablePosition().get() );
    m_gui_shptr->addQuatVarRW( bar_id4, "rotation", m_light_sphere_shptr->getMapableTwRotation().get() );
    //m_gui_shptr->addRotTypeRW( bar_id2, "type", m_camera_shptr->getMapableRotType().get() );
    m_gui_shptr->addFloatVarRW( bar_id4, "scale", m_light_sphere_shptr->getMapableScale().get() );
    
    m_gui_shptr->addRGBAVarRW( bar_id4, "specular", m_light_material->getSpecularReflectance().get() );
    m_gui_shptr->addRGBAVarRW( bar_id4, "diffuse", m_light_material->getDiffuseReflectance().get() );
    m_gui_shptr->addRGBAVarRW( bar_id4, "ambient", m_light_material->getAmbientReflectance().get() );
}
