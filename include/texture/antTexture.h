//
//  antTexture.h
//  ant_graphics
//
//  Created by anthonycouret on 23/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antTexture__
#define __ant_graphics__antTexture__

#include <iostream>
#include <string>
#include <memory>

#include "stb_image.h"


class antTexture;
typedef std::shared_ptr<antTexture> antTextureShPtr;
typedef std::weak_ptr<antTexture> antTextureWkPtr;

class antTexture
{
    public :
    
    static antTextureShPtr create();
    ~antTexture();
    
    bool loadTextureFromFile( const std::string & texture_file );
    
    int getWidth();
    int getHeight();
    
    const unsigned char * getData();
    
    private :
    
    int m_width;
    int m_height;
    int m_nChannels;
    int m_nReqChannels;
    
    unsigned char * m_texture_data;
        
    antTexture();
    antTextureWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antTexture__) */
