//
//  Model3D.hpp
//  renderer
//
//  Created by MrMac on 2020/5/27.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef Model3D_hpp
#define Model3D_hpp

#include "common.h"
#include "Shader.hpp"
#include "Mesh3D.hpp"

class Model3D{
public:
    Model3D(const char* path, bool gamma = false):gammaCorrection(gamma) {
        loadModel(path);
    }

    void Draw(Shader shader);

private:
    std::vector<Mesh3D> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh3D processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialtextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif /* Model3D_hpp */
