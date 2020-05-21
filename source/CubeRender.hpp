//
//  CubeRender.hpp
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef CubeRender_hpp
#define CubeRender_hpp

#include "camera.h"
#include "Model.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Application.hpp"

class CubeRender {
public:
    CubeRender(glm::vec3 pos);
    ~CubeRender();
    
    void render(Camera& camera, Application* app);
    
private:
    Model       _model;
    Shader      _shader;
    Texture     _texture;
    glm::vec3   _pos;
};

#endif /* CubeRender_hpp */
