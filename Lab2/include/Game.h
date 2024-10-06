#pragma once
#include "Window.h"
#include "vector"
#include "cmath"

class Game{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
    void RestartClock();

private:
    sf::Vector2f ConvertCoordinates(sf::Vector2i& l_point);
    float GetDistance(sf::Vector2f& l_point_1, sf::Vector2f& l_point_2);

    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed_time_fixed;
};