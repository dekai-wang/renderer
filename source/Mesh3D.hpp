//
//  Mesh3D.hpp
//  renderer
//
//  Created by MrMac on 2020/5/27.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef Mesh3D_hpp
#define Mesh3D_hpp

#include "common.h"

class Shader;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    //glm::vec3 Tangent;
    //glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh3D {
public:
    Mesh3D(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<Texture>& textures);
    void Draw(Shader shader);

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

private:
    unsigned int VAO, VBO, EBO; 

    void setupMesh();
};

#endif /* Mesh3D_hpp */
