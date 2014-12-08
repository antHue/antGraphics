//
//  antSphere.h
//  ant_graphics
//
//  Created by anthonycouret on 08/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antSphere__
#define __ant_graphics__antSphere__

#include <memory>
#include <iostream>

#include "antWindow.h"
#include "antDrawable.h"

class antSphere;
typedef std::shared_ptr<antSphere> antSphereShPtr;
typedef std::weak_ptr<antSphere> antSphereWkPtr;

class antSphere : public antDrawable
{
    public :
    
    static antSphereShPtr create();
    
    ~antSphere();
        
    private :
    
    void fill();
    
    antSphere( int nVertices );
    antSphereWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antSphere__) */
