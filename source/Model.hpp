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
    
    void init(Mesh mesh);
    
    void clean();
    
    void bindVAO();

    void genVBO(int dimensions, const vector<GLfloat> &data);
    
    void genEBO(const vector<unsigned int> &data);
    
    unsigned int getIndicesCount();
private:
    Mesh            _mesh;
    GLuint          _vao;
    GLuint          _vboCount;
    vector<GLuint>  _vecVbo;
};

#endif /* Model_hpp */
