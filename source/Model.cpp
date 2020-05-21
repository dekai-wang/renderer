//
//  Model.cpp
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include "Model.hpp"


Model::Model()
: _vboCount(0)
, _vao(0)
{
    
}

Model::~Model()
{
    
}

void Model::init(Mesh mesh)
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    _mesh = std::move(mesh);

    if (_mesh.verticesPosition.size())
    {
        genVBO(3, _mesh.verticesPosition);
    }
    
    if (_mesh.verticesTexture.size())
    {
        genVBO(2, _mesh.verticesTexture);
    }
    
    if (_mesh.indices.size())
    {
        genEBO(_mesh.indices);
    }
        
}

void Model::clean()
{
    glDeleteVertexArrays(1, &_vao);
    
    if (_vecVbo.size())
        glDeleteBuffers(static_cast<GLsizei>(_vecVbo.size()), _vecVbo.data());
}

void Model::bindVAO()
{
    glBindVertexArray(_vao);
}

void Model::genVBO(int dimensions, const vector<GLfloat> &data)
{

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(_vboCount, dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(_vboCount);

    _vboCount++;
    _vecVbo.push_back(vbo);
}

void Model::genEBO(const vector<GLuint> &indices)
{
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

unsigned int Model::getIndicesCount()
{
    return static_cast<unsigned int>(_mesh.indices.size());
}
