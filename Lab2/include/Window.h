#pragma once
#include <SFML/Window.hpp>  
#include <glad/glad.h>
//#include <SFML/OpenGL.hpp>
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

    void DrawTriangle(glm::vec3 l_point_1, glm::vec3 l_point_2, glm::vec3 l_point_3);

    // hz
    // void DrawLine(sf::Vector2f &l_point_1, sf::Vector2f &l_point_2, bool l_is_stipple = false, GLfloat l_opacity = 1.f,
    //     GLfloat l_red_point_1 = 1.f, GLfloat l_green_point_1 = 0.f, GLfloat l_blue_point_1 = 0.f,
    //     GLfloat l_red_point_2 = 0.f, GLfloat l_green_point_2 = 0.f, GLfloat l_blue_point_2 = 1.f);
    // void DrawRect(sf::Vector2f &l_point_1, sf::Vector2f &l_point_2, bool l_is_black = false);
    // void DrawFilledRect(sf::Vector2f &l_point_1, sf::Vector2f &l_point_2, GLfloat l_opacity = 1.f, 
    //     GLfloat l_red = 1.f, GLfloat l_green = 1.f, GLfloat l_blue = 1.f);
    // void DrawTriangle(sf::Vector2f &l_point_1, sf::Vector2f &l_point_2, sf::Vector2f &l_point_3);
    //

private:
    void Setup(const std::string &l_title, const sf::Vector2u &l_size);
    void Destroy();
    void Create();
    sf::Window m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isOver;
    bool m_isFullscreen;
};