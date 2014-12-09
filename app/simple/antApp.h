//
//  antApp.h
//  ant_graphics
//
//  Created by anthonycouret on 07/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antApp__
#define __ant_graphics__antApp__

#include <memory>
#include <iostream>

#include "antWindow.h"
#include "antTypes.h"
#include "antAbstractApp.h"

#include "antShader.h"
#include "antGui.h"
#include "antCamera.h"
#include "antMesh.h"
#include "antSkybox.h"
#include "antPointLight.h"
#include "antSphere.h"
#include "antMapableMaterial.h"
#include "antMaterialDef.h"

#include "antMapableConfiguration.h"
#include "antConfiguration.h"

class antApp;
typedef std::shared_ptr<antApp> antAppShPtr;
typedef std::weak_ptr<antApp> antAppWkPtr;

class antApp : public antAbstractApp
{
    public :
    
    static antAppShPtr create
        ( int window_width, int window_height, const std::string & window_title );
    
    ~antApp();
    
    virtual void start();
    virtual void update();
    virtual void draw();
    virtual void shutdown();
    
    void makeGui();
    
    private :
    
    antRGBA m_background_color;
    
    //-- SPHERES ---------------------------------------------------------------
    antSphereShPtr m_sphere_shptr;
    antMapableMaterialShPtr m_sphere_material;
    
    //-- SHADERS ---------------------------------------------------------------
    GLuint m_phong_shader;
    GLuint m_light_shader;
    
    //-- CAMERA ----------------------------------------------------------------
    antCameraShPtr m_camera_shptr;    
    
    //-- LIGHT -----------------------------------------------------------------
    antSphereShPtr m_light_sphere_shptr;
    antMapableMaterialShPtr m_light_material;
    antVec3 m_light_pos;

    //-- GUI  ------------------------------------------------------------------
    antGuiShPtr m_gui_shptr;
    
    antApp( int window_width, int window_height, const std::string & window_title );
    antAppWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antApp__) */
