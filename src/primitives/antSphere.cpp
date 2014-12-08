//
//  antSphere.cpp
//  ant_graphics
//
//  Created by anthonycouret on 08/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antSphere.h"
#include "antObjLoader.h"

antSphereShPtr antSphere::create()
{
    antObjLoaderShPtr obj_loader = antObjLoader::create
        ( "/Users/anthonycouret/Developer/antGraphics/_models/sphere.obj" );

    antSphereShPtr antSphere_sh_ptr( new antSphere( obj_loader->getNVertices() ) );
    antSphere_sh_ptr->m_weak_ptr = antSphere_sh_ptr;
    
    antSphere_sh_ptr->m_hasVertices =
    obj_loader->loadVertices( antSphere_sh_ptr->m_vertices );
    
    antSphere_sh_ptr->m_hasColors =
    obj_loader->loadColors( antSphere_sh_ptr->m_colors );
    
    antSphere_sh_ptr->m_hasNormals =
    obj_loader->loadNormals( antSphere_sh_ptr->m_normals );
    
    antSphere_sh_ptr->m_hasTexCoords =
    obj_loader->loadTexCoords( antSphere_sh_ptr->m_texcoords );
    
    antSphere_sh_ptr->fill();
    
    return antSphere_sh_ptr;
}

antSphere::antSphere( int nVertices ) :
antDrawable( 4, ATTR_POSITION, ATTR_COLOR, ATTR_NORMAL, ATTR_TEX_COORD )
{
    m_nVertices = nVertices;
    
    m_vertices = ( GLfloat * ) malloc( N_VERTEX_ATTRIBS * nVertices * sizeof( GLfloat ) );
    m_colors = ( GLfloat * ) malloc( N_COLOR_ATTRIBS * nVertices * sizeof( GLfloat ) );
    m_normals = ( GLfloat * ) malloc( N_NORMAL_ATTRIBS * nVertices * sizeof( GLfloat ) );
    m_texcoords = ( GLfloat * ) malloc( N_TEXCOORDS_ATTRIBS * nVertices * sizeof( GLfloat ) );
}

void antSphere::fill()
{
    bindVao(0);
    
    if ( m_hasVertices )
    {
        bindVbo( 0 );
        setData( m_nVertices * N_VERTEX_ATTRIBS * sizeof( GLfloat ), m_vertices );
        attrib( ATTR_POSITION_LOC, N_VERTEX_ATTRIBS );
        enableVertices();
    }
    
    if ( m_hasNormals )
    {
        bindVbo( 2 );
        setData( m_nVertices * N_NORMAL_ATTRIBS * sizeof( GLfloat ), m_normals );
        attrib( ATTR_NORMAL_LOC, N_NORMAL_ATTRIBS );
        enableNormals();
        
        
        if ( m_hasColors )
        {
            bindVbo( 1 );
            setData( m_nVertices * N_COLOR_ATTRIBS * sizeof( GLfloat ), m_colors );
            attrib( ATTR_COLOR_LOC, N_COLOR_ATTRIBS );
            enableColors();
        }
        else
        {
            GLfloat colors[ m_nVertices * N_COLOR_ATTRIBS ];
            
            for ( int i = 0; i < m_nVertices; i++ )
            {
                colors[i * N_COLOR_ATTRIBS] = m_normals[i * N_NORMAL_ATTRIBS];
                colors[i * N_COLOR_ATTRIBS + 1] = m_normals[i * N_NORMAL_ATTRIBS + 1];
                colors[i * N_COLOR_ATTRIBS + 2] = m_normals[i * N_NORMAL_ATTRIBS + 2];
                colors[i * N_COLOR_ATTRIBS + 3] = 1.f;
            }
            
            bindVbo( 1 );
            setData( m_nVertices * N_COLOR_ATTRIBS * sizeof( GLfloat ), colors );
            attrib( ATTR_COLOR_LOC, N_COLOR_ATTRIBS );
            m_hasColors = true;
            enableColors();
        }
    }
    
    if ( m_hasTexCoords )
    {
        bindVbo( 3 );
        setData( m_nVertices * N_TEXCOORDS_ATTRIBS * sizeof( GLfloat ), m_texcoords );
        attrib( ATTR_TEX_COORD_LOC, N_TEXCOORDS_ATTRIBS );
        enableTexCoords();
    }
}


antSphere::~antSphere()
{
    m_weak_ptr.reset();
}