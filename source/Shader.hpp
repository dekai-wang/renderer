//
//  Shader.hpp
//  renderer
//
//  Created by MrMac on 2020/5/20.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "common.h"

class Shader {

public:
    Shader();
    ~Shader();
    
    void init(const char* vertPath, const char* fragPath);
    
    void useProgram()
    {
        glUseProgram(_program);
    }

    GLuint getProgram()
    {
        return _program;
    }

    GLint getAttrib(const char* attrib)
    {
        return glGetAttribLocation(_program, attrib);
    }

    GLint getUnifrom(const char* attrib)
    {
        return glGetUniformLocation(_program, attrib);
    }
    
    void setBool(const std::string &name, bool value) const
    {
       glUniform1i(glGetUniformLocation(_program, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const
    {
       glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const
    {
       glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
       glUniform2fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
       glUniform2f(glGetUniformLocation(_program, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
       glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
       glUniform3f(glGetUniformLocation(_program, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
       glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w)
    {
       glUniform4f(glGetUniformLocation(_program, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
       glUniformMatrix2fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
       glUniformMatrix3fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
       glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
private:
    void checkCompileError(unsigned int shader, std::string type);
    
private:
    GLuint       _program;
};

#endif /* Shader_hpp */
