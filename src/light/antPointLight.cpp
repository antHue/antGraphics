//
//  antPointLight.cpp
//  ant_graphics
//
//  Created by anthonycouret on 23/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antPointLight.h"

antPointLightShPtr antPointLight::create( const antVec3 & position )
{
    antPointLightShPtr antPointLight_sh_ptr( new antPointLight( position ) );
    antPointLight_sh_ptr->m_weak_ptr = antPointLight_sh_ptr;
    return antPointLight_sh_ptr;
}

antPointLight::antPointLight( const antVec3 & position )
{
    m_position = position;
    m_specular_color = antRGBA( 1.f, 1.f, 1.f, 1.f );
}

antPointLight::~antPointLight()
{
    m_weak_ptr.reset();
}

void antPointLight::setPosition( const antVec3 & position )
{
    m_position = position;
}

void antPointLight::setSpecularColor( const antRGBA & color )
{
    m_specular_color = color;
}

antVec3 antPointLight::getPosition()
{
    return m_position;
}
antRGBA antPointLight::getSpecularColor()
{
    return m_specular_color;
}