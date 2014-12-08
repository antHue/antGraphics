//
//  antWindow.h
//  ant_graphics
//
//  Created by anthonycouret on 21/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antWindow__
#define __ant_graphics__antWindow__

#include <iostream>
#include <memory>

#include "GLFW/glfw3.h"
#include <OpenGL/gl3.h>

/* SMART POINTER */
class antWindow;
typedef std::shared_ptr<antWindow> antWindowShPtr;
typedef std::weak_ptr<antWindow> antWindowWkPtr;

/** class antWindow
    \brief to define a glfw window with an opengl context
 */
class antWindow
{
    public :
    
    //--------------------------------------------------------------------------
    /** create
        \brief static method to create an antWindow object
     
        \param width       window width
        \param height      window height
        \param title       window title
        \param app_sptr    antAbstractApp implementation shared pointer
     
        \return an antWindow shared pointer
     */
    static antWindowShPtr create
    ( int width, int height, const std::string & title );
    
    //--------------------------------------------------------------------------
    /** render
        \brief render the antWindow object
     */
    GLFWwindow * getWindow();
    
    int getWidth() const;
    int getHeight() const;
    
    //--------------------------------------------------------------------------
    /** updateFPSCOunter
        \brief update the frames per second counter
        
        \param window_ptr a 
     
     */
    void updateFPSCounter( void );
    
    void swapAndPoll( void );
    
    void updateKeyMouse( double * m_mouse_x_pos, double * m_mouse_y_pos );
    
    void viewport();
    
    //--------------------------------------------------------------------------
    /** printWiwdowStatus
     \brief stream out informations about the antWindow object
     */
    void printWindowStatus( void );

    //--------------------------------------------------------------------------
    /** ~antWndow
     \brief destructor
     */
    ~antWindow();
    
private :
    
    //--------------------------------------------------------------------------
    /** antWindow
     \brief constructor
     
     \param width       window width
     \param height      window height
     \param title       window title
     \param app_sptr    antAbstractApp implementation shared pointer
     */
    antWindow( int width, int height, const std::string & title );
    
    //--------------------------------------------------------------------------
    void init();
    
    /** weak pointer */
    antWindowWkPtr m_weak_ptr;
    
    /** glfw window pointer */
    GLFWwindow * m_window_ptr;
    
    /** window title */
    std::string m_title;
    
    /** window width */
    int m_width;
    
    /** window height */
    int m_height;
    
};
#endif /* defined(__ant_graphics__antWindow__) */
