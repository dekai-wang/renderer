//
//  Mesh.h
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include "common.h"

struct Mesh {
    vector<GLfloat>         verticesPosition;
    vector<GLfloat>         verticesTexture;
    vector<GLuint>          indices;
};

#endif /* Mesh_h */
