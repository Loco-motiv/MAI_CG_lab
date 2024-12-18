#include "Graphics.h"

Graphics::Graphics()
{
    ConfigureOpenGL();
    MakeShader("shaders/MainVertexShader.vert", "shaders/MainFragmentShader.frag", m_shader);
    MakeShader("shaders/TextVertexShader.vert", "shaders/TextFragmentShader.frag", m_textShader);
    ConfigureFreeType();
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

void Graphics::ConfigureFreeType()
{
    if (FT_Init_FreeType(&m_ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    if (FT_New_Face(m_ft, "resources/fonts/arial.ttf", 0, &m_face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    FT_Set_Pixel_Sizes(m_face, 0, 32);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_face->glyph->bitmap.width,
            m_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_face->glyph->bitmap.buffer);
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows,
            m_face->glyph->bitmap_left, m_face->glyph->bitmap_top,
            m_face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); //?

    glGenVertexArrays(1, &m_textVAO);
    glGenBuffers(1, &m_textVBO);
    glBindVertexArray(m_textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_minTextHeight = Characters['a'].bearingTop;
    m_maxTextHeight = Characters['T'].bearingTop + Characters['p'].sizeY - Characters['p'].bearingTop;
}

void Graphics::MakeShader(const GLchar* vertexPath, const GLchar* fragmentPath, Shader*& l_shader)
{
    l_shader = new Shader(vertexPath, fragmentPath);
}

void Graphics::FreeObjects()
{
    delete m_shader;
    delete m_textShader;
}

void Graphics::MakeTriangleVAO()
{
    GLfloat points[3][3] = {
        {  0.0f,  0.5f, 0.0f },
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f }
    };

    GLfloat colours[3][3] = {
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f }
    };

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
    GLfloat vertices[8][6] = {
        //*coordinates         colors
        {  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f }, //* top right front
        {  0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f }, //* bottom right front
        { -0.5f, -0.5f,  0.5f, 0.8f, 1.0f, 1.0f }, //* bottom left front
        { -0.5f,  0.5f,  0.5f, 1.0f, 0.6f, 0.7f }, //* top left front
        {  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f }, //* top right back
        {  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f }, //* bottom right back
        { -0.5f, -0.5f, -0.5f, 0.6f, 0.6f, 1.0f }, //* bottom left back
        { -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f }  //* top left back
    };

    GLuint indices[12][3] = {
        //* front face
        { 0, 3, 1 },
        { 3, 2, 1 },
        //* back face
        { 5, 7, 4 },
        { 6, 7, 5 },
        //* left face
        { 7, 6, 3 },
        { 3, 6, 2 },
        //* right face
        { 0, 1, 5 },
        { 0, 5, 4 },
        //* top face
        { 7, 3, 4 },
        { 4, 3, 0 },
        //* bottom face
        { 5, 2, 6 },
        { 1, 2, 5 }
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
    GLfloat vertices[4][6] = {
        //*coordinates        colors
        {  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //* top right
        {  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //* bottom right
        { -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //* bottom left
        { -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f }  //* top left
    };
    GLuint indices[2][3] = {
        //* top part
        { 0, 3, 1 },
        //* bottom part
        { 3, 2, 1 }
    };

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

void Graphics::RenderText(const std::string& text, GLfloat x, GLfloat y,
                          GLfloat sx, GLfloat sy, GLfloat scale,
                          GLfloat colorR, GLfloat colorG, GLfloat colorB)
{
    // activate corresponding render state
    m_textShader->Use();
    m_textShader->SetFloatVec3("textColor", colorR, colorG, colorB);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_textVAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.bearingLeft * scale * sx;
        GLfloat ypos = y - (ch.sizeY - ch.bearingTop) * scale * sy;

        GLfloat w = ch.sizeX * scale * sx;
        GLfloat h = ch.sizeY * scale * sy;
        // update VBO for each character
        GLfloat vertices[6][4] = {
            {     xpos, ypos + h, 0.0f, 0.0f },
            {     xpos,     ypos, 0.0f, 1.0f },
            { xpos + w,     ypos, 1.0f, 1.0f },

            {     xpos, ypos + h, 0.0f, 0.0f },
            { xpos + w,     ypos, 1.0f, 1.0f },
            { xpos + w, ypos + h, 1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale * sx; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

sf::Vector2f Graphics::GetTextDimensions(const std::string& text, GLfloat sx, GLfloat sy, GLfloat scale)
{
    GLfloat x = 0;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        x += (ch.advance >> 6) * scale * sx; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    return sf::Vector2f(x, m_minTextHeight * scale * sy);
}

GLfloat Graphics::GetMaxTextHeight(GLfloat sy) const
{
    return m_maxTextHeight * sy;
}