//
//  antVbo.h
//  ant_graphics
//
//  Created by anthonycouret on 24/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antVbo__
#define __ant_graphics__antVbo__

#include <stdlib.h>
#include <memory>

#include <OpenGL/gl3.h>

class antVbo;
typedef std::shared_ptr<antVbo> antVboShPtr;
typedef std::weak_ptr<antVbo> antVboWkPtr;

/** class antVao
 
 \brief vertex array object
 */
class antVbo
{
    public :
    
    /** static creation
     
     \param  n number of vertex buffer objects
     */
    static antVboShPtr create( int n = 1, GLenum target = GL_ARRAY_BUFFER );
    
    /** destructor */
    ~antVbo();

    /** get
     
        \param  index vbo index
        \return vbo id
     */
    GLuint get( int index = 0 ) const;
    
    /** bind
        
        \param index vbo index
     */
    void bind( int index );
    
    /** setData
     
        \param size buffer size
        \param data data pointer
     */
    void setData( GLsizeiptr size, const GLvoid * data, GLenum usage );
    
    
    private :
    
    /** number of vertex buffer objects */
    int m_n;
    
    /** vertex buffer objects ids pointer */
    GLuint * m_id;
    
    GLenum m_target;
    
    antVbo( int n, GLenum target );
    antVboWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antVbo__) */
