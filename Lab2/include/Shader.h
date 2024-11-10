#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    GLuint ID;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void Use();

    void SetBool(const std::string &name, const GLboolean value) const;
    void SetInt(const std::string &name, const GLint value) const;
    void SetFloat(const std::string &name, const GLfloat value) const;
    void SetFloatMatrix(const std::string &name, const GLfloat* matrix) const;
private:

    void CheckCompileErrors(GLuint shader, std::string type);
};