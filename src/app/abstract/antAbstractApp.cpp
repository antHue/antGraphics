//
//  antAbstractApp.cpp
//  ant_graphics
//
//  Created by anthonycouret on 05/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antAbstractApp.h"

antAbstractApp::antAbstractApp( int window_width, int window_height, const std::string & window_title )
{
        m_mouse_x_pos = 0.;
        m_mouse_y_pos = 0.;
        m_time = 0.;
        m_frame_count = 0.;
        m_fps =  0.;
        m_window_shptr = antWindow::create( window_width, window_height, window_title );
}

double antAbstractApp::getCurrentTime()
{
    return glfwGetTime();
}

int antAbstractApp::updateFPSCounter()
{
    double current_time = glfwGetTime();
    double elapsed_time = current_time - m_time;
    if ( elapsed_time > 0.25 )
    {
        m_time = current_time;
        m_fps = double( m_frame_count ) / elapsed_time;
        m_frame_count = 0;
    }
    m_frame_count += 1;
    
    return m_fps;
}

void antAbstractApp::run()
{
    start();
    
    while ( !glfwWindowShouldClose( m_window_shptr->getWindow() ) )
    {
        updateFPSCounter();
        
        m_window_shptr->viewport();
        
        /* render here */
        
        /* !!! set m_time (updated every 25ms -> see updateFPS() )if no accurary needed by render()*/
        update();
                
        draw();
        
        m_window_shptr->swapAndPoll();
        m_window_shptr->updateKeyMouse( &m_mouse_x_pos, &m_mouse_y_pos );
    }
}

antAbstractApp::~antAbstractApp()
{
    m_window_shptr.reset();
}