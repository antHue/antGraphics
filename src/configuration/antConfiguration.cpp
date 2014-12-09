//
//  antConfiguration.cpp
//  _xcodeproj
//
//  Created by anthonycouret on 09/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antConfiguration.h"
#include "antMapableConfiguration.h"

antConfigurationShPtr antConfiguration::create( antRotationType type )
{
    antConfigurationShPtr antConfiguration_sh_ptr( new antConfiguration( type ) );
    antConfiguration_sh_ptr->m_weak_ptr = antConfiguration_sh_ptr;
    return antConfiguration_sh_ptr;
}

antConfiguration::antConfiguration( antRotationType type ) :
antAbstractConfiguration()
{
    m_type = type;
    m_position = antVec3( 0.f, 0.f, 0.f );
    m_rotation = quat_from_axis_rad( 1.f, 0.f, 0.f, 0.f );
    m_scale = 1.f;
}

antConfiguration::~antConfiguration() {}

void antConfiguration::setPosition( antVec3 position )
{
    m_position = position;
}

void antConfiguration::setRotation( antQuat rotation )
{
    m_rotation = rotation;
}

void antConfiguration::setScale( float scale )
{
    m_scale = scale;
}

void antConfiguration::setType( antRotationType type )
{
    m_type = type;
}

antVec3 antConfiguration::getPosition()
{
    return m_position;
}

antQuat antConfiguration::getRotation()
{
    return m_rotation;
}

antMat4 antConfiguration::getLocalToWorldMatrix()
{
    antMat4 translation_mat = translate( identity_mat4() , m_position );
    antMat4 rotation_mat = quat_to_mat4( normalise( m_rotation ) );
    
    mat4 local_to_world_matrix;
    
    switch ( m_type )
    {
        case SELF : local_to_world_matrix = scale( translation_mat * rotation_mat,
                                                  antVec3( m_scale, m_scale, m_scale ) );
            break;
        case ORBIT : local_to_world_matrix = scale( rotation_mat * translation_mat,
                                                   antVec3( m_scale, m_scale, m_scale ) );
            break;
    }
    
    return local_to_world_matrix;
}

antMat4 antConfiguration::getWorldToOriginMatrix()
{
    antMat4 inv_translation_mat =
    translate( identity_mat4(), antVec3( -m_position.v[0], -m_position.v[1], -m_position.v[2] )  );
    
    antQuat inv_rotation;
    inv_rotation.q[0] = -m_rotation.q[0];
    inv_rotation.q[1] = m_rotation.q[1];
    inv_rotation.q[2] = m_rotation.q[2];
    inv_rotation.q[3] = m_rotation.q[3];
    
    antMat4 inv_rotation_mat = quat_to_mat4( normalise( inv_rotation ) );
    
    mat4 world_to_origin_matrix;
    
    switch ( m_type )
    {
        case SELF : world_to_origin_matrix = scale( inv_translation_mat * inv_rotation_mat,
                                                   antVec3( m_scale, m_scale, m_scale ) );
            break;
        case ORBIT : world_to_origin_matrix = scale( inv_rotation_mat * inv_translation_mat,
                                                    antVec3(m_scale, m_scale, m_scale) );
            break;
    }
    return world_to_origin_matrix;
}


antAbstractConfigurationShPtr antConfiguration::makeMapable()
{
    antAbstractConfigurationShPtr m = antMapableConfiguration::create();
    m->setPosition( m_position );
    m->setRotation( m_rotation );
    m->setType( m_type );
    m->setScale( m_scale );
    return m;
}
