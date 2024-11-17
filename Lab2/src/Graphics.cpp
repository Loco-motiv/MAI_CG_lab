#include "Graphics.h"

Graphics::Graphics()
{
    ConfigureOpenGL();
    MakeShader("shaders/VertexShader.vert", "shaders/FragmentShader.frag");
    MakeTriangleVAO();
    MakeCubeVAO();
    MakeRectangleVAO();
}

Graphics::~Graphics()
{
    FreeObjects();
}

void Graphics::ConfigureOpenGL()
{
    gladLoadGL();
    glClearColor(0.2f, 0.6f, 0.3f, 1.0f);

    glEnable(GL_CULL_FACE);  //* enable culling faces
    glCullFace(GL_BACK);     //* cull back face
    glFrontFace(GL_CCW);     //* counter clock-wise

    glEnable(GL_DEPTH_TEST); //* enable depth-testing
    glDepthFunc(GL_LESS);    //* write to z buffer then w value is less than present in buffer

    glEnable(GL_BLEND);      //* enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::MakeShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    m_shader = new Shader(vertexPath, fragmentPath);
}

void Graphics::FreeObjects()
{
    delete m_shader;
}

void Graphics::MakeTriangleVAO()
{
    // clang-format off
    GLfloat points[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    GLfloat colours[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    // clang-format on

    GLuint pointsVBO;
    glCreateBuffers(1, &pointsVBO);
    glNamedBufferData(pointsVBO, 9 * sizeof(GLfloat), points, GL_STATIC_DRAW);

    GLuint coloursVBO;
    glCreateBuffers(1, &coloursVBO);
    glNamedBufferData(coloursVBO, 9 * sizeof(GLfloat), colours, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &m_triangleVAO);

    glVertexArrayVertexBuffer(m_triangleVAO, 0, pointsVBO, 0, 3 * sizeof(GL_FLOAT));
    glVertexArrayVertexBuffer(m_triangleVAO, 1, coloursVBO, 0, 3 * sizeof(GL_FLOAT));

    glVertexArrayAttribFormat(m_triangleVAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(m_triangleVAO, 1, 3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(m_triangleVAO, 0, 0);
    glVertexArrayAttribBinding(m_triangleVAO, 1, 1);

    glEnableVertexArrayAttrib(m_triangleVAO, 0);
    glEnableVertexArrayAttrib(m_triangleVAO, 1);
}

void Graphics::MakeCubeVAO()
{
    // clang-format off
    GLfloat vertices[] = {
    //*  coordinates         colors
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, //* top right front
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, //* bottom right front
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, //* bottom left front
        -0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //* top left front
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //* top right back
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //* bottom right back
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //* bottom left back
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f  //* top left back
    };
    // clang-format on

    GLuint indices[] = {
        //* front face
        0, 3, 1,
        3, 2, 1,
        //* back face
        5, 7, 4,
        6, 7, 5,
        //* left face
        7, 6, 3,
        3, 6, 2,
        //* right face
        0, 1, 5,
        0, 5, 4,
        //* top face
        7, 3, 4,
        4, 3, 0,
        //* bottom face
        5, 2, 6,
        1, 2, 5
    };

    GLuint pointsVBO;
    glCreateBuffers(1, &pointsVBO);
    glNamedBufferData(pointsVBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint pointsIBO;
    glCreateBuffers(1, &pointsIBO);
    glNamedBufferData(pointsIBO, sizeof(indices), indices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &m_cubeVAO);

    glVertexArrayVertexBuffer(m_cubeVAO, 0, pointsVBO, 0, 6 * sizeof(GL_FLOAT));
    glVertexArrayElementBuffer(m_cubeVAO, pointsIBO);

    glVertexArrayAttribFormat(m_cubeVAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(m_cubeVAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));

    glVertexArrayAttribBinding(m_cubeVAO, 0, 0);
    glVertexArrayAttribBinding(m_cubeVAO, 1, 0);

    glEnableVertexArrayAttrib(m_cubeVAO, 0);
    glEnableVertexArrayAttrib(m_cubeVAO, 1);
}

void Graphics::MakeRectangleVAO()
{
    // clang-format off
    GLfloat vertices[] = {
    //*  coordinates        colors
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, //* top right
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, //* bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, //* bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f  //* top left
    };
    GLuint indices[] = {
        //* top part
        0, 3, 1,
        //* bottom part
        3, 2, 1
    };
    // clang-format on

    GLuint pointsVBO;
    glCreateBuffers(1, &pointsVBO);
    glNamedBufferData(pointsVBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint pointsIBO;
    glCreateBuffers(1, &pointsIBO);
    glNamedBufferData(pointsIBO, sizeof(indices), indices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &m_rectangleVAO);

    glVertexArrayVertexBuffer(m_rectangleVAO, 0, pointsVBO, 0, 6 * sizeof(GL_FLOAT));
    glVertexArrayElementBuffer(m_rectangleVAO, pointsIBO);

    glVertexArrayAttribFormat(m_rectangleVAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(m_rectangleVAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));

    glVertexArrayAttribBinding(m_rectangleVAO, 0, 0);
    glVertexArrayAttribBinding(m_rectangleVAO, 1, 0);

    glEnableVertexArrayAttrib(m_rectangleVAO, 0);
    glEnableVertexArrayAttrib(m_rectangleVAO, 1);
}

void Graphics::DrawRectangle()
{
    glBindVertexArray(m_rectangleVAO);
    m_shader->Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Graphics::DrawCube()
{
    glBindVertexArray(m_cubeVAO);
    m_shader->Use();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}