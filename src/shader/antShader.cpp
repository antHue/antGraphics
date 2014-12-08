//
//  antShader.cpp
//  ant_graphics
//
//  Created by anthonycouret on 21/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antShader.h"

GLuint antShader::createShaderProgram( const std::string & vertex_shader,
                                      const std::string & fragment_shader )
{
    GLuint vertex_shader_id;
    GLuint fragment_shader_id;
    GLuint program_id;
    
    const GLchar * vertex_shader_source = readFile( vertex_shader );
    const GLchar * fragment_shader_source = readFile( fragment_shader );
    
    vertex_shader_id = glCreateShader( GL_VERTEX_SHADER );
    fragment_shader_id = glCreateShader( GL_FRAGMENT_SHADER );
    
    // id, number = 1, source, length = NULL
    glShaderSource( vertex_shader_id, 1, &vertex_shader_source, NULL );
    
    glShaderSource( fragment_shader_id, 1, &fragment_shader_source, NULL );
    
    glCompileShader( vertex_shader_id );
    int compiled = -1;
    glGetShaderiv( vertex_shader_id, GL_COMPILE_STATUS, &compiled );
    if ( GL_TRUE != compiled )
    {
        std::cerr << "ERROR : antShader::createShaderProgram() glCompileShader() vertex" << std::endl;
        return -1;
    }
    
    glCompileShader( fragment_shader_id );
    glGetShaderiv( fragment_shader_id, GL_COMPILE_STATUS, &compiled );
    if ( GL_TRUE != compiled )
    {
        std::cerr << "ERROR : antShader::createShaderProgram() glCompileShader() fragment " << std::endl;
        return -1;
    }
    
    program_id = glCreateProgram();
    glAttachShader( program_id, vertex_shader_id );
    glAttachShader( program_id, fragment_shader_id );
    glLinkProgram( program_id );
    
    /* once the program contains the shaders they are no longer needed */
    glDeleteShader( vertex_shader_id );
    glDeleteShader( fragment_shader_id );
    
    delete [] vertex_shader_source;
    delete [] fragment_shader_source;
    
    return program_id;
}

GLuint antShader::createShaderProgram( const std::string & vertex_shader,
                                      const std::string & geometry_shader,
                                      const std::string & fragment_shader )
{
    GLuint vertex_shader_id;
    GLuint geometry_shader_id;
    GLuint fragment_shader_id;
    GLuint program_id;
    
    const GLchar * vertex_shader_source = readFile( vertex_shader );
    const GLchar * geometry_shader_source = readFile( geometry_shader );
    const GLchar * fragment_shader_source = readFile( fragment_shader );
    
    vertex_shader_id = glCreateShader( GL_VERTEX_SHADER );
    geometry_shader_id = glCreateShader( GL_GEOMETRY_SHADER );
    fragment_shader_id = glCreateShader( GL_FRAGMENT_SHADER );
    
    // id, number = 1, source, length = NULL
    glShaderSource( vertex_shader_id, 1, &vertex_shader_source, NULL );
    glShaderSource( geometry_shader_id, 1, &geometry_shader_source, NULL );
    glShaderSource( fragment_shader_id, 1, &fragment_shader_source, NULL );
    
    glCompileShader( vertex_shader_id );
    int compiled = -1;
    glGetShaderiv( vertex_shader_id, GL_COMPILE_STATUS, &compiled );
    if ( GL_TRUE != compiled )
    {
        std::cerr << "ERROR : antShader::createShaderProgram() glCompileShader() vertex" << std::endl;
        return -1;
    }
    
    glCompileShader( geometry_shader_id );
    glGetShaderiv( geometry_shader_id, GL_COMPILE_STATUS, &compiled );
    if ( GL_TRUE != compiled )
    {
        std::cerr << "ERROR : antShader::createShaderProgram() glCompileShader() geometry " << std::endl;
        return -1;
    }
    
    glCompileShader( fragment_shader_id );
    glGetShaderiv( fragment_shader_id, GL_COMPILE_STATUS, &compiled );
    if ( GL_TRUE != compiled )
    {
        std::cerr << "ERROR : antShader::createShaderProgram() glCompileShader() fragment " << std::endl;
        return -1;
    }
    
    program_id = glCreateProgram();
    glAttachShader( program_id, fragment_shader_id );
    glAttachShader( program_id, geometry_shader_id );
    glAttachShader( program_id, vertex_shader_id );

    glLinkProgram( program_id );
    
    glGetProgramiv (program_id, GL_LINK_STATUS, &compiled);
    if (GL_TRUE != compiled)
    {
        std::cerr << "ERROR : antShader::createShaderProgram() glCompileShader() link " << std::endl;
        return -1;
    }
    
    /* once the program contains the shaders they are no longer needed */
    glDeleteShader( vertex_shader_id );
    glDeleteShader( geometry_shader_id );
    glDeleteShader( fragment_shader_id );
    
    delete [] vertex_shader_source;
    delete [] geometry_shader_source;
    delete [] fragment_shader_source;
    
    return program_id;
}

GLchar * antShader::readFile( const std::string & file_path )
{
    GLchar * source;
    
    FILE * file = fopen( file_path.c_str(), "rt" );
    
    if ( file != NULL )
    {
        fseek( file, 0, SEEK_END );
        size_t count = size_t( ftell( file ) );
        rewind( file );
        
        if ( count > 0 )
        {
            source = ( GLchar * ) malloc ( sizeof( GLchar ) * ( count + 1) );
            count = fread( source, sizeof( GLchar ), count, file );
            source[count] = '\0';
        }
        
        fclose( file );
    }
    
    return source;
}
