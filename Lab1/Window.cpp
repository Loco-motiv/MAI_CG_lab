#include "window.h"

Window::Window() { Setup("Lab_1", sf::Vector2u(640, 480)); }

Window::Window(const std::string &l_title, const sf::Vector2u &l_size)
{
    Setup(l_title, l_size);
}

Window::~Window() { Destroy(); }

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
    
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), m_windowTitle, style, settings);
    m_window.setVerticalSyncEnabled(true); // frames displaying at monitor refresh rate

    glEnable(GL_BLEND); // enable opaque parameter for glColor4
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // rule for calculating blending

    glLineWidth(2); // x2 line width for nicer lines at angles

    m_window.setActive(true); // activating window for opengl rendering
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
            glViewport(0, 0, event.size.width, event.size.height); // calculating opengl coordinates from display coordinates 
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 
}

void Window::EndDraw() 
{
    glFlush();
    m_window.display();
}

void Window::DrawLine(sf::Vector2f &l_point_1, sf::Vector2f &l_point_2, bool l_is_stipple, GLfloat l_opacity, 
    GLfloat l_red_point_1, GLfloat l_green_point_1, GLfloat l_blue_point_1, GLfloat l_red_point_2,
    GLfloat l_green_point_2, GLfloat l_blue_point_2) 
{
    if (l_point_1 == l_point_2)
    {
        return;
    }  
    if (l_is_stipple)
    {
        glEnable(GL_LINE_STIPPLE); // enable stippling for next line
        glLineStipple(1, 0x00FF); // dash stipple
    }
    glBegin(GL_LINES);
        glColor4f(l_red_point_1, l_green_point_1, l_blue_point_1, l_opacity);
        glVertex2f(l_point_1.x, l_point_1.y);
        glColor4f(l_red_point_2, l_green_point_2, l_blue_point_2, l_opacity);
        glVertex2f(l_point_2.x, l_point_2.y);
    glEnd();
    if (l_is_stipple)
    {
        glDisable(GL_LINE_STIPPLE); // disable dash stippling for next lines
    }
}

void Window::DrawRect(sf::Vector2f &l_point_1, sf::Vector2f &l_point_2, bool l_is_black)
{
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f);
        if (l_is_black)
        {
            glColor3f(0.f, 0.f, 0.f);
        }
        glVertex2f(l_point_1.x, l_point_1.y);
        glColor3f(0.0f, 1.0f, 1.0f);
        if (l_is_black)
        {
            glColor3f(0.f, 0.f, 0.f);
        }
        glVertex2f(l_point_2.x, l_point_1.y);
        glColor3f(0.5f, 0.0f, 1.0f);
        if (l_is_black)
        {
            glColor3f(0.f, 0.f, 0.f);
        }
        glVertex2f(l_point_2.x, l_point_2.y);
        glColor3f(1.0f, 0.0f, 0.0f);
        if (l_is_black)
        {
            glColor3f(0.f, 0.f, 0.f);
        }
        glVertex2f(l_point_1.x, l_point_2.y);
    glEnd();
}

void Window::DrawFilledRect(sf::Vector2f &l_point_1, sf::Vector2f &l_point_2, GLfloat l_opacity, GLfloat l_red, GLfloat l_green, GLfloat l_blue)
{
    glBegin(GL_QUADS);
        glColor4f(l_red, l_green, l_blue, l_opacity);
        glVertex2f(l_point_1.x, l_point_1.y);
        glVertex2f(l_point_2.x, l_point_1.y);
        glVertex2f(l_point_2.x, l_point_2.y);
        glVertex2f(l_point_1.x, l_point_2.y);
    glEnd();
}

void Window::DrawTriangle(sf::Vector2f &l_point_1, sf::Vector2f &l_point_2, sf::Vector2f &l_point_3)
{
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(l_point_1.x, l_point_1.y);
        glVertex2f(l_point_2.x, l_point_2.y);
        glVertex2f(l_point_3.x, l_point_3.y);
    glEnd();
}