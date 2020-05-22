//
//  CubeRender.cpp
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include "CubeRender.hpp"

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

GLfloat textureCoord[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};

CubeRender::CubeRender(glm::vec3 pos, std::string filename)
{
    _pos = pos;
    
    _shader.init("resource/texture.vert", "resource/texture.frag");
    
    _texture.loadTexture(filename.data());
    
    Mesh mesh;
    for (size_t i = 0; i < sizeof(vertices) / sizeof(GLfloat); i++) {
        mesh.verticesPosition.push_back(vertices[i]);
    }
    for (size_t i = 0; i < sizeof(textureCoord) / sizeof(GLfloat); i++) {
        mesh.verticesTexCoord.push_back(textureCoord[i]);
    }
    for (size_t i = 0; i < sizeof(indices) / sizeof(GLuint); i++) {
        mesh.indices.push_back(indices[i]);
    }
    
    _model.init();
    
    _model.genVBO(_shader.getAttrib("aPosition"), 3, mesh.verticesPosition);
    
    _model.genVBO(_shader.getAttrib("aTexCoord"), 2, mesh.verticesTexCoord);
    
    _model.genEBO(mesh.indices);
    
    _shader.useProgram();
    
    _shader.setInt("uTexture", 0);
}

CubeRender::~CubeRender()
{
    
}

void CubeRender::render(Camera& camera, Application* app)
{
    _texture.bindTexture();
    
    
    
    glm::mat4 model         = glm::mat4(1.0f);
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
