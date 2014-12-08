//
//  antCube.cpp
//  ant_graphics
//
//  Created by anthonycouret on 24/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antCube.h"
#include <iostream>

antCubeShPtr antCube::create
( int nVbo, bool genColors,
 bool genNormals, bool genTexCoords )
{
    antCubeShPtr antCube_sh_ptr( new antCube( nVbo, genColors, genNormals, genTexCoords ) );
    antCube_sh_ptr->m_weak_ptr = antCube_sh_ptr;
    return antCube_sh_ptr;
}

antCube::antCube
( int nVbo, bool genColors,
bool genNormals, bool genTexCoords ) :
antDrawable( nVbo, ATTR_POSITION )
{
    m_nVertices = ( 12 * 3 * 3 );
    
    generateVertices();
    if ( genColors ) { generateColors(); }
    if ( genNormals ) { generateNormals(); }
    if ( genTexCoords ) { generateTexCoords(); }
}

void antCube::generateVertices()
{
    m_vertices = ( GLfloat * ) malloc( N_VERTEX_ATTRIBS * m_nVertices * sizeof( GLfloat ) );
    
    GLfloat vertices[12 * 3 * 3] =
    {
        // back face
        -1.f, 1.f, -1.f,      // left top far
        -1.f, -1.f, -1.f,    // left bottom far
        1.f, -1.f, -1.f,     // right bottom far
        
        1.f, -1.f, -1.f,     // right bottom far
        1.f, 1.f, -1.f,      // right top far
        -1.f, 1.f, -1.f,     // left top far
        
        // left face
        -1.f, -1.f, 1.f,
        -1.f, -1.f, -1.f,
        -1.f, 1.f, -1.f,
        
        -1.f, 1.f, -1.f,
        -1.f, 1.f, 1.f,
        -1.f, -1.f, 1.f,
        
        // right face
        1.f, -1.f, -1.f,
        1.f, -1.f, 1.f,
        1.f, 1.f, 1.f,
        
        1.f, 1.f, 1.f,
        1.f, 1.f, -1.f,
        1.f, -1.f, -1.f,

        
        // front face
        -1.f, -1.f, 1.f,
        -1.f, 1.f, 1.f,
        1.f, 1.f, 1.f,
        
        1.f, 1.f, 1.f,
        1.f, -1.f, 1.f,
        -1.f, -1.f, 1.f,
        
        // top face
        -1.f, 1.f, -1.f,
        1.f, 1.f, -1.f,
        1.f, 1.f, 1.f,
        
        1.f, 1.f, 1.f,
        -1.f, 1.f, 1.f,
        -1.f, 1.f, -1.f,
        
        // bottom face
        -1.f, -1.f, -1.f,
        -1.f, -1.f, 1.f,
        1.f, -1.f, -1.f,
        
        1.f, -1.f, -1.f,
        -1.f, -1.f, 1.f,
        1.f, -1.f, 1.f
    };
    
    for ( int i = 0; i < m_nVertices; i++)
    {
        m_vertices[i] = vertices[i];
    }
    
    m_hasVertices = true;
    bindVao(0);
    bindVbo(0);
    setData( m_nVertices * N_VERTEX_ATTRIBS * sizeof(GLfloat), m_vertices );
    attrib( ATTR_POSITION_LOC, N_VERTEX_ATTRIBS );
    enableVertices();
}

//------------------------------------------------------------------------------
void antCube::generateTexCoords()
{
    std::cout << "antCube::generateTexCoords not defined" << std::endl;
}

void antCube::generateNormals()
{
    std::cout << "antCube::generateNormals not defined" << std::endl;
}

void antCube::generateColors()
{
    std::cout << "antCube::generateColors not defined" << std::endl;
}

void antCube::draw()
{
    antDrawable::draw( GL_TRIANGLES );
}

antCube::~antCube()
{
    m_weak_ptr.reset();
}