//
//  antCamera.cpp
//  ant_graphics
//
//  Created by anthonycouret on 22/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antCamera.h"

antCameraShPtr antCamera::create()
{
    antCameraShPtr camera_sh_ptr( new antCamera() );
    camera_sh_ptr->m_weak_ptr = camera_sh_ptr;
    return camera_sh_ptr;
}

antCamera::antCamera()
{
    m_world_configuration = antConfiguration::create();

    m_near = 0.1f;
    m_far = 100.f;
    m_fov = 67.f * ONE_DEG_IN_RAD;
    m_aspect_ratio = 800.f / 600.f;
}

mat4 antCamera::getViewMatrix()
{
    return m_world_configuration->getWorldToOriginMatrix();
}

mat4 antCamera::getProjMatrix()
{
    float range = tan( m_fov * 0.5f ) * m_near;
    float sx = ( 2.f * m_near ) / ( range * m_aspect_ratio + range * m_aspect_ratio );
    float sy = m_near / range;
    float sz = -( m_far + m_near ) / (m_far - m_near );
    float pz = -( 2.f * m_far * m_near ) / ( m_far - m_near );
    
    mat4 proj_mat = mat4( sx, 0.f, 0.f, 0.f,
                         0.f, sy, 0.f, 0.f,
                         0.f, 0.f, sz, -1.f,
                         0.f, 0.f, pz, 0.f   );
    return proj_mat;
}

//void antCamera::setPosition( antVec3 position )
//{
//    m_world_configuration->setPosition( position );
//}
//
//void antCamera::makeMapableConfiguration()
//{
//    m_world_configuration = std::dynamic_pointer_cast<antConfiguration>( m_world_configuration )->makeMapable();
//}
//
//antMapableVec3 antCamera::getMapablePosition()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapablePosition();
//}
//
//antMapableQuat antCamera::getMapableRotation()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapableRotation();
//}
//
//antMapableVec4 antCamera::getMapableTwRotation()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapableTwRotation();
//}
//
//antMapableFloat antCamera::getMapableScale()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapableScale();
//}
//
//antMapableRotType antCamera::getMapableRotType()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapableRotType();
//}
//
//void antCamera::setRotation( antQuat rotation )
//{
//    m_world_configuration->setRotation( rotation );
//}
//
//void antCamera::setConfigType( bool type )
//{
//    m_world_configuration->setType( type ? ORBIT : SELF );
//};

antCamera::~antCamera()
{
    m_weak_ptr.reset();
}

