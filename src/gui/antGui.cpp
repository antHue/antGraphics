//
//  antGui.cpp
//  ant_graphics
//
//  Created by anthonycouret on 05/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antGui.h"

antGuiShPtr antGui::create( antWindowShPtr window )
{
    antGuiShPtr antGui_sh_ptr( new antGui( window ) );
    antGui_sh_ptr->m_weak_ptr = antGui_sh_ptr;
    return antGui_sh_ptr;
}

antGui::antGui( antWindowShPtr window )
{
    /* init AntTweakBar */
    m_bars_count = 0;
    TwInit( TW_OPENGL_CORE, NULL );
    TwWindowSize( window->getWidth(), window->getHeight() );
    
    glfwSetWindowSizeCallback( window->getWindow(), (GLFWwindowposfun)TwWindowSizeGLFW3 );
    glfwSetMouseButtonCallback(window->getWindow(), (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
    glfwSetCursorPosCallback(window->getWindow(), (GLFWcursorposfun)TwEventMousePosGLFW3);
    glfwSetScrollCallback(window->getWindow(), (GLFWscrollfun)TwEventMouseWheelGLFW3);
    glfwSetKeyCallback(window->getWindow(), (GLFWkeyfun)TwEventKeyGLFW3);
    glfwSetCharCallback(window->getWindow(), (GLFWcharfun)TwEventCharGLFW3);
    
//    // Set GLFW event callbacks
//    // - Redirect window size changes to the callback function WindowSizeCB
//    //glfwSetWindowSizeCallback(WindowSizeCB);
//    // - Directly redirect GLFW mouse button events to AntTweakBar
//    glfwSetMouseButtonCallback( window->getWindow(), (GLFWmousebuttonfun)TwEventMouseButtonGLFW );
//    // - Directly redirect GLFW mouse position events to AntTweakBar
//    glfwSetCursorPosCallback( window->getWindow(), (GLFWcursorposfun)TwEventMousePosGLFW );
//    glfwSetScrollCallback( window->getWindow(), (GLFWscrollfun) TwEventMouseWheelGLFW );
//
////    glfwSetMousePosCallback((GLFWmouseposfun)TwEventMousePosGLFW);
////    // - Directly redirect GLFW mouse wheel events to AntTweakBar
////    glfwSetMouseWheelCallback((GLFWmousewheelfun)TwEventMouseWheelGLFW);
////    // - Directly redirect GLFW key events to AntTweakBar
//    glfwSetKeyCallback( window->getWindow(), (GLFWkeyfun)TwEventKeyGLFW );
////    glfwSetKeyCallback((GLFWkeyfun)TwEventKeyGLFW);
////    // - Directly redirect GLFW char events to AntTweakBar
////    glfwSetCharCallback((GLFWcharfun)TwEventCharGLFW);
//    glfwSetCharCallback( window->getWindow(), (GLFWcharfun)TwEventCharGLFW );
}

int antGui::addBar( const std::string & name )
{
    m_ant_bars.push_back( TwNewBar( name.c_str() ) );
    m_bar_names.push_back( name );
    
    TwDefine( ( name + " color='0 0 255' alpha=255 ").c_str() );
    TwDefine( ( name + " text=light").c_str() );
    
    return ( m_bars_count++ );
}

void antGui::addFloatVarRW( int bar_id, const std::string & name, float * var )
{
    TwAddVarRW( m_ant_bars[bar_id], name.c_str(), TW_TYPE_FLOAT, var,
               ( " label=" + name + " " ).c_str() );
}


void antGui::addRGBAVarRW( int bar_id, const std::string & name, antRGBA * var )
{
    std::string ext_name[4] = { "r", "g", "b", "a" };
    
    for ( int i = 0; i < 4; i++ )
    {
        TwAddVarRW( m_ant_bars[bar_id], ( name + "_" + ext_name[i] ).c_str(),
                    TW_TYPE_FLOAT, &(var->v[i]), ( "group=" + name ).c_str() );
        
        TwDefine((" " + m_bar_names[bar_id] + "/" + name + "_" + ext_name[i] + " min=0 max=1 " ).c_str() );
        TwDefine((" " + m_bar_names[bar_id] + "/" + name + "_" + ext_name[i] + " precision=2 " ).c_str() );
        TwDefine((" " + m_bar_names[bar_id] + "/" + name + "_" + ext_name[i] + " step=0.01 " ).c_str() );
    }
}

void antGui::addQuatVarRW( int bar_id, const std::string & name, antVec4 * var )
{
    TwAddVarRW( m_ant_bars[bar_id], name.c_str(), TW_TYPE_QUAT4F, &(var->v),
               ( " label=" + name + " " ).c_str() );
}

void antGui::addVec3VarRW( int bar_id, const std::string & name, antVec3 * var )
{
    TwAddVarRW( m_ant_bars[bar_id], name.c_str(), TW_TYPE_DIR3F, &(var->v),
               ( " label=" + name + " " ).c_str() );
}

void antGui::addToggleRW( int bar_id, const std::string & name, bool * var )
{
    TwAddVarRW( m_ant_bars[bar_id], name.c_str(), TW_TYPE_BOOL8, var,
               ( " label=" + name + " " ).c_str() );
}

void antGui::addRotTypeRW( int bar_id, const std::string & name, antRotationType * type )
{
    std::cout << "NOT DEFINED void antGui::addRotTypeRW( int bar_id, const std::string & name, antRotationType * type )" << std::endl;
}


void antGui::defVarShortCut( int bar_id, const std::string & name, const std::string & incrKey, const std::string & decrKey )
{
    TwDefine( (" " + m_bar_names[bar_id] + "/" + name +
               " keyincr=" + incrKey + " keydecr=" + decrKey + " ").c_str() );
}

void antGui::draw()
{
    TwDraw();
}

antGui::~antGui()
{
    TwTerminate();
    m_weak_ptr.reset();
}