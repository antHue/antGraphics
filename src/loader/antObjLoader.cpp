//
//  antObjLoader.cpp
//  ant_graphics
//
//  Created by anthonycouret on 22/11/2014.
//  Copyright (c) 2014 ac. All rights reserved.
//

#include "antObjLoader.h"

antObjLoaderShPtr antObjLoader::create( const std::string & file_path )
{
    antObjLoaderShPtr ObjLoader_sh_ptr( new antObjLoader( file_path ) );
    ObjLoader_sh_ptr->m_weak_ptr = ObjLoader_sh_ptr;
    return ObjLoader_sh_ptr;
}

antObjLoader::antObjLoader( const std::string & file_path )
{
    m_loaded = false;
    
    Assimp::Importer importer;
    
    /* removed */
    importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
                                aiComponent_COLORS
//                                | aiComponent_TANGENTS_AND_BITANGENTS
                                | aiComponent_BONEWEIGHTS
                                | aiComponent_ANIMATIONS
                                | aiComponent_TEXTURES
                                | aiComponent_LIGHTS
                                | aiComponent_CAMERAS);
    
    m_scene = aiImportFile( file_path.c_str(),
//                                aiProcess_Triangulate
//                                | aiProcess_JoinIdenticalVertices
                                 aiProcess_RemoveComponent
                                |aiProcess_GenNormals
                                | aiProcess_CalcTangentSpace
                                |aiProcess_PreTransformVertices
//                                  | aiProcess_GenUVCoords
//                                  | aiProcess_MakeLeftHanded
                                );
    
    if ( !m_scene )
    {
        std::cerr << "ERROR : antObjLoader::antObjLoader() aiImportFile()" << std::endl;
        exit( EXIT_FAILURE );
    }
    
    if ( m_scene->mNumMeshes > 0 )
    {
        m_mesh = m_scene->mMeshes[0];
        m_nVertices = m_mesh->mNumVertices;
        m_loaded = true;
    }
    else
    {
        std::cerr << "ERROR : antObjLoader::antObjLoader() aiImportFile()" << std::endl;
        exit( EXIT_FAILURE );
    }    
}

bool antObjLoader::hasVertices() { return m_mesh->HasPositions(); }
bool antObjLoader::hasColors() { return m_mesh->HasVertexColors(0); }
bool antObjLoader::hasTexCoords() { return m_mesh->HasTextureCoords(0); }
bool antObjLoader::hasNormals() { return m_mesh->HasNormals(); }


antObjLoader::~antObjLoader()
{
    delete m_mesh;
    m_weak_ptr.reset();
}

bool antObjLoader::loadVertices( GLfloat * vertices )
{
    if ( m_loaded && m_mesh->HasPositions() )
    {
        for ( int i = 0; i < m_nVertices; i++ )
        {
            const aiVector3D * v = &( m_mesh->mVertices[i] );
            vertices[ i * 3] = (GLfloat)v->x;
            vertices[ i * 3 + 1] = (GLfloat)v->y;
            vertices[ i * 3 + 2] = (GLfloat)v->z;
        }
        return true;
    }
    return false;
}

bool antObjLoader::loadColors( GLfloat * colors )
{
    if ( m_loaded && m_mesh->HasVertexColors( 0 ) )
    {
        for ( int i = 0; i < m_nVertices; i++ )
        {
            const aiColor4D * c = &( m_mesh->mColors[0][i] );
            colors[ i * 4] = (GLfloat)c->r;
            colors[ i * 4 + 1] = (GLfloat)c->g;
            colors[ i * 4 + 2] = (GLfloat)c->b;
            colors[ i * 4 + 3] = (GLfloat)c->a;
            
        }
        return true;
    }
    return false;
}

bool antObjLoader::loadNormals( GLfloat * normals )
{
    if ( m_loaded && m_mesh->HasNormals() )
    {
        for ( int i = 0; i < m_nVertices; i++ )
        {
            const aiVector3D * n = &( m_mesh->mNormals[i] );
            normals[ i * 3] = (GLfloat)n->x;
            normals[ i * 3 + 1] = (GLfloat)n->y;
            normals[ i * 3 + 2] = (GLfloat)n->z;
        }
        return true;
    }
    return false;
}

bool antObjLoader::loadTexCoords( GLfloat * texcoords )
{
    if ( m_loaded && m_mesh->HasTextureCoords( 0 ) )
    {
        for ( int i = 0; i < m_nVertices; i++ )
        {
            const aiVector3D * vn = &( m_mesh->mTextureCoords[0][i] );
            texcoords[ i * 2] = (GLfloat)vn->x;
            texcoords[ i * 2 + 1] = (GLfloat)vn->y;
        }
        return true;
    }
    return false;
}