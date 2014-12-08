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

#include "antPlane.h"
#include "antShader.h"
#include "antGui.h"
#include "antCamera.h"
#include "antMesh.h"
#include "antAxis.h"
#include "antSkybox.h"
#include "antPointLight.h"
#include "antSphere.h"

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
    
    private :
    
    antRGBA m_background_color;
    
    GLuint m_simple_shader;
    GLuint m_skybox_shader;
    GLuint m_light_shader;
    
    antPlaneShPtr m_plane_shptr;
    
    antCameraShPtr m_camera_shptr;
    
    antMeshShPtr m_mesh_shptr;
    antAxisShPtr m_axis_shptr;

    antSkyboxShPtr m_skybox_shptr;

    antPointLightShPtr m_light_shptr;
    antSphereShPtr m_light_sphere_shptr;
    
    bool m_plane_type;
    antVec4 m_plane_tw_rotation;
    antVec3 m_plane_position;
    
    bool m_camera_type;
    antVec4 m_camera_tw_rotation;
    antVec3 m_camera_position;
    
    bool m_mesh_type;
    antVec4 m_mesh_tw_rotation;
    antVec3 m_mesh_position;
    
    antVec3 m_light_position;
    
    antGuiShPtr m_gui_shptr;
    
    antApp( int window_width, int window_height, const std::string & window_title );
    antAppWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antApp__) */
