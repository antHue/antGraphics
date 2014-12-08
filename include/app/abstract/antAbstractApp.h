//
//  antAbstractApp.h
//  ant_graphics
//
//  Created by anthonycouret on 05/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antAbstractApp__
#define __ant_graphics__antAbstractApp__

#include <memory>
#include <iostream>
#include "GLFW/glfw3.h"
#include "antWindow.h"

class antAbstractApp;
typedef std::shared_ptr<antAbstractApp> antAbstractAppShPtr;
typedef std::weak_ptr<antAbstractApp> antAbstractAppWkPtr;

/** class antAbstractApp 
 \brief abstract class for app definition 
 */
class antAbstractApp
{
    public :
    
    //--------------------------------------------------------------------------
    /** ~antAbstractApp
     \brief destructor
     */
    ~antAbstractApp();
    
    //--------------------------------------------------------------------------
    /** start
     \brief start app virtual method to init the app
     */
    virtual void start() = 0;
    
    //--------------------------------------------------------------------------
    /** update
     \brief update app virtual method to update app attributes
     */
    virtual void update() = 0;
    
    //--------------------------------------------------------------------------
    /** draw
     \brief draw virtual method to render the app
     */
    virtual void draw() = 0;
    
    //--------------------------------------------------------------------------
    /** shutdown
     \brief shutdown virtual method to clean the app
     */
    virtual void shutdown() = 0;
    
    //--------------------------------------------------------------------------
    /** getCurrentTime
     \return GLFW window time
     */
    double getCurrentTime();
    
    protected :
    
    /** window */
    antWindowShPtr m_window_shptr;
    
    /** current mouse x position */
    double m_mouse_x_pos;
    
    /** current mouse y position */
    double m_mouse_y_pos;
    
    /** current frame count */
    int m_frame_count;
    
    /** current frame per seconds */
    int m_fps;
    
    /** current time in seconds, updated each 0.25s */
    double m_time;
    
    //--------------------------------------------------------------------------
    /** antAbstractApp
     \brief constructor
     
     \param window_width    window width
     \param window_height   window height
     \param window_title    window title
     */
    antAbstractApp( int window_width, int window_height, const std::string & window_title );
    
    //--------------------------------------------------------------------------
    /** run
     \brief run the app
     */
    void run();
    
    private :
    
    //--------------------------------------------------------------------------
    /** updateFPSCounter
     \brief update frame attributes
     
     \return current frame count
     */
    int updateFPSCounter();

};

#endif /* defined(__ant_graphics__antAbstractApp__) */
