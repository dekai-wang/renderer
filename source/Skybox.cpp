//
//  Skybox.cpp
//  renderer
//
//  Created by MrMac on 2020/6/16.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include "Skybox.hpp"

#include "stb_image.h"

Skybox::Skybox() {
    _size = 500.0f;
}

Skybox::~Skybox() {
    
}

void Skybox::init() {
    float skyboxVertices[] = {
        // positions
        -_size,  _size, -_size,
        -_size, -_size, -_size,
         _size, -_size, -_size,
         _size, -_size, -_size,
         _size,  _size, -_size,
        -_size,  _size, -_size,

        -_size, -_size,  _size,
        -_size, -_size, -_size,
        -_size,  _size, -_size,
        -_size,  _size, -_size,
        -_size,  _size,  _size,
        -_size, -_size,  _size,

         _size, -_size, -_size,
         _size, -_size,  _size,
         _size,  _size,  _size,
         _size,  _size,  _size,
         _size,  _size, -_size,
         _size, -_size, -_size,

        -_size, -_size,  _size,
        -_size,  _size,  _size,
         _size,  _size,  _size,
         _size,  _size,  _size,
         _size, -_size,  _size,
        -_size, -_size,  _size,

        -_size,  _size, -_size,
         _size,  _size, -_size,
         _size,  _size,  _size,
         _size,  _size,  _size,
        -_size,  _size,  _size,
        -_size,  _size, -_size,

        -_size, -_size, -_size,
        -_size, -_size,  _size,
         _size, -_size, -_size,
         _size, -_size, -_size,
        -_size, -_size,  _size,
         _size, -_size,  _size
    };
    
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    std::vector<std::string> faces
    {
        "resource/textures/skybox/right.jpg",
        "resource/textures/skybox/left.jpg",
        "resource/textures/skybox/top.jpg",
        "resource/textures/skybox/bottom.jpg",
        "resource/textures/skybox/front.jpg",
        "resource/textures/skybox/back.jpg"
    };
    loadCubemap(faces);
    
    _shader.init("resource/skybox.vert", "resource/skybox.frag");
    _shader.setInt("skybox", 0);
}

void Skybox::draw(Camera& camera, Application* app) {
    glDepthFunc(GL_LEQUAL);
    
    _shader.useProgram();
    glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)app->width / (float)app->heigth, 0.1f, 100.0f);
    _shader.setMat4("view", view);
    _shader.setMat4("projection", projection);

    glBindVertexArray(_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    glDepthFunc(GL_LESS);
}

void Skybox::loadCubemap(std::vector<std::string> faces) {
    glGenTextures(1, &_cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}
