//
//  Texture.cpp
//  renderer
//
//  Created by MrMac on 2020/5/21.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include "Texture2D.hpp"
#include "Utils.hpp"

#include <stb_image.h>

Texture2D::Texture2D()
: _texture(0)
{
    textureUnit = 0;
}

Texture2D::~Texture2D()
{
    if (_texture)
        glDeleteTextures(1, &_texture);
}

void Texture2D::loadTexture(const char *filename)
{
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, comp;
    unsigned char* data = stbi_load(filename, &width, &height, &comp, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (comp == 1)
            format = GL_RED;
        else if (comp == 3)
            format = GL_RGB;
        else if (comp == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
                     format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "std_image load error " << filename << std::endl;
    }
    stbi_image_free(data);
}

void Texture2D::bindTexture()
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, _texture);
}

GLuint Texture2D::getTexture()
{
    return _texture;
}
