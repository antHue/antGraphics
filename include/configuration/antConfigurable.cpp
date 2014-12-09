//
//  antConfigurable.cpp
//  _xcodeproj
//
//  Created by anthonycouret on 09/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antConfigurable.h"

antConfigurableShPtr antConfigurable::create()
{
    antConfigurableShPtr antConfigurable_sh_ptr( new antConfigurable() );
    antConfigurable_sh_ptr->m_weak_ptr = antConfigurable_sh_ptr;
    return antConfigurable_sh_ptr;
}

antConfigurable::antConfigurable()
{
    m_world_configuration = antConfiguration::create();
}

antConfigurable::~antConfigurable()
{
    m_weak_ptr.reset();
}

void antConfigurable::setPosition( antVec3 position )
{
    m_world_configuration->setPosition( position );
}

void antConfigurable::makeMapableConfiguration()
{
    m_world_configuration = std::dynamic_pointer_cast<antConfiguration>( m_world_configuration )->makeMapable();
}

antMapableVec3 antConfigurable::getMapablePosition()
{
    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapablePosition();
}

antMapableQuat antConfigurable::getMapableRotation()
{
    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapableRotation();
}

antMapableVec4 antConfigurable::getMapableTwRotation()
{
    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapableTwRotation();
}

antMapableFloat antConfigurable::getMapableScale()
{
    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapableScale();
}

antMapableRotType antConfigurable::getMapableRotType()
{
    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_configuration)->getMapableRotType();
}

void antConfigurable::setRotation( antQuat rotation )
{
    m_world_configuration->setRotation( rotation );
}

void antConfigurable::setConfigType( bool type )
{
    m_world_configuration->setType( type ? ORBIT : SELF );
};
