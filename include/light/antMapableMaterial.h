//
//  antMapableMaterial.h
//  _xcodeproj
//
//  Created by anthonycouret on 09/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef ___xcodeproj__antMapableMaterial__
#define ___xcodeproj__antMapableMaterial__

#include <memory>
#include <iostream>

#include "antTypes.h"

class antMapableMaterial;
typedef std::shared_ptr<antMapableMaterial> antMapableMaterialShPtr;
typedef std::weak_ptr<antMapableMaterial> antMapableMaterialWkPtr;

class antMapableMaterial
{
    public :
    
    static antMapableMaterialShPtr create();
    static antMapableMaterialShPtr create
    ( const antRGBA & ks, const antRGBA & kd, const antRGBA & ka, float sp );
    
    ~antMapableMaterial();
    
    antMapableRGBA getSpecularReflectance();
    antMapableRGBA getDiffuseReflectance();
    antMapableRGBA getAmbientReflectance();
    antMapableFloat getSpecularPower();
    
    void setSpecularReflectance( const antRGBA & ks );
    void setDiffuseReflectance( const antRGBA & kd );
    void setAmbientReflectance( const antRGBA & ka );
    void setSpecularPower( float value );
    
    private :
    
    antMapableRGBA m_ks;
    antMapableRGBA m_kd;
    antMapableRGBA m_ka;
    
    antMapableFloat m_specular_power;
    
    antMapableMaterial();
    antMapableMaterial( const antRGBA & ks, const antRGBA & kd, const antRGBA & ka, float sp );
    
    antMapableMaterialWkPtr m_weak_ptr;
};

#endif /* defined(___xcodeproj__antMapableMaterial__) */
