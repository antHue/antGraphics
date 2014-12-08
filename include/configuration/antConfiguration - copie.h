//
//  antConfiguration.h
//  ant_graphics
//
//  Created by anthonycouret on 02/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antConfiguration__
#define __ant_graphics__antConfiguration__

#include <memory>
#include "antMath.h"

class antConfiguration;
typedef std::shared_ptr<antConfiguration> antConfigurationShPtr;
typedef std::weak_ptr<antConfiguration> antConfigurationWkPtr;

typedef enum { SELF = 0, ORBIT = 1 } antRotationType;

class antConfiguration
{
    public :
    
    static antConfigurationShPtr create( antRotationType type = SELF );
    
    static antConfigurationShPtr create( const antVec3 & position,
                                        antRotationType type = SELF );
    
    static antConfigurationShPtr create( const antVec3 & translation, const antVec4 & rotation,
                                        antRotationType type = SELF );
    
    static antConfigurationShPtr create( const antVec4 & translation, const antVec4 & rotation,
                                        antRotationType type = SELF );
        
    ~antConfiguration();
    
    /* MODIFIERS */
    void setPosition( antVec3 position );
    void setPosition( antVec4 position );
    void setPositionX( float x );
    void setPositionY( float y );
    void setPositionZ( float z );
    
    void setTranslation( antVec3 translation );
    void setTranslation( antVec4 translation );
    void setTranslationX( float x );
    void setTranslationY( float y );
    void setTranslationZ( float z );
    
    void translatePos( antVec3 translation );
    void translateAxis( antVec4 translation );
    void translateW( float w );
    void translateX( float x );
    void translateY( float y );
    void translateZ( float z );
    
    void setRotation( antVec4 rotation );
    void setRotationW( float w );
    void setRotationX( float x );
    void setRotationY( float y );
    void setRotationZ( float z );
    
    void rotate( antVec4 rotation );
    void rotateW( float w );
    void rotateX( float x );
    void rotateY( float y );
    void rotateZ( float z );
    
    antMat4 getLocalToWorldMatrix();
    antVec3 getWorldPosition();
    antVec3 getWorldInvPosition();
    antVec4 getLocalRotation();

    private :
    
    antRotationType m_type;
    
    antVec3 m_position;
    
    antMat4 m_local_to_world_matrix;
    
    void updatePosition();
    
    antVec3 m_translation;
    antVec3 m_translation_axis;
    
    antVec4 m_rotation;
    
    antConfiguration( antRotationType type );
    antConfiguration( const antVec3 & position, antRotationType type );
    antConfiguration( const antVec3 & translation, const antVec4 & rotation, antRotationType type );
    antConfiguration( const antVec4 & translation, const antVec4 & rotation, antRotationType type );

    antConfigurationWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antConfiguration__) */
