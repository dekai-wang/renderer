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
#include "Texture2D.hpp"
#include "Application.hpp"

class CubeRender {
public:
    CubeRender(glm::vec3 pos, std::string filename);
    ~CubeRender();
    
    void render(Camera& camera, Application* app);
    
private:
    glm::vec3   _pos;
    Model       _model;
    Shader      _shader;
    Texture2D     _texture1;
    Texture2D     _texture2;
};

#endif /* CubeRender_hpp */
