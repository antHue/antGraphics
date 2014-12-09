//
//  antAbstractConfiguration.h
//  ant_graphics
//
//  Created by anthonycouret on 02/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antAbstractConfiguration__
#define __ant_graphics__antAbstractConfiguration__

#include <memory>
#include "antTypes.h"

class antAbstractConfiguration;
typedef std::shared_ptr<antAbstractConfiguration> antAbstractConfigurationShPtr;
typedef std::weak_ptr<antAbstractConfiguration> antAbstractConfigurationWkPtr;

class antAbstractConfiguration
{
    protected :
    
    //--------------------------------------------------------------------------
    /**
     \brief constructor
     */
    antAbstractConfiguration() {};
    
    //--------------------------------------------------------------------------
    /**
     \brief destructor
     */
    virtual ~antAbstractConfiguration() {};
    
    public :

    //--------------------------------------------------------------------------
    /**
     \brief position setter
     \param position position vector
     */
    virtual void setPosition( antVec3 position ) = 0;
    
    //--------------------------------------------------------------------------
    /**
     \brief rotation setter
     \param rotation rotation versor
     */
    virtual void setRotation( antQuat rotation ) = 0;
    
    //--------------------------------------------------------------------------
    /**
     \brief scale setter
     \param scale scale factor
     */
    virtual void setScale( float scale ) = 0;
    
    //--------------------------------------------------------------------------
    /**
     \brief type setter
     \param type SELF or ORBIT
     */
    virtual void setType( antRotationType type ) = 0;
    
    //--------------------------------------------------------------------------
    /**
     \brief transform, rotate and scale identity matrix
     \return local to world matrix
     */
    virtual antMat4 getLocalToWorldMatrix() = 0;
    
    //--------------------------------------------------------------------------
    /**
     \brief inverse transform and rotate, then scale identity matrix
     \return world to origin matrix
     */
    virtual antMat4 getWorldToOriginMatrix() = 0;
};

#endif /* defined(__ant_graphics__antAbstractConfiguration__) */
