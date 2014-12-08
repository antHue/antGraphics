//
//  antPointLight.h
//  ant_graphics
//
//  Created by anthonycouret on 23/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antPointLight__
#define __ant_graphics__antPointLight__

#include <memory>

#include "antTypes.h"

class antPointLight;
typedef std::shared_ptr<antPointLight> antPointLightShPtr;
typedef std::weak_ptr<antPointLight> antPointLightWkPtr;

class antPointLight
{
    public :
    
    static antPointLightShPtr create( const antVec3 & position );
    ~antPointLight();
    
    void setPosition( const antVec3 & position );
    void setSpecularColor( const antRGBA & color );
    
    antVec3 getPosition();
    antRGBA getSpecularColor();
    
    protected :
    
    antVec3 m_position;    
    antRGBA m_specular_color;
    
    antPointLight( const antVec3 & position );
    antPointLightWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antPointLight__) */
