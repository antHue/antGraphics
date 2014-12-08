//
//  antCube.h
//  ant_graphics
//
//  Created by anthonycouret on 24/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antCube__
#define __ant_graphics__antCube__

#include <memory>
#include "antDrawable.h"
#include <OpenGL/gl3.h>

class antCube;
typedef std::shared_ptr<antCube> antCubeShPtr;
typedef std::weak_ptr<antCube> antCubeWkPtr;

class antCube : public antDrawable
{
    public :
    
    static antCubeShPtr create
    (int nVbo = 4, bool genColors = true,
     bool genNormals = true, bool genTexCoords = true);
    
    ~antCube();
    
    void generateVertices();
    void generateColors();
    void generateNormals();
    void generateTexCoords();
    
    virtual void draw();

    protected :
    
    antCube( int nVbo, bool genColors, bool genNormals, bool genTexCoords );
    
    private :
    
    antCubeWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antCube__) */
