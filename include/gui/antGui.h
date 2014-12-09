//
//  antGui.h
//  ant_graphics
//
//  Created by anthonycouret on 05/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antGui__
#define __ant_graphics__antGui__

#include <memory>
#include <iostream>

//#include "antDrawable.h"
#include "antWindow.h"
#include <AntTweakBar.h>
#include "GLFW/glfw3.h"
#include <string>
#include <vector>
#include "antGuiDef.h"
#include "antTypes.h"

class antGui;
typedef std::shared_ptr<antGui> antGuiShPtr;
typedef std::weak_ptr<antGui> antGuiWkPtr;

class antGui /*: public antDrawable*/
{
    public :
    
    static antGuiShPtr create( antWindowShPtr window );
    ~antGui();
    
    void draw();
    
    int addBar( const std::string & name );
    
    void addFloatVarRW( int bar_id, const std::string & name, float * var );
    void addRGBAVarRW( int bar_id, const std::string & name, antRGBA * var );
    void addQuatVarRW( int bar_id, const std::string & name, antVec4 * var );
    void addVec3VarRW( int bar_id, const std::string & name, antVec3 * var );
    void addToggleRW( int bar_id, const std::string & name, bool * var );
    void addRotTypeRW( int bar_id, const std::string & name, antRotationType * type );

    
    void defVarShortCut
    ( int bar_id, const std::string & name, const std::string & incrKey, const std::string & decrKey );

    inline static void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods)
    {TwEventMouseButtonGLFW(button, action);}
    inline static void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos)
    {TwMouseMotion(int(xpos), int(ypos));}
    inline static void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset)
    {TwEventMouseWheelGLFW(yoffset);}
    inline static void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods)
    {TwEventKeyGLFW(key, action);}
    inline static void TwEventCharGLFW3(GLFWwindow* window, int codepoint)
    {TwEventCharGLFW(codepoint, GLFW_PRESS);}
    inline static void TwWindowSizeGLFW3(GLFWwindow* window, int width, int height)
    {TwWindowSize(width, height);}
    
    private :
    
    int m_bars_count;
    std::vector<TwBar *> m_ant_bars;
    std::vector<std::string> m_bar_names;
    
    antGui( antWindowShPtr window );
    antGuiWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antGui__) */
