//
//  antShader.h
//  ant_graphics
//
//  Created by anthonycouret on 21/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antShader__
#define __ant_graphics__antShader__

#include <iostream>
#include <string>

#include <OpenGL/gl3.h>

class antShader
{
    public :
    
    /**
     \brief create a shader program
     \param vertex_shader vertex shader file path
     \param fragment_shader fragment shader file path
     \return shader program id
     */
    static GLuint createShaderProgram( const std::string & vertex_shader,
                                      const std::string & fragment_shader );
    
    static GLuint createShaderProgram( const std::string & vertex_shader,
                                      const std::string & geometry_shader,
                                      const std::string & fragment_shader );
    
    private :
    
    static GLchar * readFile( const std::string & file_path );
};

#endif /* defined(__ant_graphics__antShader__) */
