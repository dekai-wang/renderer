//
//  Texture.hpp
//  renderer
//
//  Created by MrMac on 2020/5/21.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "common.h"

class Texture {
public:
    Texture();
    ~Texture();
    
    void loadTexture(const char* imagePath);
    
    void bindTexture();
    
    GLuint getTexture();
private:
    GLuint      _texture;
};

#endif /* Texture_hpp */
