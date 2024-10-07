#include "Window.h"

Window::Window() { Setup("Lab_2", sf::Vector2u(640, 480)); }

Window::Window(const std::string &l_title, const sf::Vector2u &l_size)
{
    Setup(l_title, l_size);
    ConfigureOpenGL();
    GetProgram();
    MakeTriangleVAO();
}

Window::~Window() 
{ 
    Destroy();
}

void Window::Setup(const std::string &l_title, const sf::Vector2u &l_size)
{
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullscreen = false;
    m_isOver = false;
    Create();
}

void Window::Create()
{
    sf::ContextSettings settings;
    settings.depthBits = 32;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 8;
    settings.majorVersion = 4; // opengl 4.6
    settings.minorVersion = 6; // opengl 4.6
    settings.attributeFlags = sf::ContextSettings::Attribute::Core;
    
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), m_windowTitle, style, settings);
    m_window.setVerticalSyncEnabled(true); // frames displaying at monitor refresh rate

    m_window.setActive(true); // activate window for opengl rendering
}

void Window::Destroy()
{
    //It's over ((
    m_window.close();
}

void Window::Update() 
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_isOver = true;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) 
        {
            ToggleFullscreen();
        }
        else if (event.type == sf::Event::Resized)
        {
            // adjust the viewport when the window is resized
            glViewport(0, 0, event.size.width, event.size.height); // calculate opengl coordinates from display coordinates 
            m_windowSize = m_window.getSize(); // update attribute for GetWindowSize
        }
    }
}

void Window::ToggleFullscreen() 
{
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}

bool Window::IsOver() { return m_isOver; }

bool Window::IsFullscreen() { return m_isFullscreen;}

sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

sf::Window* Window::GetWindow()
{
    return &m_window;
}

void Window::BeginDraw() 
{
    glClear(GL_COLOR_BUFFER_BIT); //  clear color buffer
}

void Window::EndDraw() 
{
    glFlush(); // force execution of GL commands
    m_window.display();
}

void Window::ConfigureOpenGL()
{
    gladLoadGL();
    glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
    glEnable(GL_CULL_FACE); // enable culling faces
    glCullFace(GL_BACK);    // cull back face
    glFrontFace(GL_CCW);    // counter clock-wise
    // glEnable(GL_DEPTH_TEST); // enable depth-testing
    // glDepthFunc(GL_LESS);
}

void Window::GetProgram()
{
    const char *vertexShaderSource = "#version 460 core\n"
                                     "layout(location = 0) in vec3 vertex_position;\n"
                                     "layout(location = 1) in vec3 vertex_colour;\n"
                                     "out vec3 colour;\n"
                                     "void main() {\n"
                                     "colour = vertex_colour;\n"
                                     "gl_Position = vec4(vertex_position, 1.0);\n"
                                     "}\n\0";

    const char *fragmentShaderSource = "#version 460 core\n"
                                       "in vec3 colour;\n"
                                       "out vec4 frag_colour;\n"
                                       "void main() {\n"
                                       "frag_colour = vec4(colour, 1.0);\n"
                                       "}\n\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for compile errors
    GLint success = -1;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (GL_TRUE != success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check for compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (GL_TRUE != success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (GL_TRUE != success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);
}

void Window::MakeTriangleVAO()
{
    GLfloat points[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f};

    GLfloat colours[] = {
        1.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 1.0f};

    GLuint pointsVBO;
    glCreateBuffers(1, &pointsVBO);
    // glGenBuffers(1, &pointsVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    // glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), points, GL_STATIC_DRAW);
    glNamedBufferData(pointsVBO, 9 * sizeof(GLfloat), points, GL_STATIC_DRAW);

    GLuint coloursVBO;
    glCreateBuffers(1, &coloursVBO);
    // glGenBuffers(1, &coloursVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
    // glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colours, GL_STATIC_DRAW);
    glNamedBufferData(coloursVBO, 9 * sizeof(GLfloat), colours, GL_STATIC_DRAW);

    GLuint VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);
    glCreateVertexArrays(1, &VAO);

    glVertexArrayVertexBuffer(VAO, 0, pointsVBO, 0, 3 * sizeof(GL_FLOAT));
    glVertexArrayVertexBuffer(VAO, 1, coloursVBO, 0, 3 * sizeof(GL_FLOAT));
    
    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
    
    // glVertexArrayAttribBinding(VAO, 0, 0);
    // glVertexArrayAttribBinding(VAO, 1, 1);

    // glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), NULL);

    // glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), NULL);
    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);

    glEnableVertexArrayAttrib(VAO, 0);
    glEnableVertexArrayAttrib(VAO, 1);
    // glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(VAO);
}

void Window::DrawTriangle()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}