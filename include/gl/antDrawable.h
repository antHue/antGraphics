//
//  antDrawable.h
//  ant_graphics
//
//  Created by anthonycouret on 27/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antDrawable__
#define __ant_graphics__antDrawable__

#include <memory>
#include <cstdarg>

#include "antMacros.h"
#include "antVbo.h"
#include "antVao.h"
#include "antTypes.h"
#include "antConfiguration.h"

#include <OpenGL/gl3.h>

class antDrawable;
typedef std::shared_ptr<antDrawable> antDrawableShPtr;
typedef std::weak_ptr<antDrawable> antDrawableWkPtr;


class antDrawable
{
    public :
    
    virtual void draw( GLenum mode, GLboolean depth_mask = GL_TRUE );
 
    void bindVao( int i );
    
    void bindVbo( int i );
    
    void setData( GLsizeiptr size, const GLvoid * data, GLenum usage = GL_STATIC_DRAW );
    
    void attrib( GLuint index, GLint size,
                GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE,
                GLsizei stride = 0, const GLvoid * pointer = 0 );
    
    int  getNVertices() const;
    
    bool hasVertices()  const;
    bool hasColors()    const;
    bool hasNormals()   const;
    bool hasTexCoords() const;
    
    void enableVertices();      void disableVertices();
    void enableColors();        void disableColors();
    void enableNormals();       void disableNormals();
    void enableTexCoords();     void disableTexCoords();
    
    void print();
    
    ~antDrawable();
    
    protected :
    
    antVaoShPtr m_vao;
    antVboShPtr m_vbo;
    
    int m_nVertices;
    
    GLfloat * m_vertices;   bool m_hasVertices;   bool m_verticesEnabled;
    GLfloat * m_colors;     bool m_hasColors;     bool m_colorsEnabled;
    GLfloat * m_normals;    bool m_hasNormals;    bool m_normalsEnabled;
    GLfloat * m_texcoords;  bool m_hasTexCoords;  bool m_texcoordsEnabled;
    
    antConfigurationShPtr m_world_config;
    
    antDrawable( int nVbo, ... );
    
    /* CONFIGURATION MODIFIERS */
    
    public :
    
    void setPosition( antVec3 position );
    void setRotation( antQuat rotation );
    void setConfigType( bool type );
    void setScale( float scale );
    
    antMat4 getModelMatrix();
};

#endif /* defined(__ant_graphics__antDrawable__) */
