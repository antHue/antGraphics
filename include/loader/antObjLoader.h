//
//  antObjLoader.h
//  ant_graphics
//
//  Created by anthonycouret on 22/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antObjLoader__
#define __ant_graphics__antObjLoader__

#include <iostream>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>
#include <stdlib.h>

#include <OpenGL/gl3.h>

#include "maths_funcs.h"
#include "antVbo.h"

class antObjLoader;
typedef std::shared_ptr<antObjLoader> antObjLoaderShPtr;
typedef std::weak_ptr<antObjLoader> antObjLoaderWkPtr;

class antObjLoader
{
    public :

    static antObjLoaderShPtr create( const std::string & file_path );
    ~antObjLoader();
    
    bool hasVertices();
    bool hasColors();
    bool hasTexCoords();
    bool hasNormals();
    
    bool loadVertices( GLfloat * vertices );
    bool loadColors( GLfloat * colors );
    bool loadNormals( GLfloat * normals );
    bool loadTexCoords( GLfloat * texcoords );
    
//    bool loadPositions( antVboShPtr vbo, int i );
//    bool loadColors( antVboShPtr vbo, int i );
//    bool loadNormals( antVboShPtr vbo, int i );
//    bool loadTexCoords( antVboShPtr vbo, int i );
    
    const int getNVertices() { return m_nVertices; };

    private :
    
    bool m_loaded;
    const aiScene * m_scene;
    const aiMesh * m_mesh;
    
    int m_nVertices;

    antObjLoader( const std::string & file_path );
    antObjLoaderWkPtr m_weak_ptr;

};



#endif /* defined(__ant_graphics__antObjLoader__) */
