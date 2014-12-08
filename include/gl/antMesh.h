//
//  antMesh.h
//  ant_graphics
//
//  Created by anthonycouret on 25/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#ifndef __ant_graphics__antMesh__
#define __ant_graphics__antMesh__

#include <memory>

#include "antMacros.h"
#include "antTypes.h"
#include "antObjLoader.h"
#include "antDrawable.h"

class antMesh;
typedef std::shared_ptr<antMesh> antMeshShPtr;
typedef std::weak_ptr<antMesh> antMeshWkPtr;

class antMesh : public antDrawable
{
    public :
    
    static antMeshShPtr createFromObjFile( const std::string & file_path );
    ~antMesh();
    
    void fill();
    
    private :
    
    antMesh( int nVertices );
    antMeshWkPtr m_weak_ptr;
};

#endif /* defined(__ant_graphics__antMesh__) */
