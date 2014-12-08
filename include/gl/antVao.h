//
//  antVao.h
//  ant_graphics
//
//  Created by anthonycouret on 25/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antVao__
#define __ant_graphics__antVao__

#include <stdlib.h>
#include <memory>

#include <OpenGL/gl3.h>

class antVao;
typedef std::shared_ptr<antVao> antVaoShPtr;
typedef std::weak_ptr<antVao> antVaoWkPtr;

/** class antVao

    \brief vertex array object 
 */
class antVao
{
    public :
    
    /** static creation
     
        \param  n number of vertex array objects
     */
    static antVaoShPtr create( int n = 1 );
    
    ~antVao();
    
    /** get
     
        \param  vao index
        \return vao id
     */
    GLuint get( int index = 0 ) const;
    
    /** bind
     
     \param index vao index
     */
    void bind( int index );
    
    /** attrib
     
     \param index vao index
     \param size size ? !!!
     */
    void attrib( GLuint location, GLint attribs_size, GLenum type, GLboolean normalized,
                GLsizei stride, const GLvoid * pointer );
    
    void enable( GLuint location );
    void disable( GLuint location );
    
    private :
    
    /** number of vertex array objects */
    int m_n;
    
    /** vertex array objects ids pointer */
    GLuint * m_id;
    
    antVao( int n );
    antVaoWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antVao__) */
