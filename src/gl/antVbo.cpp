//
//  antVbo.cpp
//  ant_graphics
//
//  Created by anthonycouret on 24/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antVbo.h"

//------------------------------------------------------------------------------
antVboShPtr antVbo::create( int n, GLenum target )
{
    antVboShPtr antVbo_sh_ptr( new antVbo( n, target ) );
    antVbo_sh_ptr->m_weak_ptr = antVbo_sh_ptr;
    return antVbo_sh_ptr;
}

//------------------------------------------------------------------------------
antVbo::antVbo( int n, GLenum target ) :
m_n( n ),
m_target( target )
{
    m_id = ( GLuint * ) malloc ( n * sizeof( GLuint ) );
    glGenBuffers( n, m_id );
}

//------------------------------------------------------------------------------
antVbo::~antVbo()
{
    glDeleteBuffers( m_n, m_id );
    delete m_id;
    
    m_weak_ptr.reset();
}

//------------------------------------------------------------------------------
GLuint antVbo::get( int i ) const
{
    return m_id[i];
}

//------------------------------------------------------------------------------
void antVbo::bind( int i )
{
    glBindBuffer( m_target, m_id[i] );
}

//------------------------------------------------------------------------------
void antVbo::setData
    ( GLsizeiptr size, const GLvoid * data, GLenum usage )
{
    glBufferData( m_target, size, data, usage );
}