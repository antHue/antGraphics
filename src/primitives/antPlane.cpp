//
//  antPlane.cpp
//  ant_graphics
//
//  Created by anthonycouret on 30/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antPlane.h"

antPlaneShPtr antPlane::create
( float width, float depth, int nColumns, int nRows,
  int nVbo, bool genColors,
  bool genNormals, bool genTexCoords )
{
    antPlaneShPtr antPlane_sh_ptr
    ( new antPlane( width, depth, nColumns, nRows, nVbo, genColors, genNormals, genTexCoords ) );
    antPlane_sh_ptr->m_weak_ptr = antPlane_sh_ptr;
    return antPlane_sh_ptr;
}

antPlane::antPlane
( float width, float depth, int nColumns, int nRows,
 int nVbo, bool genColors,
 bool genNormals, bool genTexCoords ) :
antDrawable( nVbo, ATTR_POSITION ),
m_width( width ),
m_depth( depth ),
m_nColumns( nColumns ),
m_nRows( nRows )
{
    m_nVertices = ( m_nColumns * m_nRows * 6 );

    antRGBA color1( 0.f, 0.f, 0.f, 1.f );
    antRGBA color2( 1.f, 1.f, 1.f, 1.f );
    
    generateVertices();
    
    if ( genColors ) { generateColors( color1, color2 ); }
    if ( genNormals ) { generateNormals(); }
    if ( genTexCoords ) { generateTexCoords(); }    
}

void antPlane::generateVertices()
{
    float sx = m_width / m_nColumns;
    float sz = m_depth / m_nRows;
    
    m_vertices = ( GLfloat * ) malloc( N_VERTEX_ATTRIBS * m_nVertices * sizeof( GLfloat ) );
    
    for ( int i = 0; i < m_nRows; i++ )
    {
        for ( int j = 0; j < m_nColumns; j++ )
        {
            antVec3 bl( j * sx - m_width / 2.f, 0.f, i * sz - m_depth / 2.f ); // bottom left
            antVec3 tl( j * sx - m_width / 2.f, 0.f, ( i + 1 ) * sz - m_depth / 2.f ); // top left
            antVec3 tr( ( j + 1 ) * sx - m_width / 2.f, 0.f, ( i + 1 ) * sz - m_depth / 2.f ); // top right
            antVec3 br( ( j + 1 ) * sx - m_width / 2.f, 0.f, i * sz - m_depth / 2.f ); // bottom right
            
            int v = (i * m_nColumns + j) * 6 * N_VERTEX_ATTRIBS;
            for ( int n = 0; n < N_VERTEX_ATTRIBS; n++ )
            {
                m_vertices[ v + n ] = bl.v[n];
                m_vertices[ v + (1 * N_VERTEX_ATTRIBS) + n ] = tl.v[n];
                m_vertices[ v + (2 * N_VERTEX_ATTRIBS) + n ] = tr.v[n];
                
                m_vertices[ v + (3 * N_VERTEX_ATTRIBS) + n ] = tr.v[n];
                m_vertices[ v + (4 * N_VERTEX_ATTRIBS) + n ] = br.v[n];
                m_vertices[ v + (5 * N_VERTEX_ATTRIBS) + n ] = bl.v[n];
            }
        }
    }
    
    m_hasVertices = true;    
    bindVao(0);
    bindVbo(0);
    setData( m_nVertices * N_VERTEX_ATTRIBS * sizeof(GLfloat), m_vertices );
    attrib( ATTR_POSITION_LOC, N_VERTEX_ATTRIBS );
    enableVertices();
}

void antPlane::generateColors( const antRGBA & color_1, const antRGBA & color_2 )
{
    m_colors = ( GLfloat * ) malloc( N_COLOR_ATTRIBS * m_nVertices * sizeof( GLfloat ) );
    
    // for each square ---------------------------------------------------------
    for ( int i = 0; i < m_nRows; i++ )
    {
        for ( int j = 0; j < m_nColumns; j++ )
        {
    //--------------------------------------------------------------------------
            
            int c = (i * m_nColumns + j) * 6 * N_COLOR_ATTRIBS;
            
            // for each
            for ( int n = 0; n < N_COLOR_ATTRIBS; n++ )
            {
                m_colors[ c + n ] = color_1.v[n];
                m_colors[ c + (1 * N_COLOR_ATTRIBS) + n ] = color_1.v[n];
                m_colors[ c + (2 * N_COLOR_ATTRIBS) + n ] = color_1.v[n];
                
                m_colors[ c + (3 * N_COLOR_ATTRIBS) + n ] = color_2.v[n];
                m_colors[ c + (4 * N_COLOR_ATTRIBS) + n ] = color_2.v[n];
                m_colors[ c + (5 * N_COLOR_ATTRIBS) + n ] = color_2.v[n];
            }
        }
    }
    
    m_hasColors = true;
    bindVao(0);
    bindVbo(1);
    setData( m_nVertices * N_COLOR_ATTRIBS * sizeof(GLfloat), m_colors );
    attrib( ATTR_COLOR_LOC, N_COLOR_ATTRIBS );
    enableColors();
}

//------------------------------------------------------------------------------
void antPlane::generateTexCoords()
{
    std::cout << "antPlane::generateTexCoords not defined" << std::endl;
}

void antPlane::generateNormals()
{
    std::cout << "antPlane::generateNormals not defined" << std::endl;
}

void antPlane::draw()
{
    antDrawable::draw( GL_TRIANGLES );
}

antPlane::~antPlane()
{
    m_weak_ptr.reset();
}