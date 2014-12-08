//
//  antAxis.cpp
//  ant_graphics
//
//  Created by anthonycouret on 30/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antAxis.h"

#include <iostream>

antAxisShPtr antAxis::create
( int nVbo, bool genColors )
{
    antAxisShPtr antAxis_sh_ptr( new antAxis( nVbo, genColors) );
    antAxis_sh_ptr->m_weak_ptr = antAxis_sh_ptr;
    return antAxis_sh_ptr;
}

antAxis::antAxis( int nVbo, bool genColors ) :
antDrawable( nVbo, ATTR_POSITION, ATTR_COLOR )
{
    m_nVertices = 6;
    
    generateVertices();
    
    if ( genColors ) { generateColors(); }
}

void antAxis::generateColors()
{
    m_colors = ( GLfloat * ) malloc( N_COLOR_ATTRIBS * m_nVertices * sizeof( GLfloat ) );

    m_colors[0 * N_COLOR_ATTRIBS] = 0.f;
    m_colors[0 * N_COLOR_ATTRIBS + 1] = 0.f;
    m_colors[0 * N_COLOR_ATTRIBS + 2] = 1.f;
    m_colors[0 * N_COLOR_ATTRIBS + 3] = 1.f;
    
    m_colors[1 * N_COLOR_ATTRIBS] = 0.f;
    m_colors[1 * N_COLOR_ATTRIBS + 1] = 0.f;
    m_colors[1 * N_COLOR_ATTRIBS + 2] = 1.f;
    m_colors[1 * N_COLOR_ATTRIBS + 3] = 1.f;
    
    m_colors[2 * N_COLOR_ATTRIBS] = 1.f;
    m_colors[2 * N_COLOR_ATTRIBS + 1] = 0.f;
    m_colors[2 * N_COLOR_ATTRIBS + 2] = 0.f;
    m_colors[2 * N_COLOR_ATTRIBS + 3] = 1.f;
    
    m_colors[3 * N_COLOR_ATTRIBS] = 1.f;
    m_colors[3 * N_COLOR_ATTRIBS + 1] = 0.f;
    m_colors[3 * N_COLOR_ATTRIBS + 2] = 0.f;
    m_colors[3 * N_COLOR_ATTRIBS + 3] = 1.f;
    
    m_colors[4 * N_COLOR_ATTRIBS] = 0.f;
    m_colors[4 * N_COLOR_ATTRIBS + 1] = 1.f;
    m_colors[4 * N_COLOR_ATTRIBS + 2] = 0.f;
    m_colors[4 * N_COLOR_ATTRIBS + 3] = 1.f;
    
    m_colors[5 * N_COLOR_ATTRIBS] = 0.f;
    m_colors[5 * N_COLOR_ATTRIBS + 1] = 1.f;
    m_colors[5 * N_COLOR_ATTRIBS + 2] = 0.f;
    m_colors[5 * N_COLOR_ATTRIBS + 3] = 1.f;
    
    m_hasColors = true;
    
    bindVbo( 1 );
    setData( m_nVertices * N_COLOR_ATTRIBS * sizeof( GLfloat ), m_colors );
    attrib( ATTR_COLOR_LOC, N_COLOR_ATTRIBS );
    enableColors();
}

void antAxis::generateVertices()
{
    m_vertices = ( GLfloat * ) malloc( N_VERTEX_ATTRIBS * m_nVertices * sizeof( GLfloat ) );
    
    /* Z AXIS */
    m_vertices[0 * N_VERTEX_ATTRIBS] = 0.f;
    m_vertices[0 * N_VERTEX_ATTRIBS + 1] = 0.f;
    m_vertices[0 * N_VERTEX_ATTRIBS + 2] = -1.f;
    
    m_vertices[1 * N_VERTEX_ATTRIBS] = 0.f;
    m_vertices[1 * N_VERTEX_ATTRIBS + 1] = 0.f;
    m_vertices[1 * N_VERTEX_ATTRIBS + 2] = 1.f;

    /* X AXIS */
    m_vertices[2 * N_VERTEX_ATTRIBS] = -1.f;
    m_vertices[2 * N_VERTEX_ATTRIBS + 1] = 0.f;
    m_vertices[2 * N_VERTEX_ATTRIBS + 2] = 0.f;
    
    m_vertices[3 * N_VERTEX_ATTRIBS] = 1.f;
    m_vertices[3 * N_VERTEX_ATTRIBS + 1] = 0.f;
    m_vertices[3 * N_VERTEX_ATTRIBS + 2] = 0.f;
    
    /* Y AXIS */
    m_vertices[4 * N_VERTEX_ATTRIBS] = 0.f;
    m_vertices[4 * N_VERTEX_ATTRIBS + 1] = -1.f;
    m_vertices[4 * N_VERTEX_ATTRIBS + 2] = 0.f;
    
    m_vertices[5 * N_VERTEX_ATTRIBS] = 0.f;
    m_vertices[5 * N_VERTEX_ATTRIBS + 1] = 1.f;
    m_vertices[5 * N_VERTEX_ATTRIBS + 2] = 0.f;
    
    m_hasVertices = true;
    
    bindVao(0);
    
        bindVbo( 0 );
        setData( m_nVertices * N_VERTEX_ATTRIBS * sizeof( GLfloat ), m_vertices );
        attrib( ATTR_POSITION_LOC, N_VERTEX_ATTRIBS );
        enableVertices();
}

void antAxis::draw()
{
    antDrawable::draw( GL_LINES );
}


antAxis::~antAxis()
{
    m_weak_ptr.reset();
}