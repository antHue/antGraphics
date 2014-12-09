//
//  antMapableMaterial.cpp
//  _xcodeproj
//
//  Created by anthonycouret on 09/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antMapableMaterial.h"

antMapableMaterialShPtr antMapableMaterial::create
( const antRGBA & ks, const antRGBA & kd, const antRGBA & ka, float sp )
{
    antMapableMaterialShPtr antMapableMaterial_sh_ptr( new antMapableMaterial( ks, kd, ka, sp) );
    antMapableMaterial_sh_ptr->m_weak_ptr = antMapableMaterial_sh_ptr;
    return antMapableMaterial_sh_ptr;
}


antMapableMaterialShPtr antMapableMaterial::create()
{
    antMapableMaterialShPtr antMapableMaterial_sh_ptr( new antMapableMaterial() );
    antMapableMaterial_sh_ptr->m_weak_ptr = antMapableMaterial_sh_ptr;
    return antMapableMaterial_sh_ptr;
}


antMapableMaterial::antMapableMaterial()
{
    m_ks = antMapableRGBA( new antRGBA( 1.f, 1.f, 1.f, 1.f ) );
    m_kd = antMapableRGBA( new antRGBA( 1.f, 1.f, 1.f, 1.f ) );
    m_ka = antMapableRGBA( new antRGBA( 1.f, 1.f, 1.f, 1.f ) );
    
    m_specular_power = antMapableFloat( new float(1.f) );
}

antMapableMaterial::antMapableMaterial
( const antRGBA & ks, const antRGBA & kd, const antRGBA & ka, float sp )
{
    m_ks = antMapableRGBA( new antRGBA(ks.v[0], ks.v[1], ks.v[2], ks.v[3]) );
    m_kd = antMapableRGBA( new antRGBA(kd.v[0], kd.v[1], kd.v[2], kd.v[3]) );
    m_ka = antMapableRGBA( new antRGBA(ka.v[0], ka.v[1], ka.v[2], ka.v[3]) );
    m_specular_power = antMapableFloat( new float(sp) );

}

antMapableMaterial::~antMapableMaterial()
{
    m_weak_ptr.reset();
}

antMapableRGBA antMapableMaterial::getSpecularReflectance()
{
    return m_ks;
}

antMapableRGBA antMapableMaterial::getDiffuseReflectance()
{
    return m_kd;
}

antMapableRGBA antMapableMaterial::getAmbientReflectance()
{
    return m_ka;
}

antMapableFloat antMapableMaterial::getSpecularPower()
{
    return m_specular_power;
}

void antMapableMaterial::setSpecularReflectance( const antRGBA & ks )
{
    m_ks->v[0] = ks.v[0];
    m_ks->v[1] = ks.v[1];
    m_ks->v[2] = ks.v[2];
    m_ks->v[3] = ks.v[3];
}

void antMapableMaterial::setDiffuseReflectance( const antRGBA & kd )
{
    m_kd->v[0] = kd.v[0];
    m_kd->v[1] = kd.v[1];
    m_kd->v[2] = kd.v[2];
    m_kd->v[3] = kd.v[3];
}

void antMapableMaterial::setAmbientReflectance( const antRGBA & ka )
{
    m_ka->v[0] = ka.v[0];
    m_ka->v[1] = ka.v[1];
    m_ka->v[2] = ka.v[2];
    m_ka->v[3] = ka.v[3];
}

void antMapableMaterial::setSpecularPower( float value )
{
    *(m_specular_power.get()) = value;
}