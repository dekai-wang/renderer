//
//  Model.hpp
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include "common.h"
#include "Mesh.h"

class Model {
public:
    Model();
    
    ~Model();
    
    void init();
    
    void clean();
    
    void bindVAO();

    void genVBO(GLuint index, GLint size, const std::vector<GLfloat> &data);
    
    void genEBO(const std::vector<GLuint> &data);

private:
    GLuint                  _vao;
    std::vector<GLuint>     _vecVbo;
};

#endif /* Model_hpp */
