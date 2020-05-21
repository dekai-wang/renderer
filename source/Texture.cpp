//
//  Texture.cpp
//  renderer
//
//  Created by MrMac on 2020/5/21.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include "Texture.hpp"
#include "Utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
    
}

Texture::~Texture()
{
    glDeleteTextures(1, &_texture);
}

void Texture::loadTexture(const char *filename)
{
    glGenTextures(1, &_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, comp;
    unsigned char* data = stbi_load(filename, &width, &height, &comp, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {

    }
    stbi_image_free(data);
}

void Texture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, _texture);
}

GLuint Texture::getTexture()
{
    return _texture;
}
