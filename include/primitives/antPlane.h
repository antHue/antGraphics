//
//  antPlane.h
//  ant_graphics
//
//  Created by anthonycouret on 30/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antPlane__
#define __ant_graphics__antPlane__

#include <memory>
#include "antMacros.h"
#include "antDrawable.h"
#include "antTypes.h"
#include "antAbtractPrimitive.h"

#include <iostream>


class antPlane;
typedef std::shared_ptr<antPlane> antPlaneShPtr;
typedef std::weak_ptr<antPlane> antPlaneWkPtr;

class antPlane : public antDrawable
{
    public :
    
    static antPlaneShPtr create
    ( float width, float depth, int nColumns, int nRows,
      int nVbo = 4, bool genColors = true, bool
      genNormals = true, bool genTexCoords = true );
    
    ~antPlane();

    void generateVertices();
    void generateColors( const antRGBA & color_1, const antRGBA & color_2 );
    void generateNormals();
    void generateTexCoords();
    
    virtual void draw();
    
    private :
    
    float m_width;
    float m_depth;
    int m_nColumns;
    int m_nRows;
    
    antPlane( float width, float depth, int nColumns, int nRows,
              int nVbo, bool genColors, bool genNormals, bool genTexCoords );
    
    antPlaneWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antPlane__) */
