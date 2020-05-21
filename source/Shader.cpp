//
//  Shader.cpp
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include "Shader.hpp"

#include "common.h"
#include "Utils.hpp"

Shader::Shader()
{
    
}

Shader::~Shader()
{
    
}

void Shader::init(const char *vertPath, const char *fragPath)
{
    const char* vertCode = Utils::getFileData(vertPath).data();
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertCode, nullptr);
    glCompileShader(vert);
    checkCompileError(vert, "VERTEX");
    
    const char* fragCode = Utils::getFileData(fragPath).data();
    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragCode, nullptr);
    glCompileShader(frag);
    checkCompileError(frag, "RAGMENT");
    
    _program = glCreateProgram();
    glAttachShader(_program, vert);
    glAttachShader(_program, frag);
    glLinkProgram(_program);
    checkCompileError(_program, "PROGRAM");
    
    glDeleteShader(vert);
    glDeleteShader(frag);
}

void Shader::useProgram()
{
    glUseProgram(_program);
}

unsigned int Shader::getProgram()
{
    return _program;
}

void Shader::checkCompileError(unsigned int shader, string type)
{
    
}
