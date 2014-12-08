//
//  antAxis.h
//  ant_graphics
//
//  Created by anthonycouret on 30/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antAxis__
#define __ant_graphics__antAxis__

#include <memory>
#include "antMacros.h"
#include "antTypes.h"
#include "antDrawable.h"

class antAxis;
typedef std::shared_ptr<antAxis> antAxisShPtr;
typedef std::weak_ptr<antAxis> antAxisWkPtr;

class antAxis : public antDrawable
{
    public :
    
    static antAxisShPtr create( int nVbo, bool genColors = true );
    ~antAxis();
    
    void generateVertices();
    void generateColors();
    
    virtual void draw();
    
    private :
    
    antAxis( int nVbo, bool genColors );
    antAxisWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antAxis__) */
