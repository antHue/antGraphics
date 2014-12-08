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

class antConfiguration;
typedef std::shared_ptr<antConfiguration> antConfigurationShPtr;
typedef std::weak_ptr<antConfiguration> antConfigurationWkPtr;

typedef enum { SELF = 0, ORBIT = 1 } antRotationType;

class antConfiguration
{
    public :
    
    //--------------------------------------------------------------------------
    /** create
     \brief static method to create an antConfiguration shared pointer
     
     \param type        SELF (default) or ORBIT
     
     \return an antConfiguration shared pointer
     */
    static antConfigurationShPtr create( antRotationType type = SELF );
    
    
    //--------------------------------------------------------------------------
    /** create
     \brief static method to create an antConfiguration shared pointer
     
     \param position    position vector
     \param type        SELF (default) or ORBIT
     
     \return an antConfiguration shared pointer
     */
    static antConfigurationShPtr create
    ( const antVec3 & position, antRotationType type = SELF );
    
    
    //--------------------------------------------------------------------------
    /** create
     \brief static method to create an antConfiguration shared pointer
     
     \param position    position vector
     \param rotation    rotation versor
     \param type        SELF (default) or ORBIT
     
     \return an antConfiguration shared pointer
     */
    static antConfigurationShPtr create
    ( const antVec3 & position, const antQuat & rotation, antRotationType type = SELF );
    

    //--------------------------------------------------------------------------
    /** ~antConfiguration
     \brief destructor
     */
    ~antConfiguration();
    

    //--------------------------------------------------------------------------
    /** setPosition
     \brief position setter
     
     \param position position vector
     */
    void setPosition( antVec3 position );
    
    
    //--------------------------------------------------------------------------
    /** setRotation
     \brief rotation setter
     
     \param rotation rotation versor
     */
    void setRotation( antQuat rotation );
    
    
    //--------------------------------------------------------------------------
    /** setScale
     \brief scale setter
     
     \param scale scale factor
     */
    void setScale( float scale );

    
    //--------------------------------------------------------------------------
    /** setType
     \brief type setter
     
     \param type SELF or ORBIT
     */
    void setType( antRotationType type );
    
    
    //--------------------------------------------------------------------------
    /** getPosition
     \brief position getter
     
     \return position vector
     */
    antVec3 getPosition();
    
    
    //--------------------------------------------------------------------------
    /** getRotation
     \brief rotation getter
     
     \return rotation versor
     */
    antQuat getRotation();
    
    
    //--------------------------------------------------------------------------
    /** getLocalToWorldMatrix
     \brief transform, rotate and scale identity matrix
     
     \return local to world matrix
     */
    antMat4 getLocalToWorldMatrix();
    
    
    //--------------------------------------------------------------------------
    /** getWorldToOriginMatrix
     \brief inverse transform and rotate, then scale identity matrix
     
     \return world to origin matrix
     */
    antMat4 getWorldToOriginMatrix();

    
    private :
    
    /** rotation and transformation type */
    antRotationType m_type;
    
    /** position vector */
    antVec3 m_position;
    
    /** rotation versor */
    antQuat m_rotation;
    
    /** scale factor */
    float m_scale;
    
    //--------------------------------------------------------------------------
    /** antConfiguration
     \brief constructor
     
     \param type        SELF or ORBIT
     */
    antConfiguration( antRotationType type );
    
    
    //--------------------------------------------------------------------------
    /** antConfiguration
     \brief constructor
     
     \param position    position vector
     \param type        SELF or ORBIT
     */
    antConfiguration( const antVec3 & position, antRotationType type );
    
    
    //--------------------------------------------------------------------------
    /** antConfiguration
     \brief constructor
     
     \param position    position vector
     \param rotation    rotation versor
     \param type        SELF or ORBIT
     */
    antConfiguration( const antVec3 & position, const antQuat & rotation, antRotationType type );
    

    /** weak pointer */
    antConfigurationWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antConfiguration__) */
