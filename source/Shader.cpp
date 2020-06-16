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
    std::string vertStr = Utils::getFileData(vertPath);
    const char* vertCode = vertStr.data();
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertCode, nullptr);
    glCompileShader(vert);
    checkCompileError(vert, "VERTEX");
    
    std::string fragStr = Utils::getFileData(fragPath);
    const char* fragCode = fragStr.data();
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

void Shader::checkCompileError(unsigned int shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
