//
//  antTypes.h
//  ant_graphics
//
//  Created by anthonycouret on 07/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef ant_graphics_antTypes_h
#define ant_graphics_antTypes_h

#include "maths_funcs.h"

#define antVec2 vec2
#define antVec3 vec3
#define antVec4 vec4
#define antMat4 mat4
#define antRGB vec3
#define antRGBA vec4
#define antQuat versor

typedef std::shared_ptr< antRGBA > antMapableRGBA;
typedef std::shared_ptr< float > antMapableFloat;
typedef std::shared_ptr< antQuat > antMapableQuat;
typedef std::shared_ptr< antVec3 > antMapableVec3;
typedef std::shared_ptr< antVec4 > antMapableVec4;

typedef enum { SELF = 0, ORBIT = 1 } antRotationType;

typedef std::shared_ptr< antRotationType > antMapableRotType;


static antQuat TwQuat_to_antQuat( const antVec4 & tw_quat )
{
    antQuat q;
    q.q[0] = tw_quat.v[3];
    q.q[1] = tw_quat.v[0];
    q.q[2] = tw_quat.v[1];
    q.q[3] = tw_quat.v[2];
    return q;
}

static antVec4 antQuat_to_TwQuat( const antQuat & ant_quat )
{
    return antVec4( ant_quat.q[1], ant_quat.q[2], ant_quat.q[3], ant_quat.q[0] );
}


#endif
