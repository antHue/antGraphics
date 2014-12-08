//
//  antCamera.h
//  ant_graphics
//
//  Created by anthonycouret on 22/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antCamera__
#define __ant_graphics__antCamera__

#include <iostream>

#include <memory>
#include "maths_funcs.h"
#include <math.h>
#include "antTypes.h"
#include "antConfiguration.h"

class antCamera;
typedef std::shared_ptr<antCamera> antCameraShPtr;
typedef std::weak_ptr<antCamera> antCameraWkPtr;

typedef enum { FPS = 0, LOOKAT = 1 } antCameraType;

class antCamera
{
    public :
    
    mat4 getViewMatrix();
    mat4 getProjMatrix();
    
    void setPosition( antVec3 position );
    void setRotation( antQuat rotation );
    void setConfigType( bool type );

    static antCameraShPtr create();
    ~antCamera();

    private :
    
    /** \brief near clipping plane */
    float m_near;
    
    /** \brief far clipping plane */
    float m_far;
    
    /** \brief field of view */
    float m_fov;
    
    /** \brief aspect ratio */
    float m_aspect_ratio;
    
    antConfigurationShPtr m_world_configuration;

    antCamera();
    antCameraWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antCamera__) */
