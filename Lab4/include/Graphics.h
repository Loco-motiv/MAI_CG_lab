#pragma once

#include "Matrix.h"
#include "Shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <SFML/Window.hpp>
#include <map>

struct Character
{
    GLuint textureID; // ID handle of the glyph texture
    GLuint sizeX;
    GLuint sizeY;
    GLint bearingLeft; // Offset from baseline to left/top of glyph
    GLint bearingTop;
    GLint advance;     // Horizontal offset to advance to next glyph
};

class Graphics
{
public:
    Graphics();
    ~Graphics();
    Shader* m_shader;
    Shader* m_textShader;
    Shader* m_lightSourceShader;
    Shader* m_GUIShader;
    void DrawCube();
    void DrawLightSourceCube();
    void DrawRectangle();
    void RenderText(const std::string& text, GLfloat x, GLfloat y,
                    GLfloat sx, GLfloat sy, GLfloat scale,
                    GLfloat colorR, GLfloat colorG, GLfloat colorB);
    sf::Vector2f GetTextDimensions(const std::string& text, GLfloat sx, GLfloat sy, GLfloat scale);
    GLfloat GetMaxTextHeight(GLfloat sy) const;

private:
    void MakeShader(const GLchar* vertexPath, const GLchar* fragmentPath, Shader*& l_shader);
    void MakeTriangleVAO();
    void MakeCubeVAO();
    void MakeLightSourceCubeVAO();
    void MakeRectangleVAO(); //? color
    void FreeObjects();
    void ConfigureOpenGL();
    void ConfigureFreeType();

    GLuint m_triangleVAO;

    GLuint m_cubeVAO;
    GLuint m_lightSourceCubeVAO;
    GLuint m_cubeVBO;
    GLuint m_cubeIBO;

    GLuint m_rectangleVAO;

    GLuint m_textVAO;
    GLuint m_textVBO;

    FT_Library m_ft;
    FT_Face m_face;
    std::map<GLchar, Character> Characters;

    GLfloat m_minTextHeight;
    GLfloat m_maxTextHeight;
};