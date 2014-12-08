//
//  antTexture.cpp
//  ant_graphics
//
//  Created by anthonycouret on 23/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antTexture.h"


antTextureShPtr antTexture::create()
{
    antTextureShPtr antTexture_sh_ptr( new antTexture() );
    antTexture_sh_ptr->m_weak_ptr = antTexture_sh_ptr;
    return antTexture_sh_ptr;
}

antTexture::antTexture()
{
    m_nReqChannels = 4;
}

antTexture::~antTexture()
{
    delete m_texture_data;
    m_weak_ptr.reset();
}

bool antTexture::loadTextureFromFile( const std::string & texture_file )
{
    m_texture_data = stbi_load( texture_file.c_str(), &m_width, &m_height, &m_nChannels, m_nReqChannels );
    if ( !m_texture_data )
    {
        std::cerr << "ERROR : antTexture::loadTextureFromFile() : " << texture_file << std::endl;
    }
        
    return false;
}

int antTexture::getWidth()
{
    return m_width;
}

int antTexture::getHeight()
{
    return m_height;
}

const unsigned char * antTexture::getData()
{
    return m_texture_data;
}
