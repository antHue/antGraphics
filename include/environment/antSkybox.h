//
//  antSkybox.h
//  ant_graphics
//
//  Created by anthonycouret on 24/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antSkybox__
#define __ant_graphics__antSkybox__

#include <memory>
#include <vector>
#include <math.h>
#include <cassert>

#include "antMacros.h"
#include "antCube.h"
#include "antVbo.h"
#include "antTexture.h"
#include "antShader.h"

#include <OpenGL/gl3.h>

class antSkybox;
typedef std::shared_ptr<antSkybox> antSkyboxShPtr;
typedef std::weak_ptr<antSkybox> antSkyboxWkPtr;

typedef enum {  SKYBOX_FRONT = 0, SKYBOX_BACK = 1,
                SKYBOX_LEFT = 2, SKYBOX_RIGHT = 3,
                SKYBOX_TOP = 4, SKYBOX_BOTTOM = 5
            } SKYBOX_FACE;

class antSkybox : public antCube
{
    public :
    
    static antSkyboxShPtr create( const std::string & tex_dir );
    ~antSkybox();
        
    GLuint getTextures() { return m_textures; }
        
    private :
    
    GLuint m_textures;
    antTextureShPtr m_front_tex;
    antTextureShPtr m_back_tex;
    antTextureShPtr m_left_tex;
    antTextureShPtr m_right_tex;
    antTextureShPtr m_top_tex;
    antTextureShPtr m_bottom_tex;
    
    GLuint m_tex_normals;
    antTextureShPtr m_front_norm;
    antTextureShPtr m_back_norm;
    antTextureShPtr m_left_norm;
    antTextureShPtr m_right_norm;
    antTextureShPtr m_top_norm;
    antTextureShPtr m_bottom_norm;

    float map( float v, float in_min, float in_max, float out_min, float out_max )
    {
        return out_min + (out_max - out_min ) * ( ( v - in_min ) / ( in_max - in_min ) );
    }
        
    antTextureShPtr getFaceTexture( int face );
    antTextureShPtr getFaceNormalTex( int face );

    GLenum getGLCubeMapTexture( int face );
    
    antSkybox( const std::string & tex_dir );
    antSkyboxWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antSkybox__) */
