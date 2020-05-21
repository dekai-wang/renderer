//
//  CubeRender.cpp
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include "CubeRender.hpp"

CubeRender::CubeRender(glm::vec3 pos)
{
    _pos = pos;
    _shader.init("resource/camera.vert", "resource/camera.frag");
    
    GLfloat vertices[] = {
       -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
       -0.5f,  0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,

       -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
       -0.5f, -0.5f,  0.5f,

       -0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

       -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f, -0.5f,

       -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f, -0.5f
    };
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    Mesh mesh;
    for (size_t i = 0; i < sizeof(vertices) / sizeof(GLfloat); i++) {
        mesh.verticesPosition.push_back(vertices[i]);
    }
    for (size_t i = 0; i < sizeof(indices) / sizeof(GLuint); i++) {
        mesh.indices.push_back(indices[i]);
    }
    
    _model.init(mesh);
}

CubeRender::~CubeRender()
{
    
}

void CubeRender::render(Camera& camera, Application* app)
{
    _shader.useProgram();
    
    glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    
    projection = glm::perspective(glm::radians(camera.Zoom), (float)app->width / (float)app->heigth, 0.1f, 100.0f);
    view = camera.GetViewMatrix();
    model = glm::translate(model, glm::vec3(_pos));
    
    _shader.setMat4("model", model);
    _shader.setMat4("view", view);
    _shader.setMat4("projection", projection);
    
    _model.bindVAO();
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
}
