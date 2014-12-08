//
//  antVao.cpp
//  ant_graphics
//
//  Created by anthonycouret on 25/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antVao.h"

//------------------------------------------------------------------------------
antVaoShPtr antVao::create( int n )
{
    antVaoShPtr antVao_sh_ptr( new antVao( n ) );
    antVao_sh_ptr->m_weak_ptr = antVao_sh_ptr;
    return antVao_sh_ptr;
}

//------------------------------------------------------------------------------
antVao::antVao( int n ) :
m_n( n )
{
    m_id = ( GLuint * ) malloc ( n * sizeof( GLuint ) );
    glGenVertexArrays( n, m_id );
}

//------------------------------------------------------------------------------
antVao::~antVao()
{
    glDeleteVertexArrays( m_n, m_id );
    delete m_id;
    
    m_weak_ptr.reset();
}

//------------------------------------------------------------------------------
GLuint antVao::get( int index ) const
{
    return m_id[index];
}

//------------------------------------------------------------------------------
void antVao::bind( int index )
{
    glBindVertexArray( m_id[index] );
}

//------------------------------------------------------------------------------
void antVao::attrib( GLuint location, GLint attribs_size, GLenum type, GLboolean normalized,
                    GLsizei stride, const GLvoid * pointer )
{
    glVertexAttribPointer( location, attribs_size, type, normalized, stride, pointer );
}

//------------------------------------------------------------------------------
void antVao::enable( GLuint location )
{
    glEnableVertexAttribArray( location );
}

//------------------------------------------------------------------------------
void antVao::disable( GLuint location )
{
    glDisableVertexAttribArray( location );
}

