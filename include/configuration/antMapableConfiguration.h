//
//  antMapableConfiguration.h
//  ant_graphics
//
//  Created by anthonycouret on 02/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antMapableConfiguration__
#define __ant_graphics__antMapableConfiguration__

#include <memory>
#include "antTypes.h"
#include "antAbstractConfiguration.h"

class antBaseConfiguration;

class antMapableConfiguration;
typedef std::shared_ptr<antMapableConfiguration> antMapableConfigurationShPtr;
typedef std::weak_ptr<antMapableConfiguration> antMapableConfigurationWkPtr;

class antMapableConfiguration : public antAbstractConfiguration
{
    public :
    
    //--------------------------------------------------------------------------
    /**
     \brief static method to create an antMapableConfiguration shared pointer
     \param type SELF (default) or ORBIT
     \return an antMapableConfiguration shared pointer
     */
    static antMapableConfigurationShPtr create( antRotationType type = SELF );
    
    //--------------------------------------------------------------------------
    /**
     \brief constructor
     \param type SELF or ORBIT
     */
    antMapableConfiguration( antRotationType type );

    //--------------------------------------------------------------------------
    /**
     \brief destructor
     */
    virtual ~antMapableConfiguration();

    //--------------------------------------------------------------------------
    /**
     \copydoc antAbstractConfiguration::setPosition( antVec3 position )
     */
    virtual void setPosition( antVec3 position );
    
    //--------------------------------------------------------------------------
    /**
     \copydoc antAbstractConfiguration::setRotation( antQuat rotation )
     */
    virtual void setRotation( antQuat rotation );
    
    
    //--------------------------------------------------------------------------
    /**
     \copydoc antAbstractConfiguration::setScale( float scale )
     */
    virtual void setScale( float scale );
    
    //--------------------------------------------------------------------------
    /**
     \copydoc antAbstractConfiguration::setType( antRotationType type )
     */
    virtual void setType( antRotationType type );
    
    //--------------------------------------------------------------------------
    /**
     \brief position getter
     \return position mapable vector
     */

    antMapableVec3 getMapablePosition();
    
    //--------------------------------------------------------------------------
    /**
     \brief rotation getter
     \return rotation mapable versor
     */
    antMapableQuat getMapableRotation();
    
    //--------------------------------------------------------------------------
    /**
     \brief rotation getter
     \return tw rotation mapable versor
     */
    antMapableVec4 getMapableTwRotation();
    
    //--------------------------------------------------------------------------
    /**
     \brief scale getter
     \return sclale mapable value
     */
    antMapableFloat getMapableScale();
    
    //--------------------------------------------------------------------------
    /**
     \brief rotation type getter
     \return rotation type
     */
    antMapableRotType getMapableRotType();
    
    //--------------------------------------------------------------------------
    /**
     \copydoc antAbstractConfiguration::getLocalToWorldMatrix();
     */
    virtual antMat4 getLocalToWorldMatrix();
    
    //--------------------------------------------------------------------------
    /**
     \copydoc antAbstractConfiguration::getWorldToOriginMatrix();
     */
    virtual antMat4 getWorldToOriginMatrix();

    //--------------------------------------------------------------------------
    /**
     \brief make a return a base configuration shared pointer from this
     \return an antAbstractConfiguration base implemnentation shared pointer
     */
    antAbstractConfigurationShPtr makeBase();
    
    private :
    
    /** rotation and transformation type */
    antMapableRotType m_type;
    
    /** position vector */
    antMapableVec3 m_position;
    
    /** rotation versor */
    antMapableQuat m_rotation;
    
    /** tw rotation versor ( w at index 3 ) */
    antMapableVec4 m_tw_rotation;
    
    /** scale factor */
    antMapableFloat m_scale;

    /** weak pointer */
    antMapableConfigurationWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antMapableConfiguration__) */
