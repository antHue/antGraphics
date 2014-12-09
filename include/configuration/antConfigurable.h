//
//  antConfigurable.h
//  _xcodeproj
//
//  Created by anthonycouret on 09/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef ___xcodeproj__antConfigurable__
#define ___xcodeproj__antConfigurable__

#include <memory>
#include <iostream>

#include "maths_funcs.h"
#include "antTypes.h"
#include "antConfiguration.h"
#include "antMapableConfiguration.h"

class antConfigurable;
typedef std::shared_ptr<antConfigurable> antConfigurableShPtr;
typedef std::weak_ptr<antConfigurable> antConfigurableWkPtr;

class antConfigurable
{
    public :
    
    static antConfigurableShPtr create();
    ~antConfigurable();
    
    
    void makeMapableConfiguration();
    
    antMapableVec3 getMapablePosition();
    antMapableQuat getMapableRotation();
    antMapableVec4 getMapableTwRotation();
    antMapableFloat getMapableScale();
    antMapableRotType getMapableRotType();
    
    void setPosition( antVec3 position );
    void setRotation( antQuat rotation );
    void setConfigType( bool type );
    
    protected :
    
    antAbstractConfigurationShPtr m_world_configuration;

    antConfigurable();
    antConfigurableWkPtr m_weak_ptr;
};

#endif /* defined(___xcodeproj__antConfigurable__) */
