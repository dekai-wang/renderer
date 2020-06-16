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
#include "camera.h"
#include "Application.hpp"

class Model3D{
public:
    Model3D(const char* path, bool gamma = false):gammaCorrection(gamma) {
        shader.init("resource/model3d.vert", "resource/model3d.frag");
        loadModel(path);
    }

    void Draw(Camera& camera, Application* app);
    
private:
    std::vector<Mesh3D> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh3D processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialtextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    
    Shader              shader;
};

#endif /* Model3D_hpp */
