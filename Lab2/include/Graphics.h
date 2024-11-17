#pragma once

#include "Shader.h"

class Graphics
{
public:
    Graphics();
    ~Graphics();
    Shader* m_shader;
    void DrawCube();
    void DrawRectangle();

private:
    void MakeShader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void MakeTriangleVAO();
    void MakeCubeVAO();
    void MakeRectangleVAO(); //? color
    void FreeObjects();
    void ConfigureOpenGL();

    GLuint m_triangleVAO;
    GLuint m_cubeVAO;
    GLuint m_rectangleVAO;
};