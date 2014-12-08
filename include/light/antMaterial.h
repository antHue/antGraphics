//
//  antMaterial.h
//  ant_graphics
//
//  Created by anthonycouret on 30/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antMaterial__
#define __ant_graphics__antMaterial__

#include <memory>
#include "antTypes.h"


class antMaterial;
typedef std::shared_ptr<antMaterial> antMaterialShPtr;
typedef std::weak_ptr<antMaterial> antMaterialWkPtr;

class antMaterial
{
    public :
    
    static antMaterialShPtr create();
    static antMaterialShPtr create( const antRGBA & ks, const antRGBA & kd, const antRGBA & ka, float sp );

    ~antMaterial();
    
    antRGBA getSpecularReflectance();
    antRGBA getDiffuseReflectance();
    antRGBA getAmbientReflectance();
    float getSpecularPower();
    
    void setSpecularReflectance( const antRGBA & value );
    void setDiffuseReflectance( const antRGBA & value );
    void setAmbientReflectance( const antRGBA & value );
    void setSpecularPower( float value );
    
    private :
    
    antRGBA m_ks;
    antRGBA m_kd;
    antRGBA m_ka;
    
    float m_specular_power;
    
    antMaterial();
    antMaterial( const antRGBA & ks, const antRGBA & kd, const antRGBA & ka, float sp );
    
    antMaterialWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antMaterial__) */
