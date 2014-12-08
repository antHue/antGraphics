//
//  antMaterial.cpp
//  ant_graphics
//
//  Created by anthonycouret on 30/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antMaterial.h"

antMaterialShPtr antMaterial::create()
{
    antMaterialShPtr antMaterial_sh_ptr( new antMaterial() );
    antMaterial_sh_ptr->m_weak_ptr = antMaterial_sh_ptr;
    return antMaterial_sh_ptr;
}

antMaterialShPtr antMaterial::create( const antRGBA & ks, const antRGBA & kd, const antRGBA & ka, float sp )
{
    antMaterialShPtr antMaterial_sh_ptr( new antMaterial( ks, kd, ka, sp ) );
    antMaterial_sh_ptr->m_weak_ptr = antMaterial_sh_ptr;
    return antMaterial_sh_ptr;
}

antMaterial::antMaterial()
{
    m_ks = antRGBA( 1.f, 1.f, 1.f, 1.f );
    m_kd = antRGBA( 1.f, 1.f, 1.f, 1.f );
    m_ka = antRGBA( 1.f, 1.f, 1.f, 1.f );
    
    m_specular_power = 1.f;
}

antMaterial::antMaterial( const antRGBA & ks, const antRGBA & kd, const antRGBA & ka, float sp ) :
m_ks( ks ),
m_kd( kd ),
m_ka( ka ),
m_specular_power( sp )
{
}

antMaterial::~antMaterial()
{
    m_weak_ptr.reset();
}

antRGBA antMaterial::getSpecularReflectance()
{
    return m_ks;
}

antRGBA antMaterial::getDiffuseReflectance()
{
    return m_kd;
}

antRGBA antMaterial::getAmbientReflectance()
{
    return m_ka;
}

float antMaterial::getSpecularPower()
{
    return m_specular_power;
}

void antMaterial::setSpecularReflectance( const antRGBA & value )
{
    m_ks = value;
}

void antMaterial::setDiffuseReflectance( const antRGBA & value )
{
    m_kd = value;
}

void antMaterial::setAmbientReflectance( const antRGBA & value )
{
    m_ka = value;
}

void antMaterial::setSpecularPower( float value )
{
    m_specular_power = value;
}