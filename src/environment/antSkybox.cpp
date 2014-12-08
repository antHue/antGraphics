//
//  antSkybox.cpp
//  ant_graphics
//
//  Created by anthonycouret on 24/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antSkybox.h"

antSkyboxShPtr antSkybox::create( const std::string & tex_dir )
{
    antSkyboxShPtr antSkybox_sh_ptr( new antSkybox( tex_dir ) );
    antSkybox_sh_ptr->m_weak_ptr = antSkybox_sh_ptr;
    
    return antSkybox_sh_ptr;
}

antSkybox::antSkybox( const std::string & tex_dir ) :
antCube( 1, false, false, false )
{
    
    m_front_tex = antTexture::create(); m_front_tex->loadTextureFromFile( tex_dir + "posz.jpg");
    m_back_tex = antTexture::create(); m_back_tex->loadTextureFromFile( tex_dir + "negz.jpg");
    
    m_left_tex = antTexture::create(); m_left_tex->loadTextureFromFile( tex_dir + "negx.jpg");
    m_right_tex = antTexture::create(); m_right_tex->loadTextureFromFile( tex_dir + "posx.jpg");

    m_top_tex = antTexture::create(); m_top_tex->loadTextureFromFile( tex_dir + "posy.jpg");
    m_bottom_tex = antTexture::create(); m_bottom_tex->loadTextureFromFile( tex_dir + "negy.jpg");
    
    
//    m_front_norm = antTexture::create(); m_front_norm->loadTextureFromFile( tex_dir + "normals/posz.jpg");
//    m_back_norm = antTexture::create(); m_back_norm->loadTextureFromFile( tex_dir + "normals/negz.jpg");
//    
//    m_left_norm = antTexture::create(); m_left_norm->loadTextureFromFile( tex_dir + "normals/negx.jpg");
//    m_right_norm = antTexture::create(); m_right_norm->loadTextureFromFile( tex_dir + "normals/posx.jpg");
//    
//    m_top_norm = antTexture::create(); m_top_norm->loadTextureFromFile( tex_dir + "normals/posy.jpg");
//    m_bottom_norm = antTexture::create(); m_bottom_norm->loadTextureFromFile( tex_dir + "normals/negy.jpg");
   
    glActiveTexture( GL_TEXTURE0 );
    glGenTextures( 1, &m_textures );

    for ( int i = SKYBOX_FRONT; i <= SKYBOX_BOTTOM; i++ )
    {
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_textures );
        
        glTexImage2D( getGLCubeMapTexture( i ), 0, GL_RGBA,
                     getFaceTexture( i )->getWidth(), getFaceTexture( i )->getHeight(),
                     0, GL_RGBA, GL_UNSIGNED_BYTE, getFaceTexture( i )->getData() );
    }
    
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    
    
    m_front_tex.reset();
    m_back_tex.reset();
    m_left_tex.reset();
    m_bottom_tex.reset();
    
//    glActiveTexture( GL_TEXTURE1 );
//    glGenTextures( 1, &m_tex_normals );
//    
//    for ( int i = SKYBOX_FRONT; i <= SKYBOX_BOTTOM; i++ )
//    {
//        glBindTexture( GL_TEXTURE_CUBE_MAP, m_tex_normals );
//        
//        glTexImage2D( getGLCubeMapTexture( i ), 0, GL_RGBA,
//                     getFaceNormalTex( i )->getWidth(), getFaceNormalTex( i )->getHeight(),
//                     0, GL_RGBA, GL_UNSIGNED_BYTE, getFaceNormalTex( i )->getData() );
//
//
//    }
//    
//    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
//    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
//    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
//    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
}


antTextureShPtr antSkybox::getFaceTexture( int face )
{
    switch ( face )
    {
        case SKYBOX_FRONT : return m_front_tex; break;
        case SKYBOX_BACK : return m_back_tex; break;
        case SKYBOX_LEFT : return m_left_tex; break;
        case SKYBOX_RIGHT : return m_right_tex; break;
        case SKYBOX_TOP: return m_top_tex; break;
        case SKYBOX_BOTTOM : return m_bottom_tex; break;
            
        default:
            break;
    }
//    return NULL;
}

antTextureShPtr antSkybox::getFaceNormalTex( int face )
{
    switch ( face )
    {
        case SKYBOX_FRONT : return m_front_norm; break;
        case SKYBOX_BACK : return m_back_norm; break;
        case SKYBOX_LEFT : return m_left_norm; break;
        case SKYBOX_RIGHT : return m_right_norm; break;
        case SKYBOX_TOP: return m_top_norm; break;
        case SKYBOX_BOTTOM : return m_bottom_norm; break;
            
        default:
            break;
    }
//    return NULL;
}

GLenum antSkybox::getGLCubeMapTexture( int face )
{
    switch ( face )
    {
        case SKYBOX_FRONT : return GL_TEXTURE_CUBE_MAP_POSITIVE_Z; break;
        case SKYBOX_BACK : return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
        case SKYBOX_LEFT : return GL_TEXTURE_CUBE_MAP_NEGATIVE_X; break;
        case SKYBOX_RIGHT : return GL_TEXTURE_CUBE_MAP_POSITIVE_X; break;
        case SKYBOX_TOP: return GL_TEXTURE_CUBE_MAP_POSITIVE_Y; break;
        case SKYBOX_BOTTOM : return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
            
        default:
            break;
    }
//    return NULL;
}


antSkybox::~antSkybox()
{
    m_weak_ptr.reset();
}