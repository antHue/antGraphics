//
//  antDrawable.cpp
//  ant_graphics
//
//  Created by anthonycouret on 30/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antDrawable.h"
#include <iostream>

antDrawable::antDrawable( int nVbo, ... ) :
antConfigurable(),
m_nVertices(0),
m_hasVertices( false ), m_hasColors( false ),
m_hasNormals( false ),  m_hasTexCoords( false ),
m_verticesEnabled( false ), m_colorsEnabled( false ),
m_normalsEnabled( false ),  m_texcoordsEnabled( false )
{
    va_list args;
    va_start( args, nVbo );
    
    for ( int i = 0; i < nVbo; i++ )
    {
        va_arg( args, int );
    }
    
    va_end(args);
    
//    m_world_configuration = antConfiguration::create();
    
    m_vao = antVao::create();
    m_vbo = antVbo::create( nVbo );    
};


int antDrawable::getNVertices() const { return m_nVertices; }

bool antDrawable::hasVertices() const { return m_hasVertices; }
bool antDrawable::hasColors() const { return m_hasColors; }
bool antDrawable::hasNormals() const { return m_hasNormals; }
bool antDrawable::hasTexCoords() const { return m_hasTexCoords; }

void antDrawable::enableVertices()  { m_verticesEnabled = true; m_vao->enable( ATTR_POSITION_LOC    ); }
void antDrawable::enableColors()    { m_colorsEnabled = true;   m_vao->enable( ATTR_COLOR_LOC       ); }
void antDrawable::enableNormals()   { m_normalsEnabled = true;  m_vao->enable( ATTR_NORMAL_LOC      ); }
void antDrawable::enableTexCoords() { m_texcoordsEnabled = true;m_vao->enable( ATTR_TEX_COORD_LOC ); }

void antDrawable::disableVertices() { m_verticesEnabled = false; m_vao->disable( ATTR_POSITION_LOC ); }
void antDrawable::disableColors() { m_colorsEnabled = false;        m_vao->disable( ATTR_COLOR_LOC );}
void antDrawable::disableNormals() { m_normalsEnabled = false;  m_vao->disable( ATTR_NORMAL_LOC );}
void antDrawable::disableTexCoords() { m_texcoordsEnabled = false; m_vao->disable( ATTR_TEX_COORD_LOC );}


void antDrawable::bindVao( int i ) { m_vao->bind( i ); }
void antDrawable::bindVbo( int i ) { m_vbo->bind( i ); }


void antDrawable::setData( GLsizeiptr size, const GLvoid * data, GLenum usage )
{
    m_vbo->setData( size, data, usage );
}


void antDrawable::attrib( GLuint index, GLint size, GLenum type, GLboolean normalized,
                         GLsizei stride, const GLvoid * pointer )
{
    m_vao->attrib( index, size, type, normalized, stride, pointer );
}

void antDrawable::draw( GLenum mode, GLboolean depth_mask )
{
    glDepthMask( depth_mask );
    bindVao( 0 );
    glDrawArrays( mode, 0, m_nVertices );
    
    
    if ( depth_mask == GL_FALSE ) { glDepthMask( GL_TRUE ); }
}

void antDrawable::print()
{
    std::cout << "DRAWABLE  : " << std::endl;
    std::cout << "vertices  " << m_hasVertices  << " " << m_verticesEnabled     << std::endl;
    std::cout << "colors    " << m_hasColors    << " " << m_colorsEnabled       << std::endl;
    std::cout << "normals   " << m_hasNormals   << " " << m_normalsEnabled      << std::endl;
    std::cout << "texcoords " << m_hasTexCoords << " " << m_texcoordsEnabled    << std::endl;
}

antDrawable::~antDrawable()
{
    if ( m_hasVertices  )   { delete m_vertices;    }
    if ( m_hasColors    )   { delete m_colors;      }
    if ( m_hasNormals   )   { delete m_normals;     }
    if ( m_hasTexCoords )   { delete m_texcoords;   }
}

//void antDrawable::setPosition( antVec3 position ) { m_world_config->setPosition( position ); }
//void antDrawable::setRotation( antQuat rotation ) { m_world_config->setRotation( rotation ); };
//void antDrawable::setConfigType( bool type ) { m_world_config->setType( type ? ORBIT : SELF ); };
void antDrawable::setScale( float scale ) { m_world_configuration->setScale( scale ); }

//void antDrawable::makeMapableConfiguration()
//{
//    m_world_config = std::dynamic_pointer_cast<antConfiguration>( m_world_config )->makeMapable();
//}
//
//antMapableVec3 antDrawable::getMapablePosition()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_config)->getMapablePosition();
//}
//
//antMapableQuat antDrawable::getMapableRotation()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_config)->getMapableRotation();
//}
//
//antMapableVec4 antDrawable::getMapableTwRotation()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_config)->getMapableTwRotation();
//}
//
//antMapableFloat antDrawable::getMapableScale()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_config)->getMapableScale();
//}
//
//antMapableRotType antDrawable::getMapableRotType()
//{
//    return std::dynamic_pointer_cast<antMapableConfiguration>(m_world_config)->getMapableRotType();
//}

antMat4 antDrawable::getModelMatrix() { return m_world_configuration->getLocalToWorldMatrix(); }
