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
    
    _texture1.textureUnit = 0;
    _texture1.loadTexture(filename.data());
    
    _texture2.textureUnit = 1;
    _texture2.loadTexture("resource/textures/awesomeface.png");
    
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
    
    _shader.setInt("uTexture0", _texture1.textureUnit);
    _shader.setInt("uTexture1", _texture2.textureUnit);
}

CubeRender::~CubeRender()
{
    
}

void CubeRender::draw(Camera& camera, Application* app)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)app->width / (float)app->heigth, 0.1f, 100.0f);
    
    model = glm::translate(model, glm::vec3(_pos));
    
    _shader.setMat4("model", model);
    _shader.setMat4("view", view);
    _shader.setMat4("projection", projection);
    
    _model.bindVAO();
    
    _texture1.bindTexture();
    _texture2.bindTexture();
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
}
