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
#include "antTypes.h"
#include "antAbstractConfiguration.h"

class antConfiguration;
typedef std::shared_ptr<antConfiguration> antConfigurationShPtr;
typedef std::weak_ptr<antConfiguration> antConfigurationWkPtr;

class antConfiguration : public antAbstractConfiguration
{
    public :
    
    //--------------------------------------------------------------------------
    /**
     \brief static method to create an antConfiguration shared pointer
     \param type SELF (default) or ORBIT
     \return an antConfiguration shared pointer
     */
    static antConfigurationShPtr create( antRotationType type = SELF );
        
    //--------------------------------------------------------------------------
    /**
     \brief constructor
     \param type SELF or ORBIT
     */
    antConfiguration( antRotationType type );
    
    //--------------------------------------------------------------------------
    /**
     \brief destructor
     */
    virtual ~antConfiguration();
    
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
     \return position vector
     */
    antVec3 getPosition();
    
    //--------------------------------------------------------------------------
    /**
     \brief rotation getter
     \return rotation versor
     */
    antQuat getRotation();
    
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
     \brief make a return a mapable configuration shared pointer from this
     \return an antAbstractConfiguration mapable implementation shared pointer
     */
    antAbstractConfigurationShPtr makeMapable();
    
    private :
    
    /** rotation and transformation type */
    antRotationType m_type;
    
    /** position vector */
    antVec3 m_position;
    
    /** rotation versor */
    antQuat m_rotation;
    
    /** scale factor */
    float m_scale;

    /** weak pointer */
    antConfigurationWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antConfiguration__) */
