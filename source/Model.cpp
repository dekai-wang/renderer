//
//  Model.cpp
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include "Model.hpp"


Model::Model()
{
    
}

Model::~Model()
{
    
}

void Model::init()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
}

void Model::clean()
{
    glDeleteVertexArrays(1, &_vao);
    
    if (_vecVbo.size())
    {
       glDeleteBuffers(static_cast<GLsizei>(_vecVbo.size()), _vecVbo.data());
    }
}

void Model::bindVAO()
{
    glBindVertexArray(_vao);
}

void Model::genVBO(GLuint index, GLint size, const std::vector<GLfloat> &data)
{

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(index);

    _vecVbo.push_back(vbo);
}

void Model::genEBO(const std::vector<GLuint> &indices)
{
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
}
