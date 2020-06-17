//
//  Skybox.hpp
//  renderer
//
//  Created by MrMac on 2020/6/16.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include "common.h"
#include "camera.h"
#include "Application.hpp"
#include "Shader.hpp"

class Skybox {
public:
    Skybox();
    ~Skybox();
    
    void init();
    
    void draw(Camera& camera, Application* app);
    
private:
    void loadCubemap(std::vector<std::string> faces);
    
private:
    GLuint      _vao;
    GLuint      _vbo;
    GLuint      _cubemapTexture;
    GLfloat     _size;
    Shader      _shader;
};

#endif /* Skybox_hpp */
