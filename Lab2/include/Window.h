#pragma once
#include <SFML/Window.hpp>  
#include <glad/glad.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <iostream>

class Window
{
public:
    Window();
    Window(const std::string &l_title, const sf::Vector2u &l_size);
    ~Window();
    void BeginDraw(); // Clear the window.
    void EndDraw();   // Display the changes.
    void Update();
    bool IsOver();    // It's over ((
    bool IsFullscreen();
    sf::Window* GetWindow();
    sf::Vector2u GetWindowSize();
    void ToggleFullscreen();

    void DrawTriangle();

private:
    void Setup(const std::string &l_title, const sf::Vector2u &l_size);
    void Destroy();
    void Create();
    void ConfigureOpenGL();
    void GetProgram();
    void MakeTriangleVAO();
    sf::Window m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    GLboolean m_isOver;
    GLboolean m_isFullscreen;
};