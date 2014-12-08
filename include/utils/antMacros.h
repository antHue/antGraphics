//
//  antMacros.h
//  ant_graphics
//
//  Created by anthonycouret on 26/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef ant_graphics_antMacros_h
#define ant_graphics_antMacros_h

//------------------------------------------------------------------------------

#ifndef N_VERTEX_ATTRIBS
    #define N_VERTEX_ATTRIBS 3
#endif

#ifndef N_COLOR_ATTRIBS
    #define N_COLOR_ATTRIBS 4
#endif

#ifndef N_NORMAL_ATTRIBS
    #define N_NORMAL_ATTRIBS 3
#endif

#ifndef N_TEXCOORDS_ATTRIBS
    #define N_TEXCOORDS_ATTRIBS 2
#endif

//------------------------------------------------------------------------------

#ifndef ATTR_POSITION_LOC
    #define ATTR_POSITION_LOC 0
    #define ATTR_POSITION_STR "attr_position"
#endif

#ifndef ATTR_COLOR_LOC
    #define ATTR_COLOR_LOC 1
    #define ATTR_COLOR_STR "attr_color"
#endif

#ifndef ATTR_NORMAL_LOC
    #define ATTR_NORMAL_LOC 2
    #define ATTR_NORMAL_STR "attr_normal"
#endif

#ifndef ATTR_TEX_COORD_LOC
    #define ATTR_TEX_COORD_LOC 3
    #define ATTR_TEX_COORD_STR "attr_tex"
#endif

#ifndef ANT_VERTEX_ATTRIB 
    #define ANT_VERTEX_ATTRIB
    #define ATTR_POSITION ATTR_POSITION_LOC
    #define ATTR_COLOR ATTR_COLOR_LOC
    #define ATTR_NORMAL ATTR_NORMAL_LOC
    #define ATTR_TEX_COORD ATTR_TEX_COORD_LOC
#endif

#endif
