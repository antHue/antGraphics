//
//  antAbtractPrimitive.h
//  ant_graphics
//
//  Created by anthonycouret on 07/12/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antAbtractPrimitive__
#define __ant_graphics__antAbtractPrimitive__

#include <memory>
#include <iostream>

#include "antTypes.h"

class antAbtractPrimitive;
typedef std::shared_ptr<antAbtractPrimitive> antAbtractPrimitiveShPtr;
typedef std::weak_ptr<antAbtractPrimitive> antAbtractPrimitiveWkPtr;

class antAbtractPrimitive
{
    public :
    
    ~antAbtractPrimitive();
    
    private :
    
    antAbtractPrimitive();
};

#endif /* defined(__ant_graphics__antAbtractPrimitive__) */
