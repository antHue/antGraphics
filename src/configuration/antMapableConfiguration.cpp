//
//  antMapableConfiguration.cpp
//  _xcodeproj
//
//  Created by anthonycouret on 09/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antMapableConfiguration.h"
#include "antConfiguration.h"

antMapableConfigurationShPtr antMapableConfiguration::create( antRotationType type )
{
    antMapableConfigurationShPtr antConfiguration_sh_ptr( new antMapableConfiguration( type ) );
    antConfiguration_sh_ptr->m_weak_ptr = antConfiguration_sh_ptr;
    return antConfiguration_sh_ptr;
}

antMapableConfiguration::antMapableConfiguration( antRotationType type ) :
antAbstractConfiguration()
{
    m_position = antMapableVec3( new antVec3( 0.f, 0.f, 0.f ) );
    m_rotation = antMapableQuat( new antQuat( quat_from_axis_rad( 1.f, 0.f, 0.f, 0.f ) ) );
    
    m_tw_rotation = antMapableVec4
    ( new antVec4( m_rotation->q[3], m_rotation->q[0], m_rotation->q[1], m_rotation->q[2]) );
    
    m_type = antMapableRotType( new antRotationType(type) );
    m_scale = antMapableFloat( new float(1.f) );
}

antMapableConfiguration::~antMapableConfiguration(){}

void antMapableConfiguration::setPosition( antVec3 position )
{
    m_position->v[0] = position.v[0];
    m_position->v[1] = position.v[1];
    m_position->v[2] = position.v[2];
}

void antMapableConfiguration::setRotation( antQuat rotation )
{
    m_rotation->q[0] = m_rotation->q[0];
    m_rotation->q[1] = m_rotation->q[1];
    m_rotation->q[2] = m_rotation->q[2];
    m_rotation->q[3] = m_rotation->q[3];
    
    m_tw_rotation->v[0] = m_rotation->q[1];
    m_tw_rotation->v[1] = m_rotation->q[2];
    m_tw_rotation->v[2] = m_rotation->q[3];
    m_tw_rotation->v[3] = m_rotation->q[0];
}

void antMapableConfiguration::setScale( float scale )
{
    *(m_scale.get()) = scale;
}

void antMapableConfiguration::setType( antRotationType type )
{
    *(m_type.get()) = type;
}

antMapableVec3 antMapableConfiguration::getMapablePosition()
{
    return m_position;
}

antMapableQuat antMapableConfiguration::getMapableRotation()
{
    return m_rotation;
}

antMapableVec4 antMapableConfiguration::getMapableTwRotation()
{
    return m_tw_rotation;
}

antMapableFloat antMapableConfiguration::getMapableScale()
{
    return m_scale;
}

antMapableRotType antMapableConfiguration::getMapableRotType()
{
    return m_type;
}

antAbstractConfigurationShPtr antMapableConfiguration::makeBase()
{
    antAbstractConfigurationShPtr map = antConfiguration::create();
    
    map->setPosition( antVec3( m_position->v[0], m_position->v[1], m_position->v[2] )  );
    map->setRotation( *(m_rotation.get()) );
    map->setScale( *(m_scale.get()));
    map->setType( *(m_type.get()));
    
    return map;
}

antMat4 antMapableConfiguration::getLocalToWorldMatrix()
{
    m_rotation->q[0] = m_tw_rotation->v[3];
    m_rotation->q[1] = m_tw_rotation->v[0];
    m_rotation->q[2] = m_tw_rotation->v[1];
    m_rotation->q[3] = m_tw_rotation->v[2];
    
    antMat4 translation_mat = translate( identity_mat4() , *( m_position.get() ) );
    antMat4 rotation_mat = quat_to_mat4( normalise( *( m_rotation.get() ) ) );
    
    mat4 local_to_world_matrix;
    
    switch ( *( m_type.get() ) )
    {
        case SELF : local_to_world_matrix =
            scale( translation_mat * rotation_mat, antVec3( *(m_scale.get()), *(m_scale.get()), *(m_scale.get()) ) );
            break;
        case ORBIT : local_to_world_matrix =
            scale( rotation_mat * translation_mat, antVec3( *(m_scale.get()), *(m_scale.get()), *(m_scale.get()) ) );
            break;
    }
    
    return local_to_world_matrix;
}

antMat4 antMapableConfiguration::getWorldToOriginMatrix()
{
    m_rotation->q[0] = m_tw_rotation->v[3];
    m_rotation->q[1] = m_tw_rotation->v[0];
    m_rotation->q[2] = m_tw_rotation->v[1];
    m_rotation->q[3] = m_tw_rotation->v[2];
    
    antMat4 inv_translation_mat =
    translate( identity_mat4(), antVec3( -m_position->v[0], -m_position->v[1], -m_position->v[2] )  );
    
    antQuat inv_rotation;
    inv_rotation.q[0] = -m_rotation->q[0];
    inv_rotation.q[1] = m_rotation->q[1];
    inv_rotation.q[2] = m_rotation->q[2];
    inv_rotation.q[3] = m_rotation->q[3];
    
    antMat4 inv_rotation_mat = quat_to_mat4( normalise( inv_rotation ) );
    
    mat4 world_to_origin_matrix;
    
    switch ( *( m_type.get() ) )
    {
        case SELF : world_to_origin_matrix = scale( inv_translation_mat * inv_rotation_mat,
                                                   antVec3(*(m_scale.get()), *(m_scale.get()), *(m_scale.get())) );
            break;
        case ORBIT : world_to_origin_matrix = scale( inv_rotation_mat * inv_translation_mat,
                                                    antVec3(*(m_scale.get()), *(m_scale.get()), *(m_scale.get())) );
            break;
    }
    return world_to_origin_matrix;
}