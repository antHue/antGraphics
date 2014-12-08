//
//  antWindow.cpp
//  ant_graphics
//
//  Created by anthonycouret on 21/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antWindow.h"

//------------------------------------------------------------------------------
antWindowShPtr antWindow::create
( int width, int height, const std::string & title )
{
    antWindowShPtr window_sh_ptr( new antWindow( width, height, title ) );
    window_sh_ptr->m_weak_ptr = window_sh_ptr;
    return window_sh_ptr;
}

//------------------------------------------------------------------------------
antWindow::antWindow
( int width, int height, const std::string & title ) :
m_width( width ),
m_height( height ),
m_title( title )
{ init(); }

//------------------------------------------------------------------------------
void antWindow::init()
{
    //  init gl context and window i/o
    if ( ! glfwInit() )
    {
        std::cerr << "ERROR : antWindow::antWindow() glfwInit()" << std::endl;
        exit( EXIT_FAILURE );
    }
    
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    
    //  anti-aliasing
    glfwWindowHint( GLFW_SAMPLES, 4 );
    
    m_window_ptr = glfwCreateWindow( m_width, m_height, m_title.c_str(), NULL, NULL );
    
    if ( ! m_window_ptr )
    {
        std::cerr << "ERROR : antWindow::antWindow() glfwCreateWindow()" << std::endl;
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    
    glfwMakeContextCurrent( m_window_ptr );
    
    /* enable depth-testing */
    glEnable( GL_DEPTH_TEST );
    
    /* interpret smaller values as closers */
    glDepthFunc( GL_LESS );
}

//------------------------------------------------------------------------------
antWindow::~antWindow()
{
    glfwTerminate();
    glfwDestroyWindow( m_window_ptr );
    m_weak_ptr.reset();
}

//------------------------------------------------------------------------------
GLFWwindow * antWindow::getWindow()
{
    return m_window_ptr;
}

//------------------------------------------------------------------------------
int antWindow::getWidth() const
{
    return m_width;
}

//------------------------------------------------------------------------------
int antWindow::getHeight() const
{
    return m_height;
}

//------------------------------------------------------------------------------
void antWindow::swapAndPoll( void )
{
    glfwSwapBuffers( m_window_ptr );
    glfwPollEvents();
}

//------------------------------------------------------------------------------
void antWindow::updateKeyMouse( double * m_mouse_x_pos, double * m_mouse_y_pos )
{
    glfwGetCursorPos( m_window_ptr, m_mouse_x_pos, m_mouse_y_pos );
    
    if ( GLFW_PRESS == glfwGetKey( m_window_ptr, GLFW_KEY_ESCAPE ) )
    {
        glfwSetWindowShouldClose( m_window_ptr, 1 );
    }
}

//------------------------------------------------------------------------------
void antWindow::viewport()
{
    glViewport( 0, 0, m_width, m_height );
}

//------------------------------------------------------------------------------
void antWindow::printWindowStatus( void )
{
    const GLubyte * renderer = glGetString(GL_RENDERER);
    const GLubyte * supperted_version = glGetString(GL_VERSION);
    int gl_major_version; glGetIntegerv( GL_MAJOR_VERSION, &gl_major_version );
    int gl_minor_version; glGetIntegerv( GL_MINOR_VERSION, &gl_minor_version );

    std::cout << "------------------------" << std::endl;
    std::cout << "OpenGL renderer : " << renderer << std::endl;
    std::cout << "supported version : " << supperted_version << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "OpenGL version : " << gl_major_version << "." << gl_minor_version << std::endl;
    std::cout << "Window created : " << m_width << "x" << m_height << std::endl;
    std::cout << "------------------------" << std::endl;
}
